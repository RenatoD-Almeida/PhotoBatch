FetchContent_Declare(
    stbcontents
    GIT_REPOSITORY https://github.com/nothings/stb.git
)

FetchContent_MakeAvailable(stbcontents)

FetchContent_GetProperties(
    stbcontents
    SOURCE_DIR
    _stbSorceDir
)
 
message("Mensagem: " ${_stbSorceDir})

add_library(stb INTERFACE)
# include_directories(${_stbSorceDir})
target_include_directories(stb INTERFACE ${_stbSorceDir})
