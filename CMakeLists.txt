cmake_minimum_required(VERSION 3.20)
project(LFQSort LANGUAGES CXX)

# Set C++ standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Declare the header-only library
add_library(lfqsort INTERFACE)
target_include_directories(lfqsort INTERFACE include)

# Link libfork if needed (assuming libfork is a submodule in external/libfork)
add_subdirectory(vendor/libfork)
target_link_libraries(lfqsort INTERFACE libfork::libfork)

# Optional: Add tests
enable_testing()
add_executable(unit_tests tests/test_qsort.cc)
target_link_libraries(unit_tests PRIVATE lfqsort)
add_test(NAME test_qsort COMMAND unit_tests)
