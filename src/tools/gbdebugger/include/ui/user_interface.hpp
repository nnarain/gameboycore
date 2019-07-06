#pragma once

#include "ui/audio_stream.hpp"
#include "ui/views/view.hpp"
#include "ui/views/default_view.hpp"
#include "ui/views/memory_view.hpp"

#include "debugger/debugger_interface.hpp"

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

#include <addons/imguitabwindow/imguitabwindow.h>

#include <gameboycore/gameboycore.h>

#include <map>
#include <vector>
#include <functional>


class UserInterface
{
public:
    UserInterface(gb::GameboyCore& core, DebuggerInterface& debugger);
    ~UserInterface();

    void run();

private:
    void initialize(gb::GameboyCore& core);
    void update();
    bool isRunning() const;

    void renderViews();

    static void tabContentProvider(ImGui::TabWindow::TabLabel* tab, ImGui::TabWindow& parent, void* user_ptr);

    void handleKeyEvent(sf::Keyboard::Key key, bool pressed);

    sf::RenderWindow window_;
    sf::Clock delta_clock_;

    std::vector<View*> views_;
    DefaultView default_view_;
    MemoryView memory_view_;

    AudioStream audio_stream_;

    std::map<sf::Keyboard::Key, gb::Joy::Key> key_map_;
    std::function<void(gb::Joy::Key, bool)> key_event_;
};