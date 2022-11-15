cmake_minimum_required(VERSION 3.5)
project(a-star)

set(CMAKE_CXX_STANDARD 11)

set(SRC_CPP
    src/main.cpp
    src/display.cpp
    src/astar.cpp
)

add_executable(${PROJECT_NAME}
        ${SRC_CPP}
        )

target_link_libraries(${PROJECT_NAME}
        SDL2
        SDL_image
        )
