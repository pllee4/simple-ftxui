// Copyright 2020 Arthur Sonzogni. All rights reserved.
// Use of this source code is governed by the MIT license that can be found in
// the LICENSE file.

#include <stddef.h>                                // for size_t
#include <algorithm>                               // for max
#include <ftxui/component/component.hpp>           // for Component
#include <ftxui/component/screen_interactive.hpp>  // for ScreenInteractive
#include <string>                                  // for allocator, operator+
#include <thread>
#include <utility>  // for move
#include <vector>   // for vector

#include "ftxui/component/event.hpp"  // for Event
#include "ftxui/dom/elements.hpp"     // for text, vbox, window
#include "ftxui/screen/box.hpp"       // for ftxui

using namespace ftxui;

void TriggerRefresh(ScreenInteractive* screen) {
  while (true) {
    screen->PostEvent(Event::Custom);
    using namespace std::chrono_literals;
    std::this_thread::sleep_for(0.1s);
  }
}

Element DoubleEndedHorizontalGauge(float min, float center, float max,
                                   float progress, Color left_color,
                                   Color right_color) {
  float left = float((std::min(center, std::max(min, progress)) - min)) /
               float(center - min);
  float right = float((std::min(max, std::max(center, progress)) - center)) /
                float(max - center);
  return hbox({gauge(left) | color(left_color) | inverted,
               gauge(right) | color(right_color)});
}

class DrawKey : public Component {
 public:
  ~DrawKey() override = default;

  Element Render() override {
    Elements children;

    Element angular_display = DoubleEndedHorizontalGauge(
        -0.3, 0, 0.3, angular_, Color::Yellow, Color::Red);

    children.push_back(angular_display);
    children.push_back(text(std::to_wstring(angular_)));
    return window(text(L"keys"), vbox(std::move(children)));
  }

  bool OnEvent(Event event) override {
    if (event.character() == 'i') {
      linear_ = 0.5;
    } else if (event.character() == 'm') {
      linear_ = -0.5;
    }

    if (event.character() == 'j') {
      angular_ = 0.3;  // left
      clear_angular_ = 0;
    } else if (event.character() == 'l') {
      angular_ = -0.3;  // right
      clear_angular_ = 0;
    } else {
      if (clear_angular_++ > clear_angular_count_) {
        clear_angular_ = 0;
        angular_ = 0.0;
      }
    }

    if (event.character() == 'k') {
      linear_ = 0.0;
      angular_ = 0.0;
    }

    return Component::OnEvent(event);
  }

 private:
  float angular_{0.0};
  float linear_{0.0};
  uint16_t clear_angular_{0};
  uint16_t clear_angular_count_{4};
};

int main(int argc, const char* argv[]) {
  auto screen = ScreenInteractive::TerminalOutput();

  std::thread refresh_trigger_thread(TriggerRefresh, &screen);

  DrawKey draw_key;
  screen.Loop(&draw_key);
}
