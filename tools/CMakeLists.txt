add_library(tools
    barycentric.cpp
    barycentric.h
    Buffer.h
    Canvas.cpp
    Canvas.h
    CompositeRenderOutput.cpp
    CompositeRenderOutput.h
    FileRenderOutput.cpp
    FileRenderOutput.h
    FrameBuffer.cpp
    FrameBuffer.h
    IRenderOutput.h
    Mesh.h
    ObjReader.cpp
    ObjReader.h
    ppm.cpp
    ppm.h
    Window.cpp
    Window.h
    WindowRenderOutput.cpp
    WindowRenderOutput.h
)

target_compile_features(tools PUBLIC cxx_std_17)

find_package(glm CONFIG REQUIRED)
target_link_libraries(tools PUBLIC glm)

find_package(SDL2 CONFIG REQUIRED)
if (UNIX)
    target_include_directories(tools PUBLIC ${SDL2_INCLUDE_DIRS})
    target_link_libraries(tools PUBLIC ${SDL2_LIBRARIES})
endif()
if (WIN32)
	target_link_libraries(tools PUBLIC SDL2::SDL2 SDL2::SDL2main)
endif()
