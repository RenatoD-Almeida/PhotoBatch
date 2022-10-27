add_library(ArgumentParser SHARED argumentParser.cpp utility.cpp mode.cpp)

target_include_directories(ArgumentParser PUBLIC ../includes)
# include_directories(../includes)