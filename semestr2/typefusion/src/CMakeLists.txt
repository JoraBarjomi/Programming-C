add_library(typefusion_core STATIC
    game_utils.c
    # Добавьте здесь все остальные .c файлы вашей библиотеки, которые вы хотите тестировать
)

target_include_directories(typefusion_core PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/../include
)

add_executable(typefusion
    main.c
)

target_include_directories(typefusion PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/../include
)

target_link_libraries(typefusion PRIVATE
    typefusion_core
)