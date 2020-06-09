cmake_minimum_required(VERSION 3.10)

# set the project name
project("FDCore" VERSION 0.1)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)


add_library(${PROJECT_NAME}
            src/Common/Object.cpp
            src/ResourceManagement/IResource.cpp
            src/ResourceManagement/AbstractResource.cpp)

target_include_directories(${PROJECT_NAME} PUBLIC include)

add_executable(${PROJECT_NAME}_test test/main.cpp)

target_include_directories(${PROJECT_NAME}_test PUBLIC include)