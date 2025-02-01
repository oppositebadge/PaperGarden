cmake_minimum_required(VERSION 3.10)

# Set the project name, which will be used for the output directory
project(PaperGarden LANGUAGES CXX VERSION 0.1)

# Set build type if not specified
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug)
endif()

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Add compiler flags
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g")
endif()

#find_package(Threads REQUIRED)
find_package(raylib 5.0 REQUIRED)

# Add the path to the raylib include files
include_directories(${raylib_INCLUDE_DIR})

# Specify the assets directory
set(ASSETS_DIR ${CMAKE_SOURCE_DIR}/assets)

# Specify the build output directory based on the project name
set(BUILD_OUTPUT_DIR ${CMAKE_BINARY_DIR}/${PROJECT_NAME})

# Create the project output directory if it doesn't exist
file(MAKE_DIRECTORY ${BUILD_OUTPUT_DIR})

# Find all .cpp files in the current src directory
file(GLOB_RECURSE SOURCES ${CMAKE_SOURCE_DIR}/src/*.cpp)

# Find all additional .cpp files 
file(GLOB_RECURSE ADDITIONAL_SOURCES ${CMAKE_SOURCE_DIR}/engine/*.cpp ${CMAKE_SOURCE_DIR}/third_party/*.cpp)

# Combine both source lists
list(APPEND SOURCES ${ADDITIONAL_SOURCES})

# Add the executable and link the source files
add_executable(${PROJECT_NAME} ${SOURCES})

# Includes
include_directories("${CMAKE_SOURCE_DIR}/src" "${CMAKE_SOURCE_DIR}/engine" "${CMAKE_SOURCE_DIR}/third_party") 

target_link_libraries(${PROJECT_NAME} PRIVATE ${raylib_LIBRARY})

# Set the output directory for the executable
set_target_properties(${PROJECT_NAME} PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${BUILD_OUTPUT_DIR}
)

# Define the command to copy the assets directory to the build output directory
add_custom_command(
    TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${ASSETS_DIR} ${BUILD_OUTPUT_DIR}/assets
    COMMENT "Copying assets to build output directory"
)

# Print build type
message(STATUS "Build type: ${CMAKE_BUILD_TYPE}")
