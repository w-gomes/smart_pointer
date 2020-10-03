project(tests CXX)

find_package(Catch2 REQUIRED)

add_executable(${PROJECT_NAME} main-test.cpp test-unique-ptr.cpp)
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_SOURCE_DIR}/unique_ptr/)
target_link_libraries(${PROJECT_NAME} PUBLIC unique_ptr::unique_ptr Catch2::Catch2)

include(CTest)
include(Catch)
catch_discover_tests(tests)

# add_test(NAME ${PROJECT_NAME} COMMAND ${PROJECT_NAME})
