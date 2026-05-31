cmake_minimum_required(VERSION 4.2)
project(Yordan_Football_League_Manager)

set(CMAKE_CXX_STANDARD 20)

add_executable(Yordan_Football_League_Manager main.cpp
        League.cpp
        League.h
        Match.cpp
        Match.h
        PlayedMatch.cpp
        PlayedMatch.h
        ScheduledMatch.cpp
        ScheduledMatch.h
        Team.cpp
        Team.h
        FileManagement.h)
