find_package(GLEW REQUIRED PATHS "${PROJECT_SOURCE_DIR}/3rdParty/glew/lib/cmake")
if (GLEW_FOUND)
    include_directories(${GLEW_INCLUDE_DIRS})
    link_libraries(${GLEW_LIBRARIES})
endif()

find_package(glfw3 3.3 REQUIRED PATHS "${PROJECT_SOURCE_DIR}/3rdParty/glfw/lib/cmake")
