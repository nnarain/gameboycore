
/**
	@author Natesh Narain <nnaraindev@gmail.com>
*/

#ifndef EMULATOR_WINDOW_H
#define EMULATOR_WINDOW_H

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

#include "imgui.h"
#include "imgui-SFML.h"

#include "screen_renderer.h"
#include "audio.h"

#include <stdexcept>
#include <string>
#include <iostream>

/**
	\brief Emulator Window
*/
class Window
{
public:
	Window(gb::GameboyCore& gameboy, const std::string& title) :
		window_(sf::VideoMode(160 * 2, 144 * 2), title),
		screen_renderer_(),
		core_(gameboy),
		joypad_(gameboy.getJoypad()),
		screen_hash_overlay_(false)
	{
		ImGui::SFML::Init(window_);

		gameboy.getGPU()->setRenderCallback(
			std::bind(
				&ScreenRenderer::gpuCallback,
				&screen_renderer_,
				std::placeholders::_1, std::placeholders::_2
			)
		);
	}

	/**
		Start one off operations
	*/
	void start()
	{
	//	audio_.play();
	}

	void update()
	{
		// pump event loop
		sf::Event event;
		
		while (window_.pollEvent(event))
		{
			switch (event.type)
			{
			case sf::Event::Closed:
				window_.close();
				break;
			case sf::Event::Resized:
				break;
			case sf::Event::LostFocus:
				break;
			case sf::Event::GainedFocus:
				break;
			case sf::Event::TextEntered:
				break;
			case sf::Event::KeyPressed:
				handleKeyPressed(event.key.code);
				break;
			case sf::Event::KeyReleased:
				handleKeyReleased(event.key.code);
				break;
			case sf::Event::MouseWheelMoved:
				break;
			case sf::Event::MouseButtonPressed:
				break;
			case sf::Event::MouseButtonReleased:
				break;
			case sf::Event::MouseMoved:
				break;
			case sf::Event::MouseEntered:
				break;
			case sf::Event::MouseLeft:
				break;
			case sf::Event::JoystickButtonPressed:
				break;
			case sf::Event::JoystickButtonReleased:
				break;
			case sf::Event::JoystickMoved:
				break;
			case sf::Event::JoystickConnected:
				break;
			case sf::Event::JoystickDisconnected:
				break;
			case sf::Event::Count:
				std::runtime_error("Invalid event type");
				break;
			}
		}

		ImGui::SFML::Update(window_, deltaClock_.restart());
		drawGui();

		window_.clear(sf::Color(255, 255, 255, 255));
		screen_renderer_.draw(window_);
		ImGui::SFML::Render(window_);
		window_.display();
	}

	void drawGui()
	{
		drawMenu();

		if (screen_hash_overlay_)
		{
			drawScreenHashOverlay();
		}
	}

	void drawMenu()
	{
		if (ImGui::BeginMainMenuBar())
		{
			main_menu_height_ = ImGui::GetWindowHeight();
			screen_renderer_.setDrawRectY(main_menu_height_);

			if (ImGui::BeginMenu("Debug"))
			{
				if (ImGui::MenuItem("CPU Registers"))
				{
					
				}

				ImGui::MenuItem("Screen Hash", NULL, &screen_hash_overlay_);

				ImGui::EndMenu();
			}

			ImGui::EndMainMenuBar();
		}
	}

	/**
		Draw the current background map hash
	*/
	void drawScreenHashOverlay()
	{
		int window_flags = ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoSavedSettings;
		ImGui::SetNextWindowPos(ImVec2(0, main_menu_height_));

		if (ImGui::Begin("ScreenHash", NULL, window_flags))
		{
			ImGui::Text("Screen Hash: %X", core_.getGPU()->getBackgroundHash());

			ImGui::End();
		}
	}

	bool isOpen()
	{
		return window_.isOpen();
	}

	~Window()
	{
	}

private:

	void handleKeyPressed(sf::Keyboard::Key key)
	{
		switch (key)
		{
		case sf::Keyboard::Key::W:
			joypad_->press(gb::Joy::Key::UP);
			break;
		case sf::Keyboard::Key::A:
			joypad_->press(gb::Joy::Key::LEFT);
			break;
		case sf::Keyboard::Key::D:
			joypad_->press(gb::Joy::Key::RIGHT);
			break;
		case sf::Keyboard::Key::S:
			joypad_->press(gb::Joy::Key::DOWN);
			break;

		case sf::Keyboard::RShift:
			joypad_->press(gb::Joy::Key::SELECT);
			break;
		case sf::Keyboard::Return:
			joypad_->press(gb::Joy::Key::START);
			break;

		case sf::Keyboard::J:
			joypad_->press(gb::Joy::Key::A);
			break;
		case sf::Keyboard::K:
			joypad_->press(gb::Joy::Key::B);
			break;

		default:
			break;
		}
	}

	void handleKeyReleased(sf::Keyboard::Key key)
	{
		switch (key)
		{
		case sf::Keyboard::Key::W:
			joypad_->release(gb::Joy::Key::UP);
			break;
		case sf::Keyboard::Key::A:
			joypad_->release(gb::Joy::Key::LEFT);
			break;
		case sf::Keyboard::Key::D:
			joypad_->release(gb::Joy::Key::RIGHT);
			break;
		case sf::Keyboard::Key::S:
			joypad_->release(gb::Joy::Key::DOWN);
			break;

		case sf::Keyboard::RShift:
			joypad_->release(gb::Joy::Key::SELECT);
			break;
		case sf::Keyboard::Return:
			joypad_->release(gb::Joy::Key::START);
			break;

		case sf::Keyboard::J:
			joypad_->release(gb::Joy::Key::A);
			break;
		case sf::Keyboard::K:
			joypad_->release(gb::Joy::Key::B);
			break;

		default:
			break;
		}
	}

private:
	sf::RenderWindow window_;
	ScreenRenderer screen_renderer_;

	sf::Clock deltaClock_;

	gb::GameboyCore& core_;
	gb::Joy::Ptr& joypad_;

	// GUI elements
	float main_menu_height_;
	bool screen_hash_overlay_;
};


#endif // EMULATOR_WINDOW_H
