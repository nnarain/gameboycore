#include "user_interface.hpp"
#include <imgui-SFML.h>
#include <imgui.h>

#include <functional>


UserInterface::UserInterface()
    : window_{ sf::VideoMode{800, 600}, "GameboyCore Debugger" }
    , screen_rect_{ {800, 600} }
    , key_map_{}
{
    ImGui::SFML::Init(window_);

    if (!screen_texture_.create(framebuffer_.width(), framebuffer_.height()))
    {
        throw std::runtime_error("Could not create texture!");
    }

    screen_rect_.setTexture(&screen_texture_);

    // key mapping
    key_map_.insert({ sf::Keyboard::Key::W, gb::Joy::Key::UP });
    key_map_.insert({ sf::Keyboard::Key::S, gb::Joy::Key::DOWN });
    key_map_.insert({ sf::Keyboard::Key::A, gb::Joy::Key::LEFT });
    key_map_.insert({ sf::Keyboard::Key::D, gb::Joy::Key::RIGHT });
    key_map_.insert({ sf::Keyboard::Key::J, gb::Joy::Key::A });
    key_map_.insert({ sf::Keyboard::Key::K, gb::Joy::Key::B });
    key_map_.insert({ sf::Keyboard::Key::Return, gb::Joy::Key::START });
    key_map_.insert({ sf::Keyboard::Key::LShift, gb::Joy::Key::SELECT });
}

UserInterface::~UserInterface()
{
    audio_stream_.stop();
    ImGui::SFML::Shutdown();
}

void UserInterface::initialize(gb::GameboyCore& core)
{
    core.getGPU()->setRenderCallback(std::bind(&UserInterface::scanlineCallback, this, std::placeholders::_1, std::placeholders::_2));
    core.getGPU()->setVBlankCallback(std::bind(&UserInterface::vblankCallback, this));

    audio_stream_.initialize(core);
    audio_stream_.start();

    key_press_ = std::bind(&gb::Joy::press, core.getJoypad().get(), std::placeholders::_1);
    key_release_ = std::bind(&gb::Joy::release, core.getJoypad().get(), std::placeholders::_1);
}

void UserInterface::update()
{
    sf::Event event;

    while (window_.pollEvent(event))
    {
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
            handleKeyPress(event.key.code);
            break;
        case sf::Event::KeyReleased:
            handleKeyRelease(event.key.code);
            break;
        default:
            break;
        }
    }

    //ImGui::SFML::Update(window_, delta_clock_.restart());

    window_.clear(sf::Color{ 0, 0, 0, 255 });

    window_.draw(screen_rect_);

    //ImGui::SFML::Render(window_);

    window_.display();
}


void UserInterface::handleKeyPress(sf::Keyboard::Key key)
{
    if (key_map_.find(key) != key_map_.end())
    {
        key_press_(key_map_[key]);
    }
}

void UserInterface::handleKeyRelease(sf::Keyboard::Key key)
{
    if (key_map_.find(key) != key_map_.end())
    {
        key_release_(key_map_[key]);
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