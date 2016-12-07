
/**
	@author Natesh Narain <nnaraindev@gmail.com>
*/

#ifndef EMULATOR_WINDOW_H
#define EMULATOR_WINDOW_H

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

#include <gameboycore/tileram.h>

#include <stdexcept>
#include <string>

#include "screen_renderer.h"
#include "audio.h"

/**
	\brief Emulator Window
*/
class Window
{
public:
	Window(gb::GameboyCore& gameboy, const std::string& title) :
		window_(sf::VideoMode(160 * 2, 144 * 2), title),
		screen_renderer_(),
		joypad_(gameboy.getJoypad())
	{
		gameboy.getGPU()->setRenderCallback(
			std::bind(
				&ScreenRenderer::gpuCallback,
				&screen_renderer_,
				std::placeholders::_1, std::placeholders::_2
			)
		);

		gameboy.getAPU()->setAudioSampleCallback(
			std::bind(
				&Audio::apuCallback,
				&audio_,
				std::placeholders::_1, std::placeholders::_2
			)
		);
	}

	/**
		Start one off operations
	*/
	void start()
	{
		audio_.play();
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

		window_.clear(sf::Color(255, 0, 0, 255));
		screen_renderer_.draw(window_);
		window_.display();
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
	Audio audio_;

	gb::Joy::Ptr& joypad_;
};


#endif // EMULATOR_WINDOW_H
