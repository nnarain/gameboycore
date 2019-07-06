#include "ui/user_interface.hpp"

#include <imgui.h>
#include <imgui-SFML.h>

#include <chrono>
#include <functional>
#include <iostream>

static constexpr ImGuiWindowFlags TAB_WINDOW_FLAGS = ImGuiWindowFlags_NoScrollbar |
                                                     ImGuiWindowFlags_NoCollapse |
                                                     ImGuiWindowFlags_NoTitleBar;

UserInterface::UserInterface(gb::GameboyCore& core, DebuggerInterface& debugger)
    : window_{ sf::VideoMode{800, 600}, "GameboyCore Debugger" }
    , default_view_{core, debugger}
    , key_map_{}
{
    ImGui::SFML::Init(window_);

    // Init views
    views_.push_back(&default_view_);

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
    audio_stream_.initialize(core);
    audio_stream_.start();

    key_event_ = std::bind(&gb::GameboyCore::input, &core, std::placeholders::_1, std::placeholders::_2);

    ImGui::TabWindow::SetWindowContentDrawerCallback(&UserInterface::tabContentProvider);
}

void UserInterface::run()
{
    using namespace std::chrono_literals;

    while (isRunning())
    {
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
 
    renderViews();

    window_.clear(sf::Color{ 255, 255, 255, 255 });
    ImGui::SFML::Render(window_);

    window_.display();
}

void UserInterface::handleKeyEvent(sf::Keyboard::Key key, bool pressed)
{
    if (key_map_.find(key) != key_map_.end())
    {
        key_event_(key_map_[key], pressed);
    }
}

void UserInterface::renderViews()
{
    static bool open = true;

    const auto& window_size = ImGui::GetIO().DisplaySize;

    const auto width = window_size.x;
    const auto height = window_size.y;

    ImGui::SetNextWindowPos({ 0, 0 });
    ImGui::SetNextWindowSize({ width, height });

    if (ImGui::Begin("##TabWindow", &open, TAB_WINDOW_FLAGS))
    {
        static ImGui::TabWindow tab_window;
        if (!tab_window.isInited())
        {
            for (auto& view : views_)
            {
                tab_window.addTabLabel(view->name().c_str(), nullptr, false, false, view);
            }
        }

        tab_window.render();
    }

    ImGui::End();
}

void UserInterface::tabContentProvider(ImGui::TabWindow::TabLabel* tab, ImGui::TabWindow& parent, void* user_ptr)
{
    if (tab->userPtr != nullptr)
    {
        auto ptr = static_cast<View*>(tab->userPtr);
        ptr->render();
    }
}

bool UserInterface::isRunning() const
{
    return window_.isOpen();
}
