add_executable(sw
    sw.cpp
    Vertex.h
    ScanlineRasterizer.cpp
    ScanlineRasterizer.h
)
target_include_directories(sw PRIVATE ${PROJECT_SOURCE_DIR}/tools)
target_link_libraries(sw tools)
