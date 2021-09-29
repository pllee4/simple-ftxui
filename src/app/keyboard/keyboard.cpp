// Copyright 2020 Arthur Sonzogni. All rights reserved.
// Use of this source code is governed by the MIT license that can be found in
// the LICENSE file.

#include <stddef.h>                                // for size_t
#include <algorithm>                               // for max
#include <ftxui/component/component.hpp>           // for Component
#include <ftxui/component/screen_interactive.hpp>  // for ScreenInteractive
#include <string>                                  // for allocator, operator+
#include <utility>                                 // for move
#include <vector>                                  // for vector

#include "ftxui/component/event.hpp"  // for Event
#include "ftxui/dom/elements.hpp"     // for text, vbox, window
#include "ftxui/screen/box.hpp"       // for ftxui

using namespace ftxui;

class DrawKey : public Component {
 public:
  ~DrawKey() override = default;

  Element Render() override {
    Elements children;
    for (size_t i = std::max(0, (int)keys.size() - 20); i < keys.size(); ++i) {
      if (keys[i] == Event::ArrowLeft) {
        children.push_back(text(L"Arrow Left"));
      }
      if (keys[i] == Event::ArrowRight) {
        children.push_back(text(L"Arrow Right"));  
      }
      if (keys[i] == Event::ArrowUp) {
        children.push_back(text(L"Arrow Up"));
      }
      if (keys[i] == Event::ArrowDown) {
        children.push_back(text(L"Arrow Down"));
      }
    }
    return window(text(L"keys"), vbox(std::move(children)));
  }

  bool OnEvent(Event event) override {
    keys.push_back(event);
    return true;
  }

 private:
  std::vector<Event> keys;
};

int main(int argc, const char* argv[]) {
  auto screen = ScreenInteractive::TerminalOutput();
  DrawKey draw_key;
  screen.Loop(&draw_key);
}
