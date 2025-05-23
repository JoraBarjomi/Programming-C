#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <termios.h>
#include <unistd.h>
#include <math.h>
#include <time.h>
#include "main.h"
// #include "game_utils.h"

bool flag = true;

int main(int, char**){

        FILE *file;
        char words[MAX_WORDS][MAX_LEN];
        char text[SHORT][MAX_LEN];
        char user_input[MAX_LEN];
        int word_count = 0;
        int error = 0;
        int total_len = 0;
        int time_limit = 10;
        int c, mode, diff, choice, random_idx;
        char playerName[25];

        const char *curret_difficulty = "../include/words.txt";
        int text_size = SHORT;

        srand(time(NULL));

        printf("Enter your name: ");
        fgets(playerName, sizeof playerName, stdin);
        playerName[strcspn(playerName, "\n")] = '\0';

        grtFunc(playerName);

        while (flag){
        printMenu(playerName);

        switch (navMenu()) {
            
            case 1: //play
                modePlay(playerName, total_len, text, words, word_count, text_size, curret_difficulty, time_limit);
                break;

            case 2: //difficulty
                word_count = modeDifficulty(words);
                clearBuff();
                break;

            case 3: //mode
                printf("Time limit:     15(1)   30(2)   60(3)\n>");
                choice = choiceFunc();

                if (choice == 1) {

                    printf("Time set: 15\n");
                    time_limit = 15;

                } else if (choice == 2) {

                    printf("Time set: 30\n");
                    time_limit = 30;

                } else {

                    printf("Time set: 60\n");
                    time_limit = 60;

                }
                clearBuff();
                break;

            case 4: // text size
                choice = modeSize(words);
                if (choice == 1) {
                    text_size = SHORT;
                } else if (choice == 2) {
                    text_size = MEDIUM;
                } else {
                    text_size = LONG;
                }
                clearBuff();
                break;       
                    
            case 5: //print stats
                char buff[100];
                printf("Stats of all players:\n");
                FILE *stats_file;
                stats_file = fopen("../include/stats.txt", "r");
                    if (stats_file){
                        while(fgets(buff, sizeof(buff), stats_file) != NULL){
                            printf("%s", buff);
                        }
                    }
                    break;

            case 6: //exit
                printf("GG!");
                sleep(1);
                flag = false;
        }
    }
}


int getch(void) {
    struct termios oldt, newt;
    int ch;

    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);

    ch = getchar();

    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    return ch;
}

void clearBuff(){

    int c;
    while ((c = getchar()) != '\n' && c != EOF) { }

}

void grtFunc(char name[25]){

    printf("Hello, %s! Welcome to", name);
    printf(COLOR_EMERALD" Type"COLOR_RESET);
    printf(COLOR_DARK_RED "Fusion" COLOR_RESET);
    printf(" — the ultimate typing test!\n");

}

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
    stats_file = fopen("../include/stats.txt", "a");

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

void endGame(char name[25], int error, double time, int total_len, int len_input, int text_size){

    double accuracy = ((double)len_input / total_len) * 100;
    double score = (((len_input - error) / time) / total_len) * 100;
    double wpm = ((double)len_input / 5) / time;

    printf("\nStats:");
    if (error < 3){

        printf(COLOR_GREEN"\n[NICE]\n" COLOR_RESET COLOR_EMERALD"Time: %.0f seconds\nAccuracy: %.0f" "\nEntered chars: %d" "\nWpM: %.2f" "\nTotal score: %.2f\n"COLOR_RESET, time, accuracy, len_input, wpm, score);
        fflush(stdout);

    } else if (error <= 5){

        printf(COLOR_YELLOW"\n[GOOD]\n" COLOR_RESET COLOR_BRIGHT_RED"Time: %.0f seconds\nAccuracy: %.0f" "\nEntered chars: %d" "\nWpM: %.2f" "\nTotal score: %.2f\n"COLOR_RESET, time, accuracy, len_input, wpm, score);
        fflush(stdout);

    } else{

        printf(COLOR_RED"\n[BAD]\nErorrs: %d\n" COLOR_RESET COLOR_DARK_RED"Time: %.0f seconds\nAccuracy: %.0f\nEntered chars: %d\nWpM: %.2f\nTotal score: %.2f\n"COLOR_RESET, error, time, accuracy, len_input, wpm, score);
        fflush(stdout);

    }

    printf("\n");
    save_stats(name, accuracy, wpm, total_len, error, time, score);

}


void printMenu(char name[25]) {

    printf("1. Play\n");
    printf("2. Difficulty\n");
    printf("3. Mode\n");
    printf("4. Text size\n");
    printf("5. Stats\n");
    printf("6. Exit\n");
    printf(">");

}


int choiceFunc(){

    int value;
    while (scanf("%d", &value) != 1 || value < 1 || value > 3)
    {
        printf("Incorrect input. Try again: ");
        int c;
        while ((c = getchar()) != '\n' && c != EOF) { }
    }
    return value;

}


int navMenu(){

    int value;
    while (scanf("%d", &value) != 1 || value < 1 || value > 6)
    {
        printf("Incorrect input. Try again: ");
        int c;
        while ((c = getchar()) != '\n' && c != EOF) { }
    }
    return value;

}


int bckSpace(int *last_pos, int *len_input, int j){

    if (*last_pos > j) {

        (*last_pos)--;
        (*len_input)--;
        printf("\b \b");

    }
}


int modeDifficulty(char words[MAX_WORDS][MAX_LEN]){

    int word_count = 0;

    printf("Choose difficulty:\n easy(1)     normal(2)       hard(3)\n ");

    switch (choiceFunc()){

        case 1:{
            char filename[] = "../include/words.txt";
            word_count = wordsCnt(filename, words);
            return word_count;
        }

        case 2:{
            char filename[] = "../include/words2.txt";
            word_count = wordsCnt(filename, words);
            return word_count;
        }

        case 3:{
            char filename[] = "../include/words3.txt";
            word_count = wordsCnt(filename, words);
            return word_count;
        }
    }
    if (word_count == 0) {

        printf("No words loaded! Exiting...\n");
        return 1;

    }
}


int modeSize(char words[MAX_WORDS][MAX_LEN]){
    int random_idx;
    int error = 0;

    printf("Choose mode:\n short(1)     medium(2)       long(3)\n\n");
    switch (choiceFunc()){

        case 1:{
            char text[SHORT][MAX_LEN];
            return 1;
        }

        case 2:{
            char text[MEDIUM][MAX_LEN];
            return 2;
        }
        
        case 3:{
            char text[LONG][MAX_LEN];
            return 3;
        }
        
        default:{
            char text[SHORT][MAX_LEN];
        }
    }
}


int modePlay(char player_name[25], int total_len, char text[][MAX_LEN], char words[MAX_WORDS][MAX_LEN], int word_count, int text_size, const char *filename, int time_limit){

    time_t start_time;
    time_t current_time;
    double passed_time = 0;
    int random_idx;
    int error = 0;
    int last_pos = 0;    
    int len_input = 0;
    int right_input = 0;
    total_len += text_size - 1;
    bool time_left = true;
    printf("\n");
    clearBuff();

    if (word_count == 0){
        word_count = wordsCnt(filename, words);
    }

    for (int i = 0; i < text_size; i++){
        random_idx = rand() % word_count;
        strcpy(text[i], words[random_idx]);
        printf("%s ", text[i]);
        total_len += strlen(text[i]);
    }
    printf("\n\n");

    start_time = time(NULL);

    while (time_left == true){

        for (int i = 0; i < text_size && time_left; i++){

            int j = 0;
            char input[MAX_LEN] = {0};

            current_time = time(NULL);
            passed_time = difftime(current_time, start_time);
            if (passed_time >= time_limit){
                printf(COLOR_YELLOW"\nTime's up! GG\n"COLOR_RESET);
                time_left = false;
                break;
            }

            while(j < strlen(text[i]) && len_input < total_len && time_left){

                int c = getch();
                len_input++;
                if (last_pos < MAX_LEN - 1) {
                    input[last_pos++] = c;
                }

                if (c == 127 || c == 8) {
                    bckSpace(&last_pos, &len_input, j);
                }
                else if (c != EOF && c != '\n'){

                    if (last_pos < MAX_LEN - 1) {
                        input[last_pos++] = c;
                    }

                    if (c == text[i][j]){
                        printf(COLOR_GREEN "%c" COLOR_RESET, (char)c);
                        j++;
                        right_input++;
                    } else {
                        printf(COLOR_RED "%c" COLOR_RESET, c);
                        error++;
                    }
                    last_pos++;
                }

            }
            if (!time_left) break;

            if (i < text_size - 1){
                int c = getch();
                if (c == ' ' && len_input < total_len) {
                    printf(" ");
                    len_input++;
                    right_input++;
                } else{
                    printf(COLOR_BRIGHT_RED "%c" COLOR_RESET, (char)c);
                    error++;
                }
            }
        }

        double accuracy = ((double)right_input / total_len) * 100;
        if (accuracy > 90){

            if(filename == "../include/words.txt") filename = "../include/words2.txt";
            else filename = "../include/words3.txt";

            word_count = wordsCnt(filename, words);
            printf(COLOR_EMERALD"\n\nThe difficulty has been increased! Accuracy: %.2f\n"COLOR_RESET, accuracy);

            for (int i = 0; i < text_size; i++){
                random_idx = rand() % word_count;
                strcpy(text[i], words[random_idx]);
                printf("%s ", text[i]);
                total_len += strlen(text[i]);
            }
            printf("\n\n");
        } else {
            time_left = false;
        }
    }

    passed_time = difftime(current_time, start_time);
    endGame(player_name, error, passed_time, total_len, right_input, text_size);
}