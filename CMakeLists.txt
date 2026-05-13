cmake_minimum_required(VERSION 3.16)

project(QtTetrisPoc VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_DISABLE_FIND_PACKAGE_WrapVulkanHeaders TRUE)

if(WIN32 AND NOT DEFINED CMAKE_PREFIX_PATH)
    if(EXISTS "C:/Qt/6.11.0/mingw_64/lib/cmake")
        list(APPEND CMAKE_PREFIX_PATH "C:/Qt/6.11.0/mingw_64/lib/cmake")
    endif()
endif()

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)

add_executable(QtTetrisPoc
    qt-tetris-poc/src/main.cpp
    qt-tetris-poc/src/TetrisGridWidget.cpp
)

target_include_directories(QtTetrisPoc PRIVATE
    qt-tetris-poc/src
)

target_link_libraries(QtTetrisPoc PRIVATE
    Qt${QT_VERSION_MAJOR}::Widgets
)

add_custom_target(poc_build_and_run
    COMMAND $<TARGET_FILE:QtTetrisPoc>
    DEPENDS QtTetrisPoc
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
    USES_TERMINAL
)

add_library(QtTetrisCore STATIC
    qt-tetris/src/model/Board.cpp
    qt-tetris/src/model/GameState.cpp
    qt-tetris/src/model/Tetromino.cpp
)

target_include_directories(QtTetrisCore PUBLIC
    qt-tetris/src
)

add_executable(QtTetris
    qt-tetris/src/main.cpp
    qt-tetris/src/TetrisGridWidget.cpp
    qt-tetris/src/TetrisRenderer.cpp
    qt-tetris/src/TetrisController.cpp
)

target_include_directories(QtTetris PRIVATE
    qt-tetris/src
)

target_link_libraries(QtTetris PRIVATE
    Qt${QT_VERSION_MAJOR}::Widgets
    QtTetrisCore
)

add_custom_target(core_build_and_run
    COMMAND $<TARGET_FILE:QtTetris>
    DEPENDS QtTetris
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
    USES_TERMINAL
)
