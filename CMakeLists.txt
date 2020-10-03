cmake_minimum_required(VERSION 3.15)

project(main CXX)

find_package(FMT REQUIRED)

add_subdirectory(unique_ptr)

add_executable(${PROJECT_NAME} main.cpp)
target_include_directories(${PROJECT_NAME} PUBLIC unique_ptr/unique_ptr.hpp)
target_link_libraries(
  ${PROJECT_NAME} 
  PUBLIC unique_ptr::unique_ptr
         fmt::fmt-header-only
)
target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_20)

add_subdirectory(test)
enable_testing()
