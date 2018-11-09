#include "user_interface.hpp"
#include <imgui-SFML.h>
#include <imgui.h>

#include <functional>

UserInterface::UserInterface()
    : window_{ sf::VideoMode{800, 600}, "GameboyCore Debugger" }
    , screen_rect_{ {800, 600} }
{
    ImGui::SFML::Init(window_);

    if (!screen_texture_.create(framebuffer_.width(), framebuffer_.height()))
    {
        throw std::runtime_error("Could not create texture!");
    }

    screen_rect_.setTexture(&screen_texture_);
}

UserInterface::~UserInterface()
{
    ImGui::SFML::Shutdown();
}

void UserInterface::initialize(gb::GameboyCore& core)
{
    core.getGPU()->setRenderCallback(std::bind(&UserInterface::scanlineCallback, this, std::placeholders::_1, std::placeholders::_2));
    core.getGPU()->setVBlankCallback(std::bind(&UserInterface::vblankCallback, this));
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