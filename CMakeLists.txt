cmake_minimum_required(VERSION 3.10)

# Project name
project(binpatcher C)

# Check if the target system is Windows
if(WIN32)
    message("Building for Windows")
else()
    message("Building for Linux/Unix")
endif()

# Set the C standard
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED True)

# Enable all compiler warnings
if (CMAKE_COMPILER_IS_GNUCC)
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wextra -pedantic")
endif()

# Add the executable
add_executable(binpatcher binpatcher.c)

# Install the binary
install(TARGETS binpatcher DESTINATION /usr/local/bin)
