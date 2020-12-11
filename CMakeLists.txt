project( OpenGLPractices )

set(CMAKE_BUILD_TYPE Debug)

cmake_minimum_required( VERSION 3.6 )

include("cmake/cmake.cmake")
include("cmake/opengl.cmake")



add_executable( main main.cpp )


target_link_libraries(main ${OPENGL_LIBRARIES} GLEW::GLEW glfw)
