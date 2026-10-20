/cmake_minimum_required(VERSION 3.21)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_VISIBILITY_PRESET hidden)

project(Enz7y-Menu)

# Collect all source files
file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS src/*.cpp)
add_library(${PROJECT_NAME} SHARED ${SOURCES})

# Verify the Geode SDK is available
if (NOT DEFINED ENV{GEODE_SDK})
    message(FATAL_ERROR "Unable to find Geode SDK! Please define GEODE_SDK environment variable")
else()
    message(STATUS "Found Geode: $ENV{GEODE_SDK}")
endif()

# Add the Geode SDK
add_subdirectory($ENV{GEODE_SDK} ${CMAKE_CURRENT_BINARY_DIR}/geode)
setup_geode_mod(${PROJECT_NAME})

# Fetch gd-imgui-cocos using CPM
CPMAddPackage("gh:matcool/gd-imgui-cocos#main") # Using 'main' branch; you can pin a specific commit hash

# Link the imgui-cocos library to your mod
target_link_libraries(${PROJECT_NAME} imgui-cocos)
