cmake_minimum_required (VERSION 2.6)
project (opengl_dod)

add_compile_options(
  "-g" "-Wall" 
)

include_directories(include)
file(GLOB SOURCES "src/*.cpp")

add_executable(build/opengl-dod.out ${SOURCES})

find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)
include_directories( ${OPENGL_INCLUDE_DIRS}  ${GLUT_INCLUDE_DIRS} )

find_package(GLEW REQUIRED)
include_directories(${GLEW_INCLUDE_DIRS})

target_link_libraries(build/opengl-dod.out ${OPENGL_LIBRARIES} ${GLEW_LIBRARIES} ${GLUT_LIBRARY})