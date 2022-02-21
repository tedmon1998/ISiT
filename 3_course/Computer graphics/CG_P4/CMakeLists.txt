cmake_minimum_required(VERSION 3.20)
project(CG_P4)

set(CMAKE_CXX_STANDARD 17)

file(MAKE_DIRECTORY ${CMAKE_BINARY_DIR}/shaders)

configure_file(${CMAKE_SOURCE_DIR}/shaders/s1_frag.glsl ${CMAKE_BINARY_DIR}/shaders/s1_frag.glsl COPYONLY)
configure_file(${CMAKE_SOURCE_DIR}/shaders/s1_vert.glsl ${CMAKE_BINARY_DIR}/shaders/s1_vert.glsl COPYONLY)
configure_file(${CMAKE_SOURCE_DIR}/shaders/s2_frag.glsl ${CMAKE_BINARY_DIR}/shaders/s2_frag.glsl COPYONLY)
configure_file(${CMAKE_SOURCE_DIR}/shaders/s2_vert.glsl ${CMAKE_BINARY_DIR}/shaders/s2_vert.glsl COPYONLY)


file(MAKE_DIRECTORY ${CMAKE_BINARY_DIR}/models)
configure_file(${CMAKE_SOURCE_DIR}/models/Chest.obj ${CMAKE_BINARY_DIR}/models/Chest.obj COPYONLY)

#add_executable(CG_P4 old/main.cpp camera.h old/model.h old/shader.h old/mesh.h old/stb_image.cpp old/stb_image.h old/shader_m.h)
add_executable(CG_P4 main.cpp)
        if(UNIX AND NOT APPLE)
    message(STATUS "Linux")
    target_link_libraries(CG_P4 m glfw GLEW GL assimp)
else()
    message(STATUS "Windows")
    target_link_libraries(CG_P4 m glu32 opengl32 glfw3 glew32 assimp)
endif()
