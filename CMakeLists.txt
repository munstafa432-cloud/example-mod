cmake_minimum_required(VERSION 3.21)
project(Enz7y-Menu)

# This line is what is failing for you right now
find_package(Geode REQUIRED)

# This sets up the Geode targets and mod.json parsing
setup_geode_mod(Enz7y-Menu)

# Add your source files here
target_sources(${PROJECT_NAME} PRIVATE
    src/EchoMenu.hpp
    src/EchoMenu.cpp
    src/Pause menu hook.cpp
)
