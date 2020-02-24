cmake_minimum_required(VERSION 3.10)

# set the project name
project(VCM C)

add_compile_options(
  "-Wall" "-Wpedantic" "-Wextra" "-fexceptions"
  "-O0" "-g3" "-ggdb"
)


find_package(SDL2 REQUIRED)

# header files & SDL
include_directories(HEAD)
include_directories(${SDL2_INCLUDE_DIRS})


# source files
file(GLOB SOURCES "SRC/*.c")

# add the executable
add_executable(VCM ${SOURCES})
target_link_libraries(VCM ${SDL2_LIBRARIES})
