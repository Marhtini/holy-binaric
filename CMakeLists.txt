cmake_minimum_required(VERSION 3.10)
project(HolyBinaric)

# Specify the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Find and link PortAudio
find_package(portaudio REQUIRED)

# Add the executable
add_executable(holy_binaric main.cpp)

# Link PortAudio to the executable
target_link_libraries(holy_binaric PRIVATE portaudio)
cmake_minimum_required(VERSION 3.10)
project(HolyBinaric)

# Specify the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Find and link PortAudio
find_package(portaudio REQUIRED)

# Add the executable
add_executable(holy_binaric src/main.cpp)

# Link PortAudio to the executable
target_link_libraries(holy_binaric PRIVATE portaudio)
