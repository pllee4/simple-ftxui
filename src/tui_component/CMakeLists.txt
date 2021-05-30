add_library(tui_component src/window.cpp)
target_link_libraries(tui_component PUBLIC
ftxui::screen
ftxui::dom
ftxui::component)
target_include_directories(tui_component PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
    PRIVATE src)