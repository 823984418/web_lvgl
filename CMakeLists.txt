cmake_minimum_required(VERSION 3.13 FATAL_ERROR)

project("webLvgl")

include_directories(.)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Oz -sUSE_SDL=2 -g0")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Oz -sUSE_SDL=2 -g0")

add_subdirectory(lvgl)
add_subdirectory(lv_drivers)

add_executable(webLvgl webLvgl.cpp)

target_link_libraries(webLvgl lvgl lv_drivers)
target_link_options(webLvgl PUBLIC
        -g0
        -sEXPORT_NAME="WebLvgl"
        -flto
        -sEXIT_RUNTIME=0
        -sMODULARIZE=1
        -lembind
        -sUSE_SDL=2
        -sALLOW_MEMORY_GROWTH=1
        -sALLOW_TABLE_GROWTH=1
        -sLLD_REPORT_UNDEFINED
        -fno-exceptions
        --closure=1
        )

