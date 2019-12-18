cmake_minimum_required(VERSION 3.12)

project(terrain)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_subdirectory("external/stb")
add_subdirectory("external/fastnoise")
add_subdirectory("external/glad")
add_subdirectory("external/glfw")
add_subdirectory("external/glm")
add_subdirectory("external/imgui")

file(GLOB_RECURSE HEADERS ./include/*.h)
file(GLOB_RECURSE SOURCES ./src/*.cpp)

add_executable(
    ${PROJECT_NAME}
    ${HEADERS}
    ${SOURCES}
)

target_include_directories(${PROJECT_NAME} PUBLIC ./include)

target_link_libraries(${PROJECT_NAME} PUBLIC glad glm glfw fastnoise stb imgui)

add_custom_command(
	TARGET ${PROJECT_NAME} PRE_BUILD 
	COMMAND ${CMAKE_COMMAND} -E copy_directory 
			${CMAKE_CURRENT_SOURCE_DIR}/data 
			${CMAKE_CURRENT_BINARY_DIR}/data
)