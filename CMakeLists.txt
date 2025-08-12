# Minimum CMake version required
cmake_minimum_required(VERSION 3.10)

# Name of your project
project(strands)

# This is the magic line that creates compile_commands.json
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Create an executable named 'my_app' from main.cpp
add_executable(strands src/main.cpp)

# Tell the target where to find its header files.
# This adds the 'src' directory to the include path.
target_include_directories(strands PRIVATE ${CMAKE_PROJECT_SOURCE_DIR}/src)
