cmake_minimum_required(VERSION 3.27.0)
project(btree VERSION 0.1.0 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 17)

include_directories(${CMAKE_SOURCE_DIR}/btree/include)

set(SOURCE
  # ${CMAKE_SOURCE_DIR}/src/xxx.cpp
)

add_executable(${PROJECT_NAME} ${SOURCE} ${CMAKE_SOURCE_DIR}/btree/src/main.cpp)

# target_compile_options(${PROJECT_NAME} PRIVATE -Wall)

# Google Test setup
set(TEST_PROJECT_NAME test_${PROJECT_NAME})
add_subdirectory(${CMAKE_SOURCE_DIR}/libs/googletest)
set(TEST_FILES
  ${CMAKE_SOURCE_DIR}/btree/test/test_btree.cpp
  ${CMAKE_SOURCE_DIR}/btree/test/test_is_comparable.cpp
)
add_executable(${TEST_PROJECT_NAME} ${TEST_FILES} ${SOURCE})
target_link_libraries(${TEST_PROJECT_NAME} gtest gtest_main)
enable_testing()
add_test(NAME BTreeTest COMMAND ${TEST_PROJECT_NAME} --gtest_filter=BTreeTest.*)
add_test(NAME IsComparableTest COMMAND ${TEST_PROJECT_NAME} --gtest_filter=IsComparable.*)
