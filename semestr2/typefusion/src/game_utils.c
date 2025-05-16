// src/game_utils.c
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "main.h" // Включаем main.h для определений MAX_WORDS, MAX_LEN и т.д.

FILE *openFile(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        perror("Error: file can't open! Ooops!!!");
        return NULL;
    }
    return file;
}

int wordsCnt(const char *filename, char words[MAX_WORDS][MAX_LEN]) {
    FILE *file = openFile(filename);
    int word_count = 0;

    if (file) {
        while (fgets(words[word_count], MAX_LEN, file) != NULL && word_count < MAX_WORDS) {
            words[word_count][strcspn(words[word_count], "\n")] = 0;
            word_count++;
        }
        fclose(file);
    }
    return word_count;
}

void save_stats(const char name[25], double accuracy, double wpm, int total_len, int error, double time, double score) {
    FILE *stats_file;
    stats_file = fopen("./include/stats.txt", "a");

    if (stats_file == NULL) {
        perror("Error opening stats file");
        return;
    }
    fprintf(stats_file,
        "========================\n"
        "Player        : %s\n"
        "Accuracy      : %.0f%%\n"
        "Speed         : %.2f WPM\n"
        "Chars entered : %d\n"
        "Total errors  : %d\n"
        "Time elapsed  : %.0f sec\n"
        "Overall score : %.2f\n"
        "========================\n\n",
        name,
        accuracy,
        wpm,
        total_len,
        error,
        time,
        score
    );
    fclose(stats_file);
}