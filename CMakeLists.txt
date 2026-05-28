cmake_minimum_required(VERSION 3.10)

project(ContentAwareImageResizing)

set(CMAKE_CXX_STANDARD 17)

find_package(OpenCV REQUIRED)

include_directories(
    include
    ${OpenCV_INCLUDE_DIRS}
)

add_executable(
    seam_carver
    src/main.cpp
    src/energy.cpp
    src/seam_carver.cpp
)

target_link_libraries(
    seam_carver
    ${OpenCV_LIBS}
)