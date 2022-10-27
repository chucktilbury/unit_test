project(unit_test)

set(CMAKE_C_COMPILER /usr/bin/clang)
set(CMAKE_CXX_COMPILER /usr/bin/clang++)
set(LIBRARY_OUTPUT_PATH "${PROJECT_SOURCE_DIR}/../bin")
file(MAKE_DIRECTORY "${PROJECT_SOURCE_DIR}/../bin")

add_library( ${PROJECT_NAME} STATIC
    asserts.c
    memory.c
    messages.c
    ptr_list.c
    tests.c
)

target_compile_options(${PROJECT_NAME} PRIVATE
    -Wall
    -Wextra
    $<$<CONFIG:DEBUG>:-g3>
    $<$<CONFIG:DEBUG>:-Og>
    $<$<CONFIG:DEBUG>:-DMEMORY_DEBUG>
    $<$<CONFIG:DEBUG>:-DENA_TRACE>
    $<$<CONFIG:RELEASE>:-Ofast>
    $<$<CONFIG:PROFILE>:-pg -O0>
)
