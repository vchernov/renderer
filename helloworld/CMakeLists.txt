add_executable(helloworld main.cpp)
target_include_directories(helloworld PRIVATE ${PROJECT_SOURCE_DIR}/tools)
target_link_libraries(helloworld tools)
