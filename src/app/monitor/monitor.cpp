/* 
 * monitor.cpp
 * Created on: May 30, 2021 17:25
 * Description: 
 * 
 * Copyright (c) 2021 Pin Loon Lee (pllee4)
 */ 
 
#include <iostream>
#include <thread>
#include <chrono>

#include "tui_component/window.hpp"
#include "ftxui/component/screen_interactive.hpp"

using namespace ftxui;
using namespace pllee4;

int main(int argc, const char* argv[]) {
  auto screen = ScreenInteractive::Fullscreen();
  bool refresh_ui_continue = true;
  Window main_window;

  std::thread refresh_ui([&] {
    while (refresh_ui_continue) {
      using namespace std::chrono_literals;
      std::this_thread::sleep_for(0.05s);
      main_window.UpdateTicks();
      screen.PostEvent(Event::Custom);
    }
  });

  screen.Loop(main_window.RenderComponent());
  refresh_ui_continue = false;
  refresh_ui.join();
  return 0;
}