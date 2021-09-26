# Battleship game CMakeLists.txt
cmake_minimum_required(VERSION 3.10)
project(battleship VERSION 1.0 LANGUAGES CXX)

# Set h files directory
include_directories(
    ${PROJECT_SOURCE_DIR}/include
)

# Set source files
set(EXECUTABLE_SOURCES
    ${PROJECT_SOURCE_DIR}/src/main.cpp
    ${PROJECT_SOURCE_DIR}/src/Computer.cpp
    ${PROJECT_SOURCE_DIR}/src/Display.cpp
    ${PROJECT_SOURCE_DIR}/src/Engine.cpp
    ${PROJECT_SOURCE_DIR}/src/Grid.cpp
    ${PROJECT_SOURCE_DIR}/src/Player.cpp
    ${PROJECT_SOURCE_DIR}/src/Ship.cpp
)

# Define the binary
add_executable(${PROJECT_NAME} ${EXECUTABLE_SOURCES})

# Find required libraries
find_library(PTHREAD pthread REQUIRED)
find_library(PNG png REQUIRED)
find_library(JPEG jpeg REQUIRED)
find_library(TIFF tiff REQUIRED)
find_library(X11 X11 REQUIRED)

# Link libraries
target_link_libraries(${PROJECT_NAME} PRIVATE ${PTHREAD} ${PNG} ${JPEG} ${TIFF}
    ${X11})
