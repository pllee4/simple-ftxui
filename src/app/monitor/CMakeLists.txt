add_executable(app_monitor ${CMAKE_CURRENT_SOURCE_DIR}/monitor.cpp)
target_link_libraries(app_monitor tui_component)
set_target_properties(app_monitor PROPERTIES CXX_STANDARD 17)