cmake_minimum_required(VERSION 3.0)
project(tree2md VERSION 1.0)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_executable(${PROJECT_NAME} main.cc)

target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_20)

# find_package(fmt CONFIG REQUIRED)
# target_link_libraries(${PROJECT_NAME} PRIVATE fmt::fmt)