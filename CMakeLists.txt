cmake_minimum_required(VERSION 3.21.1)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_CXX_FLAGS "-lncurses -Wall -g")

# generate file required by clangd
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(SOURCE ${CMAKE_CURRENT_SOURCE_DIR}/src)
set(INCLUDE ${CMAKE_CURRENT_SOURCE_DIR}/include)
project(main)

# enable debugging symbols for gdb when compiling with clang
# https://stackoverflow.com/a/47045466
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -D_GLIBCXX_DEBUG")

add_executable(main ${SOURCE}/main.cpp  ${SOURCE}/player.cpp ${SOURCE}/board.cpp ${SOURCE}/food.cpp ${SOURCE}/snake.cpp)

target_include_directories(main $ENV{INCLUDE} PUBLIC ${INCLUDE} ${INCLUDE}/drawable)
