cmake_minimum_required(VERSION 3.16)

project(ProjetoPOO VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Todos os .cpp de src/ entram no executável
file(GLOB_RECURSE FONTES CONFIGURE_DEPENDS ${CMAKE_SOURCE_DIR}/src/*.cpp)

add_executable(app ${FONTES})
target_include_directories(app PRIVATE ${CMAKE_SOURCE_DIR}/include)

if(MSVC)
    target_compile_options(app PRIVATE /W4)
else()
    target_compile_options(app PRIVATE -Wall -Wextra -Wpedantic)
endif()