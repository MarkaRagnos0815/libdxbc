cmake_minimum_required(VERSION 3.21)

project(dxbc CXX)

include(${CMAKE_CURRENT_LIST_DIR}/../cmake/build.cmake)
include(${CMAKE_CURRENT_LIST_DIR}/../cmake/functions.cmake)

file(GLOB_RECURSE PROJECT_SOURCE_FILES *.* ../include/*.h)
file(GLOB DXBC_HEADERS ../include/*)

add_library(${PROJECT_NAME} STATIC ${PROJECT_SOURCE_FILES})

set_target_cxx_standard(${PROJECT_NAME} 14)
set_target_c_standard(${PROJECT_NAME} 11)
set_target_properties(${PROJECT_NAME} PROPERTIES POSITION_INDEPENDENT_CODE TRUE)
set_target_properties(${PROJECT_NAME} PROPERTIES LINKER_LANGUAGE CXX)

target_include_directories(
	${PROJECT_NAME}
	BEFORE
	PRIVATE
	../include/
)


include(${CMAKE_CURRENT_LIST_DIR}/../cmake/default_target_settings.cmake)

install(TARGETS dxbc RUNTIME DESTINATION bin LIBRARY DESTINATION bin ARCHIVE DESTINATION lib)
install(FILES ${DXBC_HEADERS} DESTINATION include)