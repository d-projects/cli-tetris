cmake_minimum_required(VERSION 3.22.1)

project (cli_tetris)

set(SOURCES
    src/Block.cc
    src/Board.cc
    src/Command.cc
    src/GameController.cc
    src/LevelStrategy.cc
    src/TextView.cc
    src/View.cc
    src/main.cc
)

add_executable(${PROJECT_NAME} ${SOURCES})

target_include_directories(${PROJECT_NAME}
    PRIVATE 
        ${PROJECT_SOURCE_DIR}/include
)