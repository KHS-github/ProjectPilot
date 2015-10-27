
find_package(PkgConfig)
find_package(OpenGL)
find_package(X11)
include_directories(${X11_INCLUDE_DIRS})
link_directories(${OPENGL_glu_LIBRARY})
link_directories(${OPENGL_gl_LIBRARY})

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -pthread")

set(GL_MODULES ./GL/GLPro.cpp)
set(SYSTEM_MODULES ./System/PostOffice.cpp ./System/ProgramLoader.cpp ./System/Stage.cpp ./System/Object.cpp ./System/Activor.cpp)
set(UTIL_MODULES ./Util/Cache.hpp ./Util/Logger.cpp ./Util/DefinedPattern.cpp ./Util/Singleton.hpp ./Util/ReadStream.cpp ./Util/WriteStream.cpp)
set(AVIATOR_OBJ ./Aviator/Aviator.cpp)

add_executable(Aviator main.cpp)
add_library(AviatorLib OBJECT ${AVIATOR_OBJ})
add_library(AviatorGL OBJECT ${GL_MODULES})
add_library(AviatorSystem OBJECT ${SYSTEM_MODULES} ${UTIL_MODULES})

set(SUB_LIBS AviatorLib AviatorGL AviatorSystem)

foreach(LIB_ITEM ${SUB_LIBS})
    set(LIB_LIST ${LIB_LIST} $<TARGET_OBJECTS:${LIB_ITEM}>)
endforeach()

add_library(UnitedLib STATIC ${LIB_LIST})

target_link_libraries(Aviator UnitedLib ${X11_LIBRARIES} ${OPENGL_LIBRARIES})