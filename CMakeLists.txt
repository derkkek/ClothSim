set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
option(BUILD_SHARED_LIBS "Build shared libraries" OFF)

include(FetchContent)
FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 2.6.x)
FetchContent_MakeAvailable(SFML)

# Add Editor library
file(GLOB EDITOR_SOURCES "Editor/src/*.cpp" "Editor/src/*.h")
add_library(Editor STATIC ${EDITOR_SOURCES})
target_include_directories(Editor PUBLIC "Editor/src")

cmake_minimum_required(VERSION 3.16)
project(ClothSimulation LANGUAGES CXX)

add_executable(${PROJECT_NAME}
    src/main.cpp
    src/Particle.cpp
    src/Particle.h
    src/Arithmetic.cpp
    src/Arithmetic.h
    src/Line.h
    src/Line.cpp
    src/Cloth.cpp
    src/Cloth.h
    src/EventHandler.cpp
    src/EventHandler.h
    src/Application.cpp
    src/Application.h
    src/Renderer.cpp
    src/Renderer.h
)

target_include_directories(${PROJECT_NAME} PRIVATE "src" "Editor/src")
target_link_libraries(${PROJECT_NAME} PRIVATE sfml-graphics)
target_link_libraries(${PROJECT_NAME} PRIVATE Editor)
target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_17)

if(WIN32)
    add_custom_command(
        TARGET ${PROJECT_NAME}
        COMMENT "Copy OpenAL DLL"
        PRE_BUILD COMMAND ${CMAKE_COMMAND} -E copy ${SFML_SOURCE_DIR}/extlibs/bin/$<IF:$<EQUAL:${CMAKE_SIZEOF_VOID_P},8>,x64,x86>/openal32.dll $<TARGET_FILE_DIR:${PROJECT_NAME}>
        VERBATIM)
endif()