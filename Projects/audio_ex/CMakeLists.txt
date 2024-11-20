cmake_minimum_required(VERSION 3.16.0)
include($ENV{IDF_PATH}/tools/cmake/project.cmake)
set(EXTRA_COMPONENT_DIRS ../../../Developing-IoT-Projects-with-ESP32-2nd-edition-main-new/components)


add_compile_options(-fdiagnostics-color=always -Wno-write-strings)
project(audio_ex)