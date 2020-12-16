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

set(HEADER_FILES
    include/ApplicationManagement/AbstractApplication.h
#
    include/Common/CallOnEdit.h
    include/Common/Comparison.h
    include/Common/ContiguousMap.h
    include/Common/ContiguousSet.h
    include/Common/CopyOnWrite.h
    include/Common/CRTPTrait.h
    include/Common/EnumFlag.h
    include/Common/FileUtils.h
    include/Common/Identifiable.h
    include/Common/Macros.h
    include/Common/NonCopyableTrait.h
    include/Common/Object.h
    include/Common/ObjectGuard.h
    include/Common/Singleton.h
    include/Common/Span.h
    include/Common/ThreadPool.h
    include/Common/TypeInformation.h
#
    include/Communication/MessageHeader.h
    include/Communication/Request.h
    include/Communication/RequestType.h
#
    include/DynamicVariable/AbstractValue.h
    include/DynamicVariable/DynamicVariable.h
    include/DynamicVariable/PrimitiveValue.h
    include/DynamicVariable/ValueType.h
#
    include/Log/AbstractLogger.h
    include/Log/Logger.h
    include/Log/LogLevel.h
#
    include/PluginManagement/AbstractPlugin.h
    include/PluginManagement/Plugin.h
    include/PluginManagement/PluginBinder.h
    include/PluginManagement/PluginManager.h
    include/PluginManagement/PluginResource.h
#
    include/ResourceManagement/AbstractResource.h
    include/ResourceManagement/IResource.h
    include/ResourceManagement/ResourceManager.h
    include/ResourceManagement/StrategyResource.h
)

set(SRC_FILES
    src/ApplicationManagement/AbstractApplication.cpp
#
    src/Common/FileUtils.cpp
    src/Common/Object.cpp
    src/Common/ThreadPool.cpp
#
    src/DynamicVariable/DynamicVariable.cpp
#
    src/Log/Logger.cpp
#
    src/PluginManagement/AbstractPlugin.cpp
    src/PluginManagement/PluginManager.cpp
    src/PluginManagement/PluginResource.cpp
#
    src/ResourceManagement/IResource.cpp
    src/ResourceManagement/AbstractResource.cpp
    src/ResourceManagement/ResourceManager.cpp
)

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