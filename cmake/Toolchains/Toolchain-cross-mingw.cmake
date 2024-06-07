set(CMAKE_SYSTEM_NAME Windows)
set(CMAKE_SYSTEM_PROCESSOR x86_64)

# Specify the cross compiler prefix
set(CMAKE_C_COMPILER_TARGET x86_64-w64-mingw32)
set(CMAKE_C_COMPILER x86_64-w64-mingw32-gcc)
set(CMAKE_CXX_COMPILER x86_64-w64-mingw32-g++)
set(CMAKE_RC_COMPILER x86_64-w64-mingw32-windres)

# Set the CMake find mechanism to search for headers and libraries in the cross compiler's sysroot
set(CMAKE_FIND_ROOT_PATH /usr/x86_64-w64-mingw32)

# Tell CMake to not check the compiler identification
set(CMAKE_CROSSCOMPILING_EMULATOR "")

# Set the path to the cross compiler's bin directory
set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_PACKAGE ONLY)
