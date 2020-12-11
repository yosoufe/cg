find_package(GLEW REQUIRED PATHS "${PROJECT_SOURCE_DIR}/3rdParty/glew/lib/cmake")
if (GLEW_FOUND)
    include_directories(${GLEW_INCLUDE_DIRS})
    # link_libraries(${GLEW_LIBRARIES})
endif()

find_package(glfw3 3.3 REQUIRED PATHS "${PROJECT_SOURCE_DIR}/3rdParty/glfw/lib/cmake")
if(glfw3_FOUND)
    include_directories(${GLFW_INCLUDE_DIRS})
endif()


set(OpenGL_GL_PREFERENCE "LEGACY") # "GLVND" or "LEGACY"
find_package(OpenGL REQUIRED)
message("OPENGL_LIBRARIES: ${OPENGL_LIBRARIES}")
include_directories(${OPENGL_INCLUDE_DIRS})