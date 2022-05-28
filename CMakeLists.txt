cmake_minimum_required(VERSION 3.13 FATAL_ERROR)

project("webLvgl")

include_directories(.)

add_subdirectory(lvgl)
add_subdirectory(lv_drivers)

add_executable(webLvgl webLvgl.cpp)
target_compile_options(webLvgl PUBLIC
        -sUSE_SDL=2
        )

target_link_libraries(webLvgl lvgl lv_drivers)
target_link_options(webLvgl PUBLIC
        -sEXPORT_NAME="WebLvgl"
        -sMODULARIZE=1
        -lembind
        -sUSE_SDL=2
        -sALLOW_MEMORY_GROWTH=1
        -sALLOW_TABLE_GROWTH=1
        -sLLD_REPORT_UNDEFINED
        #        -gsource-map
        )

