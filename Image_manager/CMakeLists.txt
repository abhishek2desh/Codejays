cmake_minimum_required(VERSION 3.14)
project(image_manager)

# Add C++17 support
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find required packages
find_package(OpenCV REQUIRED)
find_package(GTest REQUIRED)

# Include directories
include_directories(${OpenCV_INCLUDE_DIRS})
# Include cxxopts
# Specify the CxxOpts include directory
include_directories(c:/cxxopts/include)

if(MSVC)
    add_compile_options(
        $<$<CONFIG:>:/MT> #---------|
        $<$<CONFIG:Debug>:/MTd> #---|-- Statically link the runtime libraries
        $<$<CONFIG:Release>:/MT> #--|
    )
endif()
# Add the main application target
add_executable(image_manager src/main.cpp src/image_manager.cpp)
target_link_libraries(image_manager ${OpenCV_LIBS})

# Add the test target
add_executable(image_manager_test test/image_manager_test.cpp src/image_manager.cpp)
target_link_libraries(image_manager_test ${OpenCV_LIBS} GTest::GTest GTest::Main)