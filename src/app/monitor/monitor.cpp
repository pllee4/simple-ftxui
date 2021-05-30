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

void TriggerRefresh(ScreenInteractive* screen) {
  while (true) {
    screen->PostEvent(Event::Custom);
    using namespace std::chrono_literals;
    std::this_thread::sleep_for(0.1s);
  }
}

int main(int argc, const char* argv[]) {
  auto screen = ScreenInteractive::Fullscreen();
  std::thread refresh_trigger_thread(TriggerRefresh, &screen);
  Window main_window;
  screen.Loop(&main_window);
  return 0;
}