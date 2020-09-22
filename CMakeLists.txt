cmake_minimum_required(VERSION 3.10)

project("FDCore" VERSION 0.1)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -Wall -Wextra")

option(FDCORE_BUILD_STATIC "Build FDCore as static library" OFF)

option(FDCORE_BUILD_TESTS "Build FDCore tests" ON)

if(NOT DEFINED BOOST_ROOT)
    message(STATUS "BOOST_ROOT not defined: using default path")
else()
    if(NOT DEFINED BOOST_INCLUDEDIR)
        set(BOOST_INCLUDEDIR ${BOOST_ROOT}/include)
    endif()
    
    if(NOT DEFINED BOOST_LIBRARYDIR)
        set(BOOST_LIBRARYDIR ${BOOST_ROOT}/lib)
    endif()
endif()

if(NOT DEFINED GTEST_ROOT)
    message(STATUS "GTEST_ROOT not defined: using default path")
else()
    if(NOT GTEST_INCLUDE_DIR)
        set(GTEST_INCLUDE_DIR ${GTEST_ROOT}/include)
    endif()
    
    if(NOT GTEST_LIBRARIES)
        set(GTEST_LIBRARIES ${GTEST_ROOT}/lib)
    endif()
endif()

set(SRC_FILES
    src/Common/Object.cpp
    src/Common/ThreadPool.cpp
    src/Common/FileUtils.cpp
    src/Log/Logger.cpp
    src/ApplicationManagement/AbstractApplication.cpp
    src/ResourceManagement/IResource.cpp
    src/ResourceManagement/AbstractResource.cpp
    src/ResourceManagement/ResourceManager.cpp
    src/PluginManagement/AbstractPlugin.cpp
    src/PluginManagement/PluginManager.cpp
    src/PluginManagement/PluginResource.cpp
    src/DynamicVariable/DynamicVariable.cpp)

if(FDCORE_BUILD_STATIC)
    add_library(${PROJECT_NAME} STATIC ${SRC_FILES})
else()
    add_library(${PROJECT_NAME} SHARED ${SRC_FILES})
endif()

target_include_directories(${PROJECT_NAME}
                            PUBLIC include
                            PUBLIC ${BOOST_INCLUDEDIR})

find_package(Boost 1.75 COMPONENTS system filesystem REQUIRED)

if(FDCORE_BUILD_TESTS)
    if(NOT GTEST_FOUND)
        find_package(GTest REQUIRED COMPONENTS gtest)
        set(THREADS_PREFER_PTHREAD_FLAG ON)
        find_package(Threads REQUIRED)
    endif()

    add_library(${PROJECT_NAME}_test_plugin SHARED test/test_Plugin.cpp)

    target_include_directories(${PROJECT_NAME}_test_plugin
                                PUBLIC include
                                PUBLIC test
                                PUBLIC ${BOOST_INCLUDEDIR}
                                PUBLIC ${GTEST_INCLUDE_DIR})

    target_link_libraries(${PROJECT_NAME}_test_plugin ${PROJECT_NAME})

    add_executable(${PROJECT_NAME}_test test/main.cpp)

    set_property(TARGET ${PROJECT_NAME}_test PROPERTY ENABLE_EXPORTS 1)

    target_include_directories(${PROJECT_NAME}_test
                                PUBLIC include
                                PUBLIC ${BOOST_INCLUDEDIR}
                                PUBLIC ${GTEST_INCLUDE_DIR})

    target_link_libraries(${PROJECT_NAME}_test Threads::Threads)
    target_link_libraries(${PROJECT_NAME}_test Boost::filesystem Boost::system)
    target_link_libraries(${PROJECT_NAME}_test GTest::GTest)
    target_link_libraries(${PROJECT_NAME}_test dl)
    target_link_libraries(${PROJECT_NAME}_test ${PROJECT_NAME})
    target_link_libraries(${PROJECT_NAME}_test ${PROJECT_NAME}_test_plugin)

    enable_testing()
    include(GoogleTest)
    gtest_discover_tests(${PROJECT_NAME}_test)
endif()