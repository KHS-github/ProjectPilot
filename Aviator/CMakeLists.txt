
find_package(PkgConfig)
find_package(OpenGL)
find_package(X11)
pkg_search_module(GLFW glfw3)
include_directories(${X11_INCLUDE_DIRS} ${GLFW_INCLUDE_DIRS})
link_directories(${OPENGL_glu_LIBRARY})
link_directories(${OPENGL_gl_LIBRARY})

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=gnu++14 -pthread")

set(GL_MODULES ./GL/GLPro.cpp)
set(SYSTEM_MODULES ./System/PostOffice.cpp ./System/ProgramLoader.cpp ./System/Stage.cpp ./System/Object.cpp ./System/Activor.cpp)
set(UTIL_MODULES ./Util/Cache.hpp ./Util/Logger.cpp ./Util/DefinedPattern.cpp)
set(AVIATOR_OBJ ./Aviator/Aviator.cpp)

add_executable(Aviator main.cpp)
add_library(AviatorLib ${AVIATOR_OBJ})
add_library(AviatorGL ${GL_MODULES})
add_library(AviatorSystem ${SYSTEM_MODULES} ${UTIL_MODULES})
target_link_libraries(Aviator AviatorGL AviatorSystem ${X11_LIBRARIES} ${OPENGL_LIBRARIES})