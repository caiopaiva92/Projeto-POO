cmake_minimum_required(VERSION 3.16)

project(ProjetoPOO VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Biblioteca com as classes: todos os .cpp de src/, exceto o main.cpp
file(GLOB FONTES_LIB CONFIGURE_DEPENDS ${CMAKE_SOURCE_DIR}/src/*.cpp)
list(REMOVE_ITEM FONTES_LIB ${CMAKE_SOURCE_DIR}/src/main.cpp)

add_library(poo ${FONTES_LIB})
target_include_directories(poo PUBLIC ${CMAKE_SOURCE_DIR}/include)

# Portão de avisos da Unidade I, aplicado à biblioteca das classes
if(MSVC)
    target_compile_options(poo PRIVATE /W4 /WX)
else()
    target_compile_options(poo PRIVATE
        -Wall -Wextra -Wpedantic -Wshadow -Wold-style-cast -Wcast-align
        -Wconversion -Wsign-conversion -Wnon-virtual-dtor -Wdouble-promotion
        -Wformat=2 -Werror)
endif()

# Executável: só o main.cpp, ligado à biblioteca
add_executable(app ${CMAKE_SOURCE_DIR}/src/main.cpp)
target_link_libraries(app PRIVATE poo)