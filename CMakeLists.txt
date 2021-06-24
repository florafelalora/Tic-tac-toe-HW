cmake_minimum_required(VERSION 3.17)
project(amoba C)

set(CMAKE_C_STANDARD 11)

add_executable(amoba main.c amoba.c amoba.h ai.c ai.h game.c game.h)