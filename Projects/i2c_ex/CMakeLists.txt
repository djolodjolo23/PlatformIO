cmake_minimum_required(VERSION 3.16.0)
include($ENV{IDF_PATH}/tools/cmake/project.cmake)
set(EXTRA_COMPONENT_DIRS ../../esp-idf-lib/components
../../esp-idf-lib)
add_compile_options(-fdiagnostics-color=always -Wno-write-strings)
project(i2c_ex)
