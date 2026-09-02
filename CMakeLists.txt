cmake_minimum_required(VERSION 3.16)
project(APOSMusicPlayer)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt6 REQUIRED COMPONENTS Widgets Multimedia)

add_executable(APOSMusicPlayer
    main.cpp
    mainwindow.cpp
    mainwindow.h
    songmodel.cpp
    songmodel.h
    musicscanner.cpp
    musicscanner.h
    song.h
    musicplayer.cpp
    musicplayer.h
    songdelegate.cpp
    songdelegate.h
    nowplayingwidget.cpp
    nowplayingwidget.h
)

target_link_libraries(APOSMusicPlayer PRIVATE Qt6::Widgets Qt6::Multimedia)
