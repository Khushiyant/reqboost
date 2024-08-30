# CMakeLists.txt

cmake_minimum_required(VERSION 3.4...3.18)
project(reqboost LANGUAGES CXX)

# Find Python interpreter and libraries using the new FindPython module
find_package(Python 3.10 REQUIRED COMPONENTS Interpreter Development)
# Get the pybind11 installation path using Python
execute_process(
    COMMAND python -m pybind11 --cmakedir
    OUTPUT_VARIABLE pybind11_DIR
    OUTPUT_STRIP_TRAILING_WHITESPACE
)
# Use the obtained pybind11_DIR
find_package(pybind11 REQUIRED)

# Find required packages
find_package(CURL REQUIRED)
find_package(Poco REQUIRED Foundation Net)

# Include directories
include_directories(${CMAKE_SOURCE_DIR}/include/reqboost ${CMAKE_SOURCE_DIR}/include/reqboost/bindings ${CURL_INCLUDE_DIRS} ${Poco_INCLUDE_DIRS})

# Collect all source files
file(GLOB_RECURSE SOURCES "src/*.cpp")

# Define the Python extension module
pybind11_add_module(reqboost ${SOURCES})

# Link libraries
target_link_libraries(reqboost PRIVATE ${CURL_LIBRARIES} Poco::Foundation Poco::Net)

# Set C++ standard
set_target_properties(reqboost PROPERTIES
    CXX_STANDARD 14
    CXX_STANDARD_REQUIRED YES
)
