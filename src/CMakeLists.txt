add_library(ArgumentParser SHARED argumentParser.cpp utility.cpp mode.cpp)
add_library(ArgumentParserpDev SHARED argumentParser.cpp utility.cpp mode.cpp)

target_link_libraries(ArgumentParser PUBLIC stb)
target_link_libraries(ArgumentParserpDev PUBLIC stb)


target_compile_definitions(ArgumentParserpDev PUBLIC dev)

target_include_directories(ArgumentParser PUBLIC ../includes)
target_include_directories(ArgumentParserpDev PUBLIC ../includes)
# include_directories(../includes)