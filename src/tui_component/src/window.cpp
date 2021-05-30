/* 
 * window.cpp
 * Created on: May 30, 2021 17:25
 * Description: 
 * 
 * Copyright (c) 2021 Pin Loon Lee (pllee4)
 */ 

#include "tui_component/window.hpp"

#include "ftxui/screen/string.hpp"

namespace pllee4 {
Window::Window() {
    Add(&main_container);
}

ftxui::Element Window::Render() {
    static float value = 0.0;
    static bool inversed = false;
    if (inversed) {
        value -= 0.1;
    } else {
        value += 0.1;
    }
    if (value >= 1.0) {
        inversed = true;
    } else if (value <= 0.0) {
        inversed = false;
    }
    ftxui::Element document = ftxui::hbox({
        ftxui::vbox({
            ftxui::text(L"Work in progress..."),
        }),
        ftxui::gauge(value) | ftxui::color(ftxui::Color::Green),   
    });
    return document | ftxui::border;
}

}
