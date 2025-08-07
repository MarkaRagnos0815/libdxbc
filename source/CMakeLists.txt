cmake_minimum_required(VERSION 3.21)

project(dxbc CXX)

include(${CMAKE_CURRENT_LIST_DIR}/../cmake/build.cmake)
include(${CMAKE_CURRENT_LIST_DIR}/../cmake/functions.cmake)

file(GLOB_RECURSE PROJECT_HEADER_FILES ../include/*.h)
file(GLOB_RECURSE PROJECT_SOURCE_FILES *.cpp)
file(GLOB_RECURSE PROJECT_SOURCE_FILES_INCLUDE *.h *.inl)
file(GLOB DXBC_HEADERS ../include/*)

add_library(${PROJECT_NAME} STATIC ${PROJECT_SOURCE_FILES} ${PROJECT_HEADER_FILES} ${PROJECT_SOURCE_FILES_INCLUDE})

source_group("Sources"            FILES ${PROJECT_SOURCE_FILES})
source_group("Private Headres"    FILES ${PROJECT_SOURCE_FILES_INCLUDE})
source_group("Headers"            FILES ${PROJECT_HEADER_FILES})


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
install(FILES ${DXBC_HEADERS} DESTINATION include/${PROJECT_NAME})
