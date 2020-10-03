project(unique_ptr CXX)

add_library(${PROJECT_NAME} INTERFACE)
add_library(unique_ptr::${PROJECT_NAME} ALIAS ${PROJECT_NAME})
