cmake_minimum_required(VERSION 3.10)

# set the project name
project(VCM C)

add_compile_options(
  "-Wall" "-fexceptions"
  "-O0" "-g3" "-ggdb"
)

# header files
include_directories(include)


# source files
file(GLOB SOURCES "src/*.c")

# add the executable
add_executable(VCM ${SOURCES})
