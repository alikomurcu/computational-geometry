cmake_minimum_required(VERSION 3.10)

# Set the project name
project(SutherlandHodgman)

# Add the executable
add_executable(SutherlandHodgman src/sutherland_hodgman.cpp)

# Include directories
target_include_directories(SutherlandHodgman PRIVATE src)