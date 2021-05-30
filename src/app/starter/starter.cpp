#include <thread>
#include <chrono>
#include <iostream>

#include "ftxui/dom/elements.hpp"
#include "ftxui/screen/screen.hpp"
#include "ftxui/screen/string.hpp"
 #include "ftxui/component/screen_interactive.hpp"

using namespace ftxui;

int main(void) {

  auto vertical_box = [&] {
    auto content = vbox({
        hbox({text(L"- 1st item: "), text(L"1") | bold}) | color(Color::Green),
        hbox({text(L"- 2nd item: "), text(L"2") | bold}) | color(Color::YellowLight),
        hbox({text(L"- 3rd item: "), text(L"3") | bold}) | color(Color::BlueLight),
    });
    return window(text(L" Vertical Box "), content);
  };

  auto horizontal_box = [&] {
    auto content = vbox({
        vbox({text(L"1st item: "), text(L"- 1") | bold}) | color(Color::Green),
        vbox({text(L"2nd item: "), text(L"- 2") | bold}) | color(Color::YellowLight),
        vbox({text(L"3rd item: "), text(L"- 3") | bold}) | color(Color::BlueLight),
    });
    return window(text(L" Horizontal Box "), content);
  };

  Element display =  //
      vbox({
          text(L"Welcome to starter app!") | hcenter | color(Color:: White) |  bgcolor(Color::Cyan),
          filler(),
          separator(),
          hbox({
              vertical_box(),
              horizontal_box()
          }),
          vertical_box(),
          horizontal_box(),
      });

  // Limit the size of the document to 80 char.
  display = display | size(WIDTH, LESS_THAN, 80);

  auto screen = Screen::Create(Dimension::Full(), Dimension::Fit(display));
  Render(screen, display);

  std::cout << screen.ToString() << std::endl;

  return EXIT_SUCCESS;
}
