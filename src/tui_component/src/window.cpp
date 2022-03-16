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
ftxui::Component Window::RenderComponent() {
  auto main_renderer = ftxui::Renderer(main_container_, [&] {
    float progress = ticks_ % 100 / 100.f;
    return ftxui::hbox({
        ftxui::vbox({
            ftxui::text(L"Work in progress..."),
        }),
        ftxui::gauge(progress) | ftxui::color(ftxui::Color::Green),
    });
  });
  return main_renderer;
}
}  // namespace pllee4
