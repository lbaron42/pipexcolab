cmake_minimum_required(VERSION 3.24)
project(pipexcolab C)

set(CMAKE_C_STANDARD 99)

add_executable(pipexutils.c Makefile pipex.h pipex.c)