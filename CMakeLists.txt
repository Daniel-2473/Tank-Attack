cmake_minimum_required(VERSION 3.28)
project(Tanquitos LANGUAGES CXX)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

include(FetchContent)
FetchContent_Declare(SFML
        GIT_REPOSITORY https://github.com/SFML/SFML.git
        GIT_TAG 3.1.0
        GIT_SHALLOW ON
        EXCLUDE_FROM_ALL
        SYSTEM)
FetchContent_MakeAvailable(SFML)

add_executable(Tanquitos src/main/main.cpp
        src/data_estructures/Queue.cpp
        src/data_estructures/Queue.h
        src/data_estructures/PriorityQueue.cpp
        src/data_estructures/PriorityQueue.h
        src/data_estructures/Nodo.h
        src/data_estructures/Nodo.cpp
        src/data_estructures/Grafo.cpp
        src/data_estructures/Grafo.h
        src/algorithms/BFS.h
        src/algorithms/BFS.cpp
)
target_compile_features(Tanquitos PRIVATE cxx_std_17)
target_link_libraries(Tanquitos PRIVATE SFML::Graphics)

set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT Tanquitos)