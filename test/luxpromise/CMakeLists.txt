CMAKE_MINIMUM_REQUIRED (VERSION 2.8)
PROJECT (LuxPromiseTest)
FIND_PACKAGE(PkgConfig)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_CURRENT_SOURCE_DIR}/../cmake_modules)

include(AddGTestTest)
include(AddGMock)

add_gmock()

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set (TARGET luxpromisetest)

include_directories (${CMAKE_BINARY_DIR}/include)

add_executable (${TARGET} maintest.cpp)

target_link_libraries(${TARGET}
  gtest
  gtest_main
  gmock
  gmock_main
  )

add_test(NAME ${TARGET} COMMAND ${TARGET})
