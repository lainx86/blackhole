cmake_minimum_required(VERSION 3.16)

project(blackhole_mono_particles
    VERSION 0.1.0
    LANGUAGES C CXX
)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

find_package(OpenGL REQUIRED)
find_package(glfw3 QUIET)
find_package(glm QUIET)

if(NOT TARGET glfw)
    find_package(PkgConfig REQUIRED)
    pkg_check_modules(GLFW3 REQUIRED IMPORTED_TARGET glfw3)
endif()

add_library(glad STATIC
    external/glad/src/glad.c
)
target_include_directories(glad PUBLIC
    external/glad/include
)

add_executable(blackhole_mono_particles
    src/main.cpp
    src/Shader.cpp
    src/Camera.cpp
    src/ParticleSystem.cpp
    src/Grid.cpp
    src/BlackHole.cpp
    src/Framebuffer.cpp
)

target_include_directories(blackhole_mono_particles PRIVATE
    src
)

target_compile_definitions(blackhole_mono_particles PRIVATE
    BLACKHOLE_SHADER_DIR="${CMAKE_CURRENT_SOURCE_DIR}/assets/shaders"
)

target_link_libraries(blackhole_mono_particles PRIVATE
    glad
    OpenGL::GL
)

if(TARGET glfw)
    target_link_libraries(blackhole_mono_particles PRIVATE glfw)
else()
    target_link_libraries(blackhole_mono_particles PRIVATE PkgConfig::GLFW3)
endif()

if(TARGET glm::glm)
    target_link_libraries(blackhole_mono_particles PRIVATE glm::glm)
else()
    message(STATUS "glm CMake target not found; assuming GLM headers are available on the compiler include path.")
endif()

if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    target_compile_options(blackhole_mono_particles PRIVATE -Wall -Wextra -Wpedantic)
endif()
