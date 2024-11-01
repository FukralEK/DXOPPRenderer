cmake_minimum_required(VERSION 3.10)

project(DXOPPRenderer)


add_definitions(-DUNICODE -D_UNICODE)
set(CMAKE_CXX_STANDARD 20)

file(GLOB_RECURSE MY_SOURCES CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")

include_directories("imgui/")

file(GLOB_RECURSE IMGUI CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/imgui/*.cpp")

list(APPEND MY_SOURCES ${IMGUI})

add_executable(DXOPPRenderer WIN32 "${MY_SOURCES}")
target_link_libraries(DXOPPRenderer PRIVATE d3d11 D3DCompiler)