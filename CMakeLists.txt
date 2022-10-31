cmake_minimum_required(VERSION 3.22)

project("PhotoBatch")

set(FETCHCONTENT_QUIET OFF CACHE BOOL "desabilita o modo quiet do FetchContent" FORCE)
include(FetchContent)

add_subdirectory(./external)

add_subdirectory(./src)
add_subdirectory(./app)