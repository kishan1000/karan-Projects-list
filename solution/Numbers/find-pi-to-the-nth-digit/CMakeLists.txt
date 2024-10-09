cmake_minimum_required(VERSION 3.10)  # Minimum version of CMake required

project(find-pi-to-the-nth-digit) # project name (optional version)

set(CMAKE_CXX_STANDARD 17) # setting which c++ std to use
set(CMAKE_CXX_STANDARD_REQUIRED True)

# find_package(GMP REQUIRED) # find the GMP library and if not found through error
# Manually specify the GMP include and library paths
set(GMP_INCLUDE_DIR "/usr/local/include")
set(GMP_LIB_DIR "/usr/local/lib")

include_directories(${GMP_INCLUDE_DIRS} ${CMAKE_SOURCE_DIR}/include) # including directories for .h and .hpp

# Link GMP library directory
link_directories(${GMP_LIB_DIR})

# Find the GMP and GMPXX libraries manually
find_library(GMP_LIBRARY gmp HINTS ${GMP_LIB_DIR})
find_library(GMPXX_LIBRARY gmpxx HINTS ${GMP_LIB_DIR})

file(GLOB SOURCES "src/*.cpp") # adding source files to SOURCES variable

add_executable(main ${SOURCES}) # adding name of executable and .cpp files

target_link_libraries(main ${GMP_LIBRARY} ${GMPXX_LIBRARY})