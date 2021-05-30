add_executable(app_starter ${CMAKE_CURRENT_SOURCE_DIR}/starter.cpp)
target_link_libraries(app_starter
  PUBLIC ftxui::screen
  PUBLIC ftxui::dom
  PUBLIC ftxui::component 
)
set_target_properties(app_starter PROPERTIES CXX_STANDARD 17)