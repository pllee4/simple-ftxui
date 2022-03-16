// Copyright 2020 Arthur Sonzogni. All rights reserved.
// Use of this source code is governed by the MIT license that can be found in
// the LICENSE file.

#include <stddef.h>  // for size_t

#include <algorithm>  // for max
#include <string>     // for allocator, operator+
#include <thread>
#include <utility>  // for move
#include <vector>   // for vector

#include "ftxui/component/captured_mouse.hpp"  // for ftxui
#include "ftxui/component/component.hpp"       // for CatchEvent, Renderer
#include "ftxui/component/event.hpp"           // for Event
#include "ftxui/component/mouse.hpp"  // for Mouse, Mouse::Left, Mouse::Middle, Mouse::None, Mouse::Pressed, Mouse::Released, Mouse::Right, Mouse::WheelDown, Mouse::WheelUp
#include "ftxui/component/screen_interactive.hpp"  // for ScreenInteractive
#include "ftxui/dom/elements.hpp"  // for text, vbox, window, Element, Elements

using namespace ftxui;

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

class DrawKey {
 public:
  DrawKey() = default;

  void OnEvent(Event event) {
    if (event.character() == "i") {
      linear_ = 0.5;
    } else if (event.character() == "m") {
      linear_ = -0.5;
    }

    if (event.character() == "j") {
      angular_ = 0.3;  // left
      clear_angular_ = 0;
    } else if (event.character() == "l") {
      angular_ = -0.3;  // right
      clear_angular_ = 0;
    } else {
      if (clear_angular_++ > clear_angular_count_) {
        clear_angular_ = 0;
        angular_ = 0.0;
      }
    }

    if (event.character() == "k") {
      linear_ = 0.0;
      angular_ = 0.0;
    }
  }

  float GetAngular() const { return angular_; }

 private:
  float linear_{0.0};
  float angular_{0.0};
  uint16_t clear_angular_{0};
  static constexpr uint16_t clear_angular_count_{4};
};

int main(int argc, const char* argv[]) {
  auto screen = ScreenInteractive::TerminalOutput();

  std::vector<Event> keys;

  DrawKey drawkey;
  auto component = Renderer([&] {
    Elements children;
    for (size_t i = std::max(0, (int)keys.size() - 20); i < keys.size(); ++i) {
      drawkey.OnEvent(keys[i]);
    }

    Element angular_display = DoubleEndedHorizontalGauge(
        -0.3, 0, 0.3, drawkey.GetAngular(), Color::Yellow, Color::Red);

    children.push_back(angular_display);
    children.push_back(text(std::to_wstring(drawkey.GetAngular())));
    return window(text(L"keys"), vbox(std::move(children)));
  });

  component = CatchEvent(component, [&](Event event) {
    keys.push_back(event);
    return true;
  });

  screen.Loop(component);
}
