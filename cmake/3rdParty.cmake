# GLEW
find_package(GLEW REQUIRED PATHS "${PROJECT_SOURCE_DIR}/3rdParty/glew/lib/cmake")

# GLFW
find_package(glfw3 3.3 REQUIRED PATHS "${PROJECT_SOURCE_DIR}/3rdParty/glfw/lib/cmake")

# OpenGL
set(OpenGL_GL_PREFERENCE "LEGACY") # "GLVND" or "LEGACY"
find_package(OpenGL REQUIRED)
message(STATUS "OPENGL_LIBRARIES: ${OPENGL_LIBRARIES}")

# GLM
set(glm_DIR "${PROJECT_SOURCE_DIR}/3rdParty/glm/cmake/glm") # if necessary
find_package(glm REQUIRED)
message(STATUS "GLM_INCLUDE_DIRS: ${GLM_INCLUDE_DIRS}")