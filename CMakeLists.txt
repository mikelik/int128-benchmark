# stop if cmake version is below 3.0
cmake_minimum_required(VERSION 3.0 FATAL_ERROR)

# project name and enable C++ support
project(int128-benchmark LANGUAGES CXX)
find_package(benchmark REQUIRED)
add_subdirectory(abseil-cpp)
add_subdirectory(intx)

# require C++11
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# we define the executable
add_executable(int128-benchmark "")

target_include_directories(int128-benchmark PUBLIC "intx/include")
target_link_libraries(int128-benchmark benchmark::benchmark absl::int128)

# and its sources
target_sources(
  int128-benchmark
  PRIVATE
    main.cpp
  )

add_executable(hex-benchmark "")
target_link_libraries(hex-benchmark benchmark::benchmark)

# and its sources
target_sources(
  hex-benchmark
  PRIVATE
    hex.cpp
  )
