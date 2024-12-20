cmake_minimum_required(VERSION 3.10)
project(HolyBinaric)

# Specify the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Locate PortAudio
find_library(PORTAUDIO_LIBRARY NAMES portaudio portaudio_cpp)
find_path(PORTAUDIO_INCLUDE_DIR NAMES portaudio.h)

if (PORTAUDIO_LIBRARY AND PORTAUDIO_INCLUDE_DIR)
    message(STATUS "Found PortAudio: ${PORTAUDIO_LIBRARY}")
else()
    message(FATAL_ERROR "PortAudio not found! Install it or set PORTAUDIO_LIBRARY and PORTAUDIO_INCLUDE_DIR.")
endif()

# Add the executable
add_executable(holy_binaric src/main.cpp)

# Include directories and link library
target_include_directories(holy_binaric PRIVATE ${PORTAUDIO_INCLUDE_DIR})
target_link_libraries(holy_binaric PRIVATE ${PORTAUDIO_LIBRARY})
