// include/game_utils.h
#ifndef GAME_UTILS_H
#define GAME_UTILS_H

#include <stdio.h>

// Объявления функций
int wordsCnt(const char *filename, char words[MAX_WORDS][MAX_LEN]);
void save_stats(const char name[25], double accuracy, double wpm, int total_len, int error, double time, double score);
FILE *openFile(const char *filename); // Объявление openFile, если оно используется вне game_utils.c

#endif // GAME_UTILS_H