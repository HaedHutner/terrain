cmake_minimum_required(VERSION 3.12)
project(imgui CXX)

add_library(${PROJECT_NAME})
target_sources(${PROJECT_NAME}
    PRIVATE
   "${CMAKE_CURRENT_SOURCE_DIR}/imgui/imconfig.h"
   "${CMAKE_CURRENT_SOURCE_DIR}/imgui/imgui.cpp"
   "${CMAKE_CURRENT_SOURCE_DIR}/imgui/imgui.h"
   "${CMAKE_CURRENT_SOURCE_DIR}/imgui/imgui_demo.cpp"
   "${CMAKE_CURRENT_SOURCE_DIR}/imgui/imgui_draw.cpp"
   "${CMAKE_CURRENT_SOURCE_DIR}/imgui/imgui_internal.h"
   "${CMAKE_CURRENT_SOURCE_DIR}/imgui/imgui_widgets.cpp"
   "${CMAKE_CURRENT_SOURCE_DIR}/imgui/imstb_textedit.h"
   "${CMAKE_CURRENT_SOURCE_DIR}/imgui/imstb_truetype.h"
)

target_include_directories(${PROJECT_NAME} PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/imgui")