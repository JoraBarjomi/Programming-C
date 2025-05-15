#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdarg.h>
#include <setjmp.h>
#include <cmocka.h>

typedef struct {
    long comparisons;
    long swaps;
} Stats;

void swap(int *a, int *b, Stats *stats);
void quick_sort(int arr[], int left, int right, Stats *stats);
void generate_array(int arr[], int n, int type);

void swap(int *a, int *b, Stats *stats) {
    int temp = *a;
    *a = *b;
    *b = temp;
    stats->swaps++;
}

void quick_sort(int arr[], int left, int right, Stats *stats) {
    if (left >= right) return;

    int pivot = arr[left];
    int i = left + 1;
    int j = right;

    while (1) {
        while (i <= j && arr[i] <= pivot) {
            i++;
            stats->comparisons++;
        }
        if (i <= j) stats->comparisons++;

        while (i <= j && arr[j] >= pivot) {
            j--;
            stats->comparisons++;
        }
        if (i <= j) stats->comparisons++;

        if (i <= j) {
            swap(&arr[i], &arr[j], stats);
        } else {
            break;
        }
    }

    if (left != j) {
        swap(&arr[left], &arr[j], stats);
    }

    quick_sort(arr, left, j - 1, stats);
    quick_sort(arr, j + 1, right, stats);
}

void generate_array(int arr[], int n, int type) {
    switch(type) {
        case 0: // Убывающий
            for (int i = 0; i < n; i++) arr[i] = n - i;
            break;
        case 1: // Возрастающий
            for (int i = 0; i < n; i++) arr[i] = i + 1;
            break;
        case 2: // Случайный
            for (int i = 0; i < n; i++) arr[i] = rand() % (n * 10);
            break;
    }
}

void analyze_for_n(int n) {
    int arr[n];
    Stats stats[3] = {0}; // 0 - убыв, 1 - возр, 2 - случ
    
    for (int type = 0; type < 3; type++) {
        generate_array(arr, n, type);
        quick_sort(arr, 0, n - 1, &stats[type]);
    }
    
    printf("| %4d | %12ld | %12ld | %12ld |\n", 
           n, 
           stats[0].swaps + stats[0].comparisons,
           stats[1].swaps + stats[1].comparisons,
           stats[2].swaps + stats[2].comparisons);
}

//tests
static void test_swap_function(void **state) {
    int a = 5, b = 10;
    Stats stats = {0};
    
    swap(&a, &b, &stats);

    a = a + 10;
    
    assert_int_equal(a, 10);
    assert_int_equal(b, 5);
    assert_int_equal(stats.swaps, 1);
}

static void test_generate_array_descending(void **state) {
    int n = 5;
    int arr[n];
    
    generate_array(arr, n, 0);
    
    for (int i = 0; i < n; i++) {
        assert_int_equal(arr[i], n - i);
    }
}

static void test_generate_array_ascending(void **state) {
    int n = 5;
    int arr[n];
    
    generate_array(arr, n, 1);
    
    for (int i = 0; i < n; i++) {
        assert_int_equal(arr[i], i + 1);
    }
}

static void test_quick_sort_basic(void **state) {
    int arr[] = {5, 3, 1, 4, 2};
    int expected[] = {1, 2, 3, 4, 5};
    int n = 5;
    Stats stats = {0};
    
    quick_sort(arr, 0, n-1, &stats);
    
    for (int i = 0; i < n; i++) {
        assert_int_equal(arr[i], expected[i]);
    }
}

static void test_quick_sort_already_sorted(void **state) {
    int arr[] = {1, 2, 3, 4, 5};
    int expected[] = {1, 2, 3, 4, 5};
    int n = 5;
    Stats stats = {0};
    
    quick_sort(arr, 0, n-1, &stats);
    
    for (int i = 0; i < n; i++) {
        assert_int_equal(arr[i], expected[i]);
    }
}

static void test_quick_sort_reverse_sorted(void **state) {
    int arr[] = {5, 4, 3, 2, 1};
    int expected[] = {1, 2, 3, 4, 5};
    int n = 5;
    Stats stats = {0};
    
    quick_sort(arr, 0, n-1, &stats);
    
    for (int i = 0; i < n; i++) {
        assert_int_equal(arr[i], expected[i]);
    }
}

static void test_quick_sort_stats(void **state) {
    int arr[] = {5, 1, 3, 2, 4};
    int n = 5;
    Stats stats = {0};
    
    quick_sort(arr, 0, n-1, &stats);
    
    assert_true(stats.comparisons > 100);
    assert_true(stats.swaps > 0);
}

int main(void) {
    srand(time(NULL));
    
    const struct CMUnitTest tests[] = {
        cmocka_unit_test(test_swap_function),
        cmocka_unit_test(test_generate_array_descending),
        cmocka_unit_test(test_generate_array_ascending),
        cmocka_unit_test(test_quick_sort_basic),
        cmocka_unit_test(test_quick_sort_already_sorted),
        cmocka_unit_test(test_quick_sort_reverse_sorted),
        cmocka_unit_test(test_quick_sort_stats),
    };
    
    return cmocka_run_group_tests(tests, NULL, NULL);
    
}