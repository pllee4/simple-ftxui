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

class DrawKey : public Component {
 public:
  ~DrawKey() override = default;

  Element Render() override {
    Elements children;

    float left_min = -0.3;
    float left_max = 0;
    float left_angular =
        float((std::min(left_max, std::max(left_min, angular_)) - left_min)) /
        float(left_max - left_min);

    float right_min = 0;
    float right_max = 0.3;

    float right_angular =
        float(
            (std::min(right_max, std::max(right_min, angular_)) - right_min)) /
        float(right_max - right_min);

    Element angular_display =
        hbox({gauge(left_angular) | color(Color::Yellow) | ftxui::inverted,
              gauge(right_angular) | color(Color::Red)});

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
