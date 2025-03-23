file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS
    "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/windows/*.cpp"
)

add_executable(${PROJECT_NAME} ${SOURCES})
add_executable(main2 ${CMAKE_CURRENT_SOURCE_DIR}/../knapsack/main2.cpp ${CMAKE_CURRENT_SOURCE_DIR}/../knapsack/knapsack.cpp)


target_include_directories(${PROJECT_NAME} PRIVATE 
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/windows
)