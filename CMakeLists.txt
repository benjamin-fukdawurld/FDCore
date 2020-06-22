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
            src/ResourceManagement/ResourceManager.cpp)

target_include_directories(${PROJECT_NAME} PUBLIC include)

add_executable(${PROJECT_NAME}_test test/main.cpp)

target_include_directories(${PROJECT_NAME}_test PUBLIC include)
target_link_libraries(${PROJECT_NAME}_test ${PROJECT_NAME})