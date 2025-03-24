cmake_minimum_required(VERSION 3.12)
cmake_policy(SET CMP0079 NEW)

project(Algorithms)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Subdirectories
add_subdirectory(src)
add_subdirectory(lib)

target_link_libraries(${PROJECT_NAME} PUBLIC 
    imgui
    d3d11
    d3dcompiler 
    dwmapi
)


file(COPY ${CMAKE_SOURCE_DIR}/assets DESTINATION ${CMAKE_BINARY_DIR})