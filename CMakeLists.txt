cmake_minimum_required(VERSION 3.26.1)
project(TuringMachine)

include_directories (/usr/include/freetype2)

include(FetchContent)
FetchContent_Declare(SFML
        GIT_REPOSITORY https://github.com/SFML/SFML.git
        GIT_TAG 2.6.x)
FetchContent_MakeAvailable(SFML)

set(CMAKE_CXX_STANDARD 17)

add_executable(TuringMachine main.cpp
        Screen.h
        RoundedRectangle.cpp
        RoundedRectangle.h
        UltimateTable.cpp
        UltimateTable.h
        Button.cpp
        Button.h
        TextBox.cpp
        TuringMachine.cpp
        TuringMachine.h
)

target_link_libraries(TuringMachine PRIVATE sfml-graphics)