add_executable(test_runner
    test_main.c
)

find_package(cmocka REQUIRED)

target_include_directories(test_runner PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/../include
    ${CMAKE_CURRENT_SOURCE_DIR}/../src
)

target_link_libraries(test_runner PRIVATE
    typefusion_core
    ${CMOCKA_LIBRARIES}
)

add_test(NAME typefusionTests COMMAND test_runner)