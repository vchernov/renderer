add_executable(wireframe wireframe.cpp)
target_include_directories(wireframe PRIVATE ${PROJECT_SOURCE_DIR}/tools)
target_link_libraries(wireframe tools)
