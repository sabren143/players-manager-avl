cmake_minimum_required(VERSION 3.31)
project(Project)

set(CMAKE_CXX_STANDARD 20)

add_executable(Project main.cpp
        AVLTree.h
        PlayerNode.h
        GroupNode.h
        PlayersManager.h
        library.cpp
        library.h)
