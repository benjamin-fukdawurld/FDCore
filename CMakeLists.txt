cmake_minimum_required(VERSION 3.10)

# set the project name
project(FDCore VERSION 0.1)

option(BUILD_TESTS "Build test cases for FDCore" True)

set(THIRDPARTY_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../thirdparty)
set(GOOGLETEST_DIR ${THIRDPARTY_DIR}/googletest)
set(SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)
set(INC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include/FDCore)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(LLVM_DIR ${THIRDPARTY_DIR}/llvm)
set(LLVM_BUILD_DIR ${LLVM_DIR}/build)

#SET(CMAKE_C_COMPILER ${THIRDPARTY_DIR})
#SET(CMAKE_CXX_COMPILER ${THIRDPARTY_DIR})

file(GLOB FDCore_SRC "${SRC_DIR}/*.cpp")
file(GLOB FDCore_INCLUDE "${INC_DIR}/*.h")

add_library(FDCore ${FDCore_SRC})

list(APPEND LIBS_LIST gtest pthread)
list(APPEND INCLUDE_LIST "include/")

target_include_directories(FDCore PUBLIC
                            ${INCLUDE_LIST})

install(TARGETS FDCore DESTINATION lib)
install(FILES ${FDCore_INCLUDE} DESTINATION include/FDCore)

if(BUILD_TESTS)
    add_executable(FDCore_test test/main.cpp)
    list(APPEND INCLUDE_LIST "${GOOGLETEST_DIR}/googletest/include")
    list(APPEND LIBS_LIST FDCore)

    target_include_directories(FDCore_test PUBLIC
                               ${INCLUDE_LIST})

    link_directories(${GOOGLETEST_DIR}/build/lib)
    add_library(gtest STATIC IMPORTED)
    set_target_properties(gtest
                          PROPERTIES
                          IMPORTED_LOCATION
                          "${GOOGLETEST_DIR}/build/lib/libgtest.a" )

    target_link_libraries(FDCore_test ${LIBS_LIST})
    install(TARGETS FDCore_test DESTINATION bin)
endif()