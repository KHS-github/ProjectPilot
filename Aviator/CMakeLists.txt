
find_package(PkgConfig)
find_package(OpenGL)
find_package(X11)
pkg_search_module(GLFW glfw3)
include_directories(${X11_INCLUDE_DIRS} ${GLFW_INCLUDE_DIRS})
link_directories(${OPENGL_glu_LIBRARY})
link_directories(${OPENGL_gl_LIBRARY})

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=gnu++14")

set(GL_MODULES ./GL/GLPro.cpp)
set(SYSTEM_MODULES ./System/PostOffice.cpp ./System/ProgramLoader.cpp)
set(UTIL_MODULES ./Util/Cache.cpp ./Util/Logger.cpp ./Util/DefinedPattern.cpp)

add_executable(Aviator Aviator.cpp)
add_library(AviatorGL ${GL_MODULES})
add_library(AviatorSystem ${SYSTEM_MODULES})
add_library(AviatorUtil ${UTIL_MODULES})
target_link_libraries(Aviator AviatorGL AviatorSystem ${X11_LIBRARIES} ${OPENGL_LIBRARIES})