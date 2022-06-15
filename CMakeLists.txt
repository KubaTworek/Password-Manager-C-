cmake_minimum_required(VERSION 3.21)
project(PasswordManager)

set(CMAKE_CXX_STANDARD 14)

add_executable(PasswordManager main.cpp Password.cpp Password.h PasswordManager.cpp PasswordManager.h CategoryManager.cpp CategoryManager.h)
