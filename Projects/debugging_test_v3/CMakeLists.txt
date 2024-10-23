cmake_minimum_required(VERSION 3.16.0)
include($ENV{IDF_PATH}/tools/cmake/project.cmake)
project(debugging_test_v3)
idf_build_set_property(COMPILE_OPTIONS "-O0" "-ggdb3" "-g3" APPEND)