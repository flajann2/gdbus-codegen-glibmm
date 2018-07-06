CMAKE_MINIMUM_REQUIRED (VERSION 2.8)
PROJECT (LuxPromiseTest)
FIND_PACKAGE(PkgConfig)

macro(print_all_variables)
  message(STATUS "print_all_variables------------------------------------------{")
  get_cmake_property(_variableNames VARIABLES)
  foreach (_variableName ${_variableNames})
    message(STATUS "${_variableName}=${${_variableName}}")
  endforeach()
  message(STATUS "print_all_variables------------------------------------------}")
endmacro()

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_CURRENT_SOURCE_DIR}/../cmake_modules)

include(AddGTestTest)
include(AddGMock)

add_gmock()

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

IF (NOT CODEGEN)
  MESSAGE (FATAL_ERROR "CODEGEN not specified. Specify path to codegen using -DCODEGEN=<path to code>")
ENDIF ()

set (TARGET test_luxpromise)

include_directories (${CMAKE_SOURCE_DIR}/../../include)

file(GLOB SOURCE_FILES "*.cpp" "*.h")
file(GLOB HEADER_FILES "../../include/*.h")

set(SOURCES
  ${SOURCE_FILES}
  ${HEADER_FILES}
  )

add_executable (${TARGET} ${SOURCES})

target_link_libraries(${TARGET}
  gtest
  gtest_main
  gmock
  gmock_main
  )

add_test(NAME ${TARGET} COMMAND ${TARGET})
