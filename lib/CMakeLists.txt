file(GLOB IMGUI_SRC
    "imgui/*.cpp"
    "imgui/backends/*.cpp"
)

add_library(imgui STATIC 
    ${IMGUI_SRC}
)

target_include_directories(imgui PUBLIC 
    imgui/include
    imgui/backends/include
)