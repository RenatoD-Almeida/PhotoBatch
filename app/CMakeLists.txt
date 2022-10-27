add_executable(${PROJECT_NAME} aplication.cpp)
add_executable(${PROJECT_NAME}pDev aplication.cpp)

target_link_libraries(${PROJECT_NAME} PUBLIC ArgumentParser)
# target_include_directories(${PROJECT_NAME} PUBLIC ../includes)

target_link_libraries(${PROJECT_NAME}pDev PUBLIC ArgumentParser)
# target_include_directories(${PROJECT_NAME}pDev PUBLIC ../includes)

target_compile_definitions(${PROJECT_NAME}pDev PUBLIC dev)

set_target_properties(${PROJECT_NAME} PROPERTIES CXX_STANDARD 20)
set_target_properties(${PROJECT_NAME}pDev PROPERTIES CXX_STANDARD 20)