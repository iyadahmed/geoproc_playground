cmake_minimum_required(VERSION 3.16)
project(geoproc_playground)

find_library(LIB_MATH m)
find_package(OpenMP)

if(CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)
    add_subdirectory(tests)
endif()

add_library(vec_math vec_math.c vec_math.h)
target_compile_features(vec_math PUBLIC c_std_11)
set_target_properties(vec_math PROPERTIES C_EXTENSIONS OFF)

add_library(load_stl load_stl.c load_stl.h)
target_compile_features(load_stl PUBLIC c_std_11)
set_target_properties(load_stl PROPERTIES C_EXTENSIONS OFF)

add_executable(geoproc_playground main.c)
target_link_libraries(geoproc_playground vec_math load_stl)

if(OpenMP_C_FOUND)
    message(STATUS "Found OpenMP: ${OpenMP_C_FOUND}")
    target_link_libraries(geoproc_playground OpenMP::OpenMP_C)
endif()

if(LIB_MATH)
    message(STATUS "Found libm: ${LIB_MATH}")
    target_link_libraries(geoproc_playground ${LIB_MATH})
endif()
