cmake_minimum_required(VERSION 3.16)
project(strands LANGUAGES CXX)

# Set C++20
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)
FetchContent_Declare(ftxui
  GIT_REPOSITORY https://github.com/ArthurSonzogni/ftxui
  GIT_TAG v6.1.9
)
FetchContent_MakeAvailable(ftxui)

# Add include directory for headers
include_directories(src)

# Recursively find all .cpp files in src/
file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS src/*.cpp)

# Create the executable
add_executable(main ${SOURCES})

target_link_libraries(main PRIVATE
    # Chose a submodule
    ftxui::component
    ftxui::dom
    ftxui::screen
)
