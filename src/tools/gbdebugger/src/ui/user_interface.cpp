#include "ui/user_interface.hpp"
#include <imgui-SFML.h>
#include <imgui.h>

#include <fmt/format.h>

#include <chrono>
#include <functional>
#include <iostream>


UserInterface::UserInterface(gb::GameboyCore& core, DebuggerInterface& debugger)
    : window_{ sf::VideoMode{800, 600}, "GameboyCore Debugger" }
    , core_{core}
    , debugger_{debugger}
    , screen_sprite_{}
    , key_map_{}
{
    ImGui::SFML::Init(window_);

    if (!screen_texture_.create(framebuffer_.width(), framebuffer_.height()))
    {
        throw std::runtime_error("Could not create texture!");
    }

    screen_sprite_.setTexture(screen_texture_);

    // key mapping
    key_map_.insert({ sf::Keyboard::Key::W, gb::Joy::Key::UP });
    key_map_.insert({ sf::Keyboard::Key::S, gb::Joy::Key::DOWN });
    key_map_.insert({ sf::Keyboard::Key::A, gb::Joy::Key::LEFT });
    key_map_.insert({ sf::Keyboard::Key::D, gb::Joy::Key::RIGHT });
    key_map_.insert({ sf::Keyboard::Key::J, gb::Joy::Key::A });
    key_map_.insert({ sf::Keyboard::Key::K, gb::Joy::Key::B });
    key_map_.insert({ sf::Keyboard::Key::Return, gb::Joy::Key::START });
    key_map_.insert({ sf::Keyboard::Key::LShift, gb::Joy::Key::SELECT });

    initialize(core);
}

UserInterface::~UserInterface()
{
    audio_stream_.stop();
    ImGui::SFML::Shutdown();
}

void UserInterface::initialize(gb::GameboyCore& core)
{
    core.setScanlineCallback(std::bind(&UserInterface::scanlineCallback, this, std::placeholders::_1, std::placeholders::_2));
    core.setVBlankCallback(std::bind(&UserInterface::vblankCallback, this));

    audio_stream_.initialize(core);
    audio_stream_.start();

    key_event_ = std::bind(&gb::GameboyCore::input, &core, std::placeholders::_1, std::placeholders::_2);
}

void UserInterface::run()
{
    using namespace std::chrono_literals;

    while (isRunning())
    {
        // TODO: Execution Control
        if (debugger_.getMode() == DebuggerInterface::Mode::RUN)
        {
            debugger_.runFrame();
        }

        state_ = core_.getCPU()->getStatus();
        //std::cout << std::hex << state_.pc << "\n";

        update();

        std::this_thread::sleep_for(16ms);
    }
}

void UserInterface::update()
{
    sf::Event event;

    while (window_.pollEvent(event))
    {
        ImGui::SFML::ProcessEvent(event);

        switch (event.type)
        {
        case sf::Event::Closed:
            window_.close();
            break;
        case sf::Event::Resized:
            // adjust view port
            window_.setView(sf::View(sf::FloatRect(0, 0, (float)event.size.width, (float)event.size.height)));
            break;
        case sf::Event::KeyPressed:
            handleKeyEvent(event.key.code, true);
            break;
        case sf::Event::KeyReleased:
            handleKeyEvent(event.key.code, false);
            break;
        default:
            break;
        }
    }

    ImGui::SFML::Update(window_, delta_clock_.restart());
 
    drawUI();
    //ImGui::ShowDemoWindow();

    window_.clear(sf::Color{ 255, 255, 255, 255 });
    ImGui::SFML::Render(window_);

    window_.display();
}

void UserInterface::drawUI()
{
    static constexpr auto window_flags = ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize
        | ImGuiWindowFlags_NoScrollbar;

    const auto& window_size = ImGui::GetIO().DisplaySize;
    const auto width = window_size.x;
    const auto height = window_size.y;

    ImGui::SetNextWindowPos({ 0, 0 });
    ImGui::SetNextWindowSize({ width, height });

    if (ImGui::Begin("Debugger", nullptr, window_flags))
    {
        const auto col_width = width / 3;

        // Create Left Pace
        if (ImGui::BeginChild("controls", {col_width, height}))
        {
            drawExecutionControl();
            ImGui::Separator();
            drawRegisters();
            ImGui::Separator();
            drawDisassembly();

            ImGui::EndChild();
        }

        ImGui::SameLine();

        if (ImGui::BeginChild("display", { 2 * col_width, height }))
        {
            drawDisplay();

            ImGui::EndChild();
        }

        ImGui::End();
    }
}

void UserInterface::drawExecutionControl()
{
    if (debugger_.getMode() == DebuggerInterface::Mode::RUN)
    {
        if (ImGui::Button("Break"))
        {
            debugger_.setMode(DebuggerInterface::Mode::STEP);
        }
    }
    else
    {
        if (ImGui::Button("Run"))
        {
            debugger_.setMode(DebuggerInterface::Mode::RUN);
        }
        ImGui::SameLine();
        if (ImGui::Button("Step"))
        {
            debugger_.step();
        }
    }
}

void UserInterface::drawRegisters()
{
    ImGui::Columns(3, "registers", false);

    ImGui::Text("AF: %04X", state_.af);
    ImGui::Text("BC: %04X", state_.bc);
    ImGui::Text("DE: %04X", state_.de);
    ImGui::Text("HL: %04X", state_.hl);

    ImGui::NextColumn();

    ImGui::Text("SP: %04X", state_.sp);
    ImGui::Text("PC: %04X", state_.pc);

    ImGui::NextColumn();

    ImGui::Text("Z: %d", state_.flag_z);
    ImGui::Text("N: %d", state_.flag_n);
    ImGui::Text("H: %d", state_.flag_h);
    ImGui::Text("C: %d", state_.flag_c);

    ImGui::Columns(1);
}

void UserInterface::drawDisassembly()
{
    if (ImGui::BeginChild("disassembly_view"))
    {
        const auto& disassembly_data = debugger_.getDisassembly();
        const auto size = disassembly_data.size();

        ImGuiListClipper clipper(size);

        while (clipper.Step())
        {
            for (auto i = clipper.DisplayStart; i < clipper.DisplayEnd; ++i)
            {
                const auto& data = disassembly_data.at(i);

                const auto str = fmt::format("{:08X}|{:04X}| {}", data.memory_address, data.logical_address, data.disassem);
                ImGui::Selectable(str.c_str(), state_.pc == data.logical_address);
            }
        }

        ImGui::EndChild();
    }
}

void UserInterface::drawDisplay()
{
    const auto window_size = ImGui::GetContentRegionAvail();
    const auto texture_size = screen_texture_.getSize();
    const auto x_scale = window_size.x / texture_size.x;
    const auto y_scale = window_size.y / texture_size.y;

    screen_sprite_.setScale(x_scale, y_scale);

    ImGui::Image(screen_sprite_);
}

void UserInterface::handleKeyEvent(sf::Keyboard::Key key, bool pressed)
{
    if (key_map_.find(key) != key_map_.end())
    {
        key_event_(key_map_[key], pressed);
    }
}

void UserInterface::scanlineCallback(const gb::GPU::Scanline& scanline, int line)
{
    // Buffer the scanline
    for (auto i = 0u; i < scanline.size(); ++i)
    {
        const auto& p = scanline[i];
        framebuffer_.write(i, line, sf::Color{ p.r, p.g, p.b, 255 });
    }
}

void UserInterface::vblankCallback()
{
    // A full frame is done
    // Update the screen texture
    screen_texture_.update(framebuffer_.data());
}

bool UserInterface::isRunning() const
{
    return window_.isOpen();
}
