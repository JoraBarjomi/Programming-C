// tests/test_main.c
#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>
#include <stdio.h>
#include <string.h>
#include "../src/main.h"
#include "../src/game_utils.h" // Предполагается, что openFile и wordsCnt находятся здесь

// Тест для функции openFile
static void test_open_file_exists(void **state) {
    FILE *f = openFile("./include/main.h"); // Проверяем существующий файл
    assert_non_null(f);
    fclose(f);
}

static void test_open_file_not_exists(void **state) {
    FILE *f = openFile("non_existent_file.txt");
    assert_null(f);
}

// Тест для функции wordsCnt
static void test_words_count_empty_file(void **state) {
    FILE *tmp = fopen("test_empty.txt", "w");
    assert_non_null(tmp);
    fclose(tmp);

    char words[MAX_WORDS][MAX_LEN];
    int count = wordsCnt("test_empty.txt", words);
    assert_int_equal(count, 0);

    remove("test_empty.txt");
}

static void test_words_count_single_word(void **state) {
    FILE *tmp = fopen("test_single.txt", "w");
    assert_non_null(tmp);
    fprintf(tmp, "testword\n");
    fclose(tmp);

    char words[MAX_WORDS][MAX_LEN];
    int count = wordsCnt("test_single.txt", words);
    assert_int_equal(count, 1);
    assert_string_equal(words[0], "testword");

    remove("test_single.txt");
}

static void test_words_count_multiple_words(void **state) {
    FILE *tmp = fopen("test_multiple.txt", "w");
    assert_non_null(tmp);
    fprintf(tmp, "word1\nlongword2\nshort3\n");
    fclose(tmp);

    char words[MAX_WORDS][MAX_LEN];
    int count = wordsCnt("test_multiple.txt", words);
    assert_int_equal(count, 3);
    assert_string_equal(words[0], "word1");
    assert_string_equal(words[1], "longword2");
    assert_string_equal(words[2], "short3");

    remove("test_multiple.txt");
}

// Вам нужно будет вынести функцию save_stats в game_utils.c и включить game_utils.h
// чтобы этот тест заработал. Пример теста для save_stats был в предыдущем ответе.

int main(void) {
    const struct CMUnitTest tests[] = {
        cmocka_unit_test(test_open_file_exists),
        cmocka_unit_test(test_open_file_not_exists),
        cmocka_unit_test(test_words_count_empty_file),
        cmocka_unit_test(test_words_count_single_word),
        cmocka_unit_test(test_words_count_multiple_words),
        // cmocka_unit_test(test_save_stats), // Раскомментируйте после переноса save_stats
    };
    return cmocka_run_group_tests(tests, NULL, NULL);
}