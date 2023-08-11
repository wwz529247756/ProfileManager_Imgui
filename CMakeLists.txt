cmake_minimum_required(VERSION 3.0.0)
project(ProfileManager VERSION 0.1.0 LANGUAGES C CXX)


find_package ( OpenGL REQUIRED )

set ( PRJ_INC_LIST )
set ( PRJ_SRC_LIST )
set ( PRJ_LIBRARIES )
set ( PRJ_INCLUDE_DIRS )

set ( GLFW_HOME "${CMAKE_CURRENT_SOURCE_DIR}/3rd_lib/glfw" )
set ( IMGUI_HOME "${CMAKE_CURRENT_SOURCE_DIR}/3rd_lib/imgui" )

set ( GLFW_INC "${GLFW_HOME}/include" )
set ( GLFW_LIB "${GLFW_HOME}/lib/libglfw3.a" )

set ( IMGUI_INC "${IMGUI_HOME}/include" )
set ( IMGUI_SRC "${IMGUI_HOME}/src" )

file ( GLOB root_header_files "${CMAKE_CURRENT_SOURCE_DIR}/*.h" )
file ( GLOB root_src_files "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp" )

file ( GLOB imgui_header_files "${IMGUI_INC}/*.h" )
file ( GLOB imgui_src_files "${IMGUI_SRC}/*.cpp" )

list ( APPEND PRJ_INCLUDE_DIRS . )
list ( APPEND PRJ_INCLUDE_DIRS ${GLFW_INC} )
list ( APPEND PRJ_INCLUDE_DIRS ${IMGUI_INC} )

list ( APPEND PRJ_INC_LIST ${root_header_files} )
list ( APPEND PRJ_INC_LIST ${imgui_header_files} )

list ( APPEND PRJ_SRC_LIST ${root_src_files} )
list ( APPEND PRJ_SRC_LIST ${imgui_src_files} )

list ( APPEND PRJ_LIBRARIES ${GLFW_LIB} )
list ( APPEND PRJ_LIBRARIES ${OPENGL_LIBRARIES} )

if(NOT CMAKE_RC_COMPILER)
    set(CMAKE_RC_COMPILER windres.exe)
endif()

add_custom_command( OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/res.obj
    COMMAND ${CMAKE_RC_COMPILER}
    -D GCC_WINDRES
    -I ${CMAKE_CURRENT_SOURCE_DIR}
    -I ${CMAKE_CURRENT_BINARY_DIR}
    -o ${CMAKE_CURRENT_BINARY_DIR}/res.obj
    -i ${CMAKE_CURRENT_SOURCE_DIR}/res.rc
)

list(APPEND PRJ_SRC_LIST ${CMAKE_CURRENT_BINARY_DIR}/res.obj)

add_executable ( ${PROJECT_NAME} ${PRJ_SRC_LIST} ${PRJ_INC_LIST} )

target_include_directories ( ${PROJECT_NAME}
    PRIVATE 
    ${PRJ_INCLUDE_DIRS}
)

target_link_libraries ( ${PROJECT_NAME} 
    PRIVATE 
    ${PRJ_LIBRARIES}
)