cmake_minimum_required(VERSION 3.20)
project("yumiLang" LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 26)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(${PROJECT_NAME} yumi/main.cpp yumi/ylex.cpp)
