cmake_minimum_required(VERSION 3.13 FATAL_ERROR)

project("webLvgl")

include_directories(.)

add_subdirectory(lvgl)
add_subdirectory(lv_drivers)

add_executable(webLvgl webLvgl.cpp)
target_compile_options(webLvgl PUBLIC
        -sUSE_SDL=2
        -O3
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


#FIND_PACKAGE(Python3)
#set(PYTHON ${Python3_EXECUTABLE} CACHE STRING "Python path")
#set(EMSCRIPTEN_ROOT $ENV{EMSDK}/upstream/emscripten CACHE STRING "Emscripten path")
#set(CMAKE_TOOLCHAIN_FILE ${EMSCRIPTEN_ROOT}/cmake/Modules/Platform/Emscripten.cmake)
#set(WEBIDL_BINDER_SCRIPT ${EMSCRIPTEN_ROOT}/tools/webidl_binder.py)

#set(WEBLVGL_FRONT_MATTER_FILE ${CMAKE_CURRENT_SOURCE_DIR}/front-matter.js)
#set(WEBLVGL_HEADER_FILE ${CMAKE_CURRENT_SOURCE_DIR}/webLvgl.h)
#set(WEBLVGL_IDL_FILE ${CMAKE_CURRENT_SOURCE_DIR}/webLvgl.idl)
#set(WEBLVGL_ONLOAD_FILE ${CMAKE_CURRENT_SOURCE_DIR}/onload.js)
#set(LVGL_SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/lvgl/src/)
#set(WEBLVGL_CPP ${CMAKE_CURRENT_SOURCE_DIR}/webLvgl.cpp)


#set(LVGL_TARGETS lvgl lv_drivers)
#foreach (_TARGET ${LVGL_TARGETS})
#    list(APPEND LVGL_LIBS $<TARGET_FILE:${_TARGET}>)
#endforeach ()

# Disable lvgl graphical benchmarks
#set(USE_GRAPHICAL_BENCHMARK OFF)

# Disable lvgl GLUT
#set(USE_GLUT OFF)

# Build Release by default
#set(CMAKE_BUILD_TYPE Release CACHE STRING "Build Type")
#
## Default is 64*1024*1024 = 64MB
#set(TOTAL_MEMORY 67108864 CACHE STRING "Total Memory")
#
## Enable for resizable heap, with some amount of slowness
#set(ALLOW_MEMORY_GROWTH 0 CACHE STRING "Allow Memory Growth")

#set(EMCC_ARGS
#        --extern-pre-js ${WEBLVGL_FRONT_MATTER_FILE}
#        --llvm-lto 1
#        --post-js ${WEBLVGL_ONLOAD_FILE}
#        -O1
#        -s ALLOW_MEMORY_GROWTH=${ALLOW_MEMORY_GROWTH}
#        -s ALLOW_TABLE_GROWTH=1
#        -s EXPORTED_FUNCTIONS=["_malloc"]
#        -s EXPORTED_RUNTIME_METHODS=["UTF8ToString"]
#        -s EXTRA_EXPORTED_RUNTIME_METHODS=["addFunction"]
#        -s EXPORT_NAME="WebLvgl"
#        -s MODULARIZE=1
#        -s NO_EXIT_RUNTIME=1
#        -s NO_FILESYSTEM=1
#        -s TOTAL_MEMORY=${TOTAL_MEMORY}
#        -I${LVGL_SRC_DIR}
#        -s USE_SDL=2
#        )
#
#if (${CLOSURE})
#    # Ignore closure errors about the lvgl Node class
#    # (Node is a DOM thing too)
#    LIST(APPEND EMCC_ARGS
#            --closure 1
#            -s IGNORE_CLOSURE_COMPILER_ERRORS=1)
#else ()
#    LIST(APPEND EMCC_ARGS
#            -s NO_DYNAMIC_EXECUTION=1)
#endif ()
#
#
#set(EMCC_JS_ARGS ${EMCC_ARGS}
#        -s AGGRESSIVE_VARIABLE_ELIMINATION=1
#        -s ELIMINATE_DUPLICATE_FUNCTIONS=1
#        -s LEGACY_VM_SUPPORT=1
#        -s SINGLE_FILE=1
#        -s WASM=0)
#
#set(EMCC_WASM_ARGS ${EMCC_ARGS}
#        -s BINARYEN_IGNORE_IMPLICIT_TRAPS=1
#        -s WASM=1)
#
#set(EMCC_GLUE_ARGS
#        -c
#        -I${LVGL_SRC_DIR}
#        -include${WEBLVGL_HEADER_FILE})


#######################################

#######################################
#add_custom_command(
#        OUTPUT webLvgl.js
#        COMMAND ${EMSCRIPTEN_ROOT}/emcc.bat -lembind ${WEBLVGL_CPP} ${LVGL_LIBS} ${EMCC_JS_ARGS} -o webLvgl.js
#        DEPENDS ${WEBLVGL_CPP} ${LVGL_TARGETS}
#        COMMENT "Building webLvgl javascript"
#        VERBATIM)
#add_custom_target(webLvgl-javascript ALL DEPENDS webLvgl.js)
#
#
########################################
#add_custom_command(
#        OUTPUT webLvgl.wasm.js webLvgl.wasm.wasm
#        COMMAND ${EMSCRIPTEN_ROOT}/emcc.bat -lembind ${WEBLVGL_CPP} ${LVGL_LIBS} ${EMCC_WASM_ARGS} -o webLvgl.wasm.js
#        DEPENDS ${WEBLVGL_CPP} ${LVGL_TARGETS}
#        COMMENT "Building webLvgl webassembly"
#        VERBATIM)
#add_custom_target(webLvgl-wasm ALL DEPENDS webLvgl.wasm.js webLvgl.wasm.wasm)



