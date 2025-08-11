cmake_minimum_required(VERSION 3.16)
project(ClothSimulation LANGUAGES CXX)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
option(BUILD_SHARED_LIBS "Build shared libraries" OFF)

# Fetch SFML
include(FetchContent)
FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 2.6.x)
FetchContent_MakeAvailable(SFML)

FetchContent_Declare(nlohmann_json
    GIT_REPOSITORY https://github.com/nlohmann/json.git
    GIT_TAG v3.11.3)

FetchContent_MakeAvailable(SFML nlohmann_json)

# Add ImGui
file(GLOB IMGUI_SRC "Editor/vendor/imgui/*.cpp")
add_library(imgui STATIC ${IMGUI_SRC})
target_include_directories(imgui PUBLIC "Editor/vendor/imgui")

# Add ImGui-SFML
set(IMGUI_DIR "${CMAKE_SOURCE_DIR}/Editor/vendor/imgui")
set(IMGUI_SFML_FIND_SFML OFF)
add_subdirectory(Editor/vendor/imgui-sfml)

# Add Editor executable
file(GLOB EDITOR_SOURCES "Editor/src/*.cpp" "Editor/src/*.h")
add_executable(EditorApp ${EDITOR_SOURCES})
target_include_directories(EditorApp PRIVATE "Editor/src" "Editor/vendor/imgui" "Editor/vendor/imgui-sfml" "src")
target_link_libraries(EditorApp PRIVATE imgui ImGui-SFML::ImGui-SFML sfml-graphics sfml-window sfml-system)

# Main application as static library
add_library(Simulation STATIC
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
    src/IScene.cpp
    src/IScene.h
    src/EmptyScene.cpp
    src/EmptyScene.h
    src/SaveManager.cpp
    src/SaveManager.h
    src/Triangle.h
    src/Triangle.cpp
)

target_include_directories(Simulation PUBLIC "src" "Editor/src" "Editor/vendor/imgui")
target_compile_features(Simulation PUBLIC cxx_std_17)

target_link_libraries(Simulation PUBLIC sfml-graphics sfml-window sfml-system nlohmann_json::nlohmann_json)
target_link_libraries(EditorApp PRIVATE Simulation)
