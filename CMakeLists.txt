cmake_minimum_required(VERSION 3.20)

project(JellyFish)

set(CMAKE_CXX_STANDARD 20)

find_package(glfw3 CONFIG REQUIRED)
Find_package(glm CONFIG REQUIRED)
Find_package(glad CONFIG REQUIRED)

add_executable(JellyFish src/main.cpp)

target_include_directories(JellyFish PRIVATE include)

target_link_libraries(JellyFish PRIVATE glfw glm::glm glad::glad)