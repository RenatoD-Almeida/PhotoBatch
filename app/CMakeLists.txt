add_executable(${PROJECT_NAME} aplication.cpp)

target_link_libraries(${PROJECT_NAME} PUBLIC ArgumentParser)
target_include_directories(${PROJECT_NAME} PUBLIC ../includes)