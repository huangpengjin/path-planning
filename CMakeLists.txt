cmake_minimum_required(VERSION 3.0)
project(path_planning)

set(CMAKE_BUILD_TYPE "Debug")

find_package(OpenCV REQUIRED)

SET( THIRD_PARTY_LIBS
  tinyxml2
  ${OpenCV_LIBS}
)

include_directories(include)

FILE(GLOB_RECURSE SOURCES src/*.c*)
FILE(GLOB_RECURSE HEADERS include/*.h*)

set(_src_root_path "${CMAKE_CURRENT_BINARY_DIR}/src")
set(_header_root_path "${CMAKE_CURRENT_BINARY_DIR}/include")
foreach(_source IN ITEMS ${SOURCES})
  get_filename_component(_source_path "${_source}" PATH)
  file(RELATIVE_PATH _source_path_rel "${_src_root_path}" "${_source_path}")
  string(REPLACE "/" "\\" _source_group_path "${_source_path_rel}")
  source_group("${_source_group_path}" FILES "${_source}")
endforeach()

foreach(_header IN ITEMS ${HEADERS})
  get_filename_component(_header_path "${_header}" PATH)
  file(RELATIVE_PATH _header_path_rel "${_header_root_path}" "${_header_path}")
  string(REPLACE "/" "\\" _group_path "${_header_path_rel}")
  source_group("${_group_path}" FILES "${_header}")
endforeach()

add_library(${PROJECT_NAME} SHARED
  ${SOURCES}
)

FILE(GLOB UNIT_TEST unit_test/*.c*)
FOREACH(TEST ${UNIT_TEST})
  GET_FILENAME_COMPONENT(TEST_TARGET "${TEST}" NAME_WE)
  ADD_EXECUTABLE(${TEST_TARGET} ${TEST} )
  TARGET_LINK_LIBRARIES(${TEST_TARGET} ${PROJECT_NAME}
  ${THIRD_PARTY_LIBS}
  )
ENDFOREACH()

