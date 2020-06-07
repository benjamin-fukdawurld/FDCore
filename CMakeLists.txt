cmake_minimum_required(VERSION 3.10)

# set the project name
project(FDCore VERSION 0.1)

set(BUILD_FDCORE_TESTS ${BUILD_TESTS} "Build test cases for FDCore" PARENT_SCOPE)

set(GOOGLETEST_DIR ${THIRDPARTY_DIR}/googletest)
set(SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)
set(INC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include/FDCore)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(LLVM_DIR ${THIRDPARTY_DIR}/llvm)
set(LLVM_BUILD_DIR ${LLVM_DIR}/build)
set(LLVM_BIN_DIR ${LLVM_DIR}/build/bin)
#SET(CMAKE_C_COMPILER clang)
#SET(CMAKE_CXX_COMPILER clang++)

#add_library(FDCore_compiler_flags INTERFACE)
#target_compile_features(FDCore_compiler_flags INTERFACE cxx_std_17)
#set(gcc_like_cxx "$<COMPILE_LANG_AND_ID:CXX,ARMClang,AppleClang,Clang,GNU>")
#set(msvc_cxx "$<COMPILE_LANG_AND_ID:CXX,MSVC>")
#target_compile_options(FDCore_compiler_flags INTERFACE
#  "$<${gcc_like_cxx}:$<BUILD_INTERFACE:-pipe;-std=gnu++1z;-g;-Wall;-Wextra;-Wshadow;-Wold-style-cast;-Wformat=2;-Wunused;-fPIC>>"
#  "$<${msvc_cxx}:$<BUILD_INTERFACE:-W3>>"
#)


file(GLOB FDCore_SRC "${SRC_DIR}/*.cpp")
file(GLOB FDCore_INCLUDE "${INC_DIR}/*.h")

add_library(FDCore ${FDCore_SRC})

list(APPEND LIBS_LIST gtest pthread)
list(APPEND INCLUDE_LIST $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>)

target_include_directories(FDCore PUBLIC
                            ${INCLUDE_LIST}
                            $<INSTALL_INTERFACE:include>)

install(TARGETS FDCore DESTINATION lib EXPORT FDCoreTargets)
install(FILES ${FDCore_INCLUDE} DESTINATION include/FDCore)

if(BUILD_TESTS)
    add_executable(FDCore_test test/main.cpp)
    list(APPEND INCLUDE_LIST $<BUILD_INTERFACE:"${GOOGLETEST_DIR}/googletest/include">)
    list(APPEND LIBS_LIST FDCore)

    target_include_directories(FDCore_test PUBLIC
                               ${INCLUDE_LIST}
                               $<INSTALL_INTERFACE:include>)

    link_directories(${GOOGLETEST_DIR}/build/lib)
    add_library(gtest STATIC IMPORTED)
    set_target_properties(gtest
                          PROPERTIES
                          IMPORTED_LOCATION
                          "${GOOGLETEST_DIR}/build/lib/libgtest.a" )

    target_link_libraries(FDCore_test ${LIBS_LIST})
    install(TARGETS FDCore_test DESTINATION bin EXPORT FDCore_testTargets)
endif()

include(InstallRequiredSystemLibraries)
set(CPACK_RESOURCE_FILE_LICENCE "${CMAKE_CURRENT_SOURCE_DIR}/LICENCE")
set(CPACK_PACKAGE_VERSION_MAJOR ${FDCore_VERSION_MAJOR})
set(CPACK_PACKAGE_VERSION_MAJOR ${FDCore_VERSION_MINOR})
include(CPack)