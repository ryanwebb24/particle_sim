cmake_minimum_required(VERSION 3.10)
project(ParticleSim)

# Use C++17
set(CMAKE_CXX_STANDARD 17)

# Include header files from 'include' folder
include_directories(include)

# Find SFML
find_package(SFML 3.0 COMPONENTS Graphics Window System REQUIRED)

# Add all source files from src/
file(GLOB SOURCES "src/*.cpp")

# Build the executable
add_executable(ParticleSim ${SOURCES})

# Link SFML libraries
target_link_libraries(ParticleSim sfml-graphics sfml-window sfml-system)
