cmake_minimum_required(VERSION 3.10)

# set the project name
project("FDCore" VERSION 0.1)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
SET(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -g -Wall -Wextra")

add_library(${PROJECT_NAME}
            src/Common/Object.cpp
            src/Log/Logger.cpp
            src/ResourceManagement/IResource.cpp
            src/ResourceManagement/AbstractResource.cpp
            src/ResourceManagement/ResourceManager.cpp
            src/PluginManagement/AbstractPlugin.cpp
            src/PluginManagement/PluginManager.cpp)

set(BOOST_ROOT /home/benjamin/Bureau/dev/FanatikDevelopment/FDFramework/thirdparty/boost)
set(BOOST_INCLUDE_DIR ${BOOST_ROOT})
set(BOOST_LIBRARYDIR ${BOOST_ROOT}/stage)

find_package(Boost 1.74 COMPONENTS system filesystem REQUIRED)

target_include_directories(${PROJECT_NAME}
                            PUBLIC include
                            PUBLIC ${BOOST_INCLUDE_DIR})

add_library(${PROJECT_NAME}_test_plugin SHARED test/test_Plugin.cpp)

target_include_directories(${PROJECT_NAME}_test_plugin
                            PUBLIC include
                            PUBLIC test
                            PUBLIC ${BOOST_INCLUDE_DIR})

target_link_libraries(${PROJECT_NAME}_test_plugin ${PROJECT_NAME})

add_executable(${PROJECT_NAME}_test test/main.cpp)
set_property(TARGET ${PROJECT_NAME}_test PROPERTY ENABLE_EXPORTS 1)

target_include_directories(${PROJECT_NAME}_test PUBLIC include)
target_link_libraries(${PROJECT_NAME}_test Boost::filesystem Boost::system)
target_link_libraries(${PROJECT_NAME}_test dl)
target_link_libraries(${PROJECT_NAME}_test ${PROJECT_NAME})
target_link_libraries(${PROJECT_NAME}_test ${PROJECT_NAME}_test_plugin)