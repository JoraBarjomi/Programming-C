#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <termios.h>
#include <unistd.h>
#include <math.h>
#include <time.h>

//const
#define MAX_LEN 20
#define MAX_WORDS 852
#define SHORT 5
#define MEDIUM 10
#define LONG 20

//colors
#define COLOR_GREEN "\033[32m"
#define COLOR_RED "\e[0;91m"
#define COLOR_YELLOW "\033[1;33m"
#define COLOR_BRIGHT_RED    "\e[1;31m"
#define COLOR_DARK_RED     "\033[38;5;196m"
#define COLOR_EMERALD      "\033[38;5;42m"
#define COLOR_RESET "\033[0m"

FILE *openFile(const char *filename);
int getch(void);
void clearBuff();
int bckSpace(int *last_pos, int *len_input, int j);
void grtFunc(char name[25]);


void save_stats(const char name[25], double accuracy, double wpm, int total_len, int error, double time,  double score);
void endGame(char name[25], int error, double time, int total_len, int len_input, int text_size);
void printMenu(char name[25]);
int choiceFunc();
int navMenu();


int wordsCnt(const char *filename, char words[MAX_WORDS][MAX_LEN]);
int modeDifficulty(char words[MAX_WORDS][MAX_LEN]);
int modeSize(char words[MAX_WORDS][MAX_LEN]);
int modePlay(char player_name[25], int total_len, char text[][MAX_LEN], char words[MAX_WORDS][MAX_LEN], int word_count, int text_size, const char *filename, int time_limit);