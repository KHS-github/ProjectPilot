
find_package(PkgConfig)
find_package(OpenGL)
find_package(X11)
find_package(GLEW)
include_directories(${X11_INCLUDE_DIRS})
link_directories(${OPENGL_glu_LIBRARY})
link_directories(${OPENGL_gl_LIBRARY})

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -g")
set(auto-load libthread-db)


AUX_SOURCE_DIRECTORY(GL GL_MODULES)
AUX_SOURCE_DIRECTORY(System SYSTEM_MODULES)
AUX_SOURCE_DIRECTORY(System/GUI SYSTEM_GUI_MODULES)
AUX_SOURCE_DIRECTORY(System/DefinedFunction PILOT_FUNCTION)
set(SYSTEM_MODULES ${SYSTEM_MODULES} ${SYSTEM_GUI_MODULES} ${PILOT_FUNCTION})
AUX_SOURCE_DIRECTORY(Util UTIL_MODULES)
AUX_SOURCE_DIRECTORY(Aviator AVIATOR_OBJ)

add_library(AviatorLib OBJECT ${AVIATOR_OBJ})
add_library(AviatorGL OBJECT ${GL_MODULES})
add_library(AviatorSystem OBJECT ${SYSTEM_MODULES} ${UTIL_MODULES})

set(SUB_LIBS AviatorLib AviatorGL AviatorSystem)

foreach(LIB_ITEM ${SUB_LIBS})
    set(LIB_LIST ${LIB_LIST} $<TARGET_OBJECTS:${LIB_ITEM}>)
endforeach()

add_library(UnitedLib STATIC ${LIB_LIST})

add_executable(Aviator main.cpp)
target_link_libraries(Aviator UnitedLib pthread ${GLEW_LIBRARIES} ${X11_LIBRARIES} ${OPENGL_LIBRARIES} ${X11_Xxf86vm_LIB})