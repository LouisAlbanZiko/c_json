cmake_minimum_required(VERSION 3.24.0)

file(GLOB_RECURSE SRC_FILES ./*.c)
add_library(c_json STATIC ${SRC_FILES})

target_include_directories(c_json
	PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../include
	PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../_vendor/c_core/include
	PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(c_json c_core)
