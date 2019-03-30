add_library(tools
    FrameBuffer.cpp
    FrameBuffer.h
    Window.cpp
    Window.h
    Canvas.cpp
    Canvas.h
    Mesh.h
    ObjReader.cpp
    ObjReader.h
)

target_compile_features(tools PUBLIC cxx_std_14)

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
