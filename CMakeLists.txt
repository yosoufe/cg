project( OpenGLPractices )

set(CMAKE_BUILD_TYPE Debug)

cmake_minimum_required( VERSION 3.6 )

include("cmake/cmake.cmake")
include("cmake/3rdParty.cmake")

set(MAIN_SOURCE_FILES 
    main.cpp
    Mesh.cpp
    Shader.cpp
    Window.cpp
    Camera.cpp
)

set(MAIN_HEADER_FILES
    Mesh.hpp
    Shader.hpp
    Window.hpp
    Camera.hpp
)

add_executable( main ${MAIN_SOURCE_FILES} )


target_link_libraries(main ${OPENGL_LIBRARIES} GLEW::GLEW glfw glm::glm)
