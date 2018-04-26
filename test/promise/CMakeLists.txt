CMAKE_MINIMUM_REQUIRED (VERSION 2.8)
PROJECT (GDbusCodegenGlibmmProxyTest)
FIND_PACKAGE(PkgConfig)

PKG_CHECK_MODULES (GLIBMM REQUIRED glibmm-2.4)
PKG_CHECK_MODULES (GIOMM  REQUIRED giomm-2.4)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

IF (NOT CODEGEN)
    MESSAGE (FATAL_ERROR "CODEGEN not specified. Specify path to codegen using -DCODEGEN=<path to code>")
ENDIF ()

SET (GENERATED_PROMISE
    ${CMAKE_BINARY_DIR}/generated/futures_promise.cpp
    ${CMAKE_BINARY_DIR}/generated/futures_promise.h
    ${CMAKE_BINARY_DIR}/generated/futures_stub.cpp
    ${CMAKE_BINARY_DIR}/generated/futures_stub.h
    ${CMAKE_BINARY_DIR}/generated/futures_common.cpp
    ${CMAKE_BINARY_DIR}/generated/futures_common.h
)

SET (INTROSPECTION_XML ${CMAKE_SOURCE_DIR}/../common/futures.xml)

ADD_CUSTOM_COMMAND (OUTPUT ${GENERATED_PROMISE}
                    COMMAND mkdir -p ${CMAKE_BINARY_DIR}/generated/
                    COMMAND ${CODEGEN} --promise=true
                                       --generate-cpp-code=${CMAKE_BINARY_DIR}/generated/futures
                                       ${INTROSPECTION_XML}
                    DEPENDS ${INTROSPECTION_XML}
                    COMMENT "Generate the promises for the test program")

SET (SOURCES
    testpromisemain.cpp
    ${CMAKE_BINARY_DIR}/generated/futures_promise.cpp
    ${CMAKE_BINARY_DIR}/generated/futures_stub.cpp
    ${CMAKE_BINARY_DIR}/generated/futures_common.cpp
)

SET (HEADERS
    testpromisemain.h
    ../common/tools.h
    ${CMAKE_BINARY_DIR}/generated/futures_promise.h
    ${CMAKE_BINARY_DIR}/generated/futures_stub.h
    ${CMAKE_BINARY_DIR}/generated/futures_common.h
)

INCLUDE_DIRECTORIES (
    ../common/
    ${GLIBMM_INCLUDE_DIRS}
    ${GIOMM_INCLUDE_DIRS}
    ${CMAKE_BINARY_DIR}/generated/
    ${CMAKE_BINARY_DIR}/generated/)

ADD_EXECUTABLE (promisetest ${SOURCES} ${HEADERS})

TARGET_LINK_LIBRARIES (promisetest
                        ${GLIBMM_LIBRARIES}
                        ${GIOMM_LIBRARIES}
)
