cmake_minimum_required(VERSION 3.16)
project(geoproc_playground)



# if(CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)
# include(CTest)
# endif()
# if(CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME AND BUILD_TESTING)
# add_subdirectory(tests)
# endif()
if(CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)
    add_subdirectory(tests)
endif()

add_library(vec_math vec_math.c vec_math.h)
target_compile_features(vec_math PUBLIC c_std_11)
set_target_properties(vec_math PROPERTIES C_EXTENSIONS OFF)

add_executable(geoproc_playground main.c)
target_link_libraries(geoproc_playground vec_math)
