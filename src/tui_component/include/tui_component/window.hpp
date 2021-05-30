/* 
 * window.hpp
 * Created on: May 30, 2021 17:24
 * Description: 
 * 
 * Copyright (c) 2021 Pin Loon Lee (pllee4)
 */ 
 
#ifndef WINDOW_HPP
#define WINDOW_HPP

#include "ftxui/component/component.hpp"
#include "ftxui/component/container.hpp"
#include "ftxui/dom/elements.hpp"

namespace pllee4 {
class Window: public ftxui::Component {
  public:
    Window();
    ftxui::Element Render() override;
  private:
  // ui elements
    ftxui::Container main_container = ftxui::Container::Horizontal();
};
} // namespace pllee4

#endif /* WINDOW_HPP */