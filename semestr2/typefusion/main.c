#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <termios.h>
#include <unistd.h>
#include <math.h>
#include <time.h>

#define MAX_LEN 20
#define MAX_WORDS 852

#define SHORT 5
#define MEDIUM 10
#define LONG 20

#define COLOR_GREEN "\033[32m"
#define COLOR_RED "\e[0;91m"
#define COLOR_BRIGHT_RED    "\e[1;31m"
#define COLOR_DARK_RED     "\033[38;5;196m"
#define COLOR_EMERALD      "\033[38;5;42m"
#define COLOR_RESET "\033[0m"

bool flag = true;

FILE *openFile(const char *filename){
    FILE *file = fopen(filename, "r");
    if(file == NULL){
        perror("Error: file can't open! Ooops!!!");
        return NULL;
    }
    return file;
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

void grtFunc(){

    printf("Welcome to");
    printf(COLOR_EMERALD" Type"COLOR_RESET);
    printf(COLOR_DARK_RED "Fusion" COLOR_RESET);
    printf(" — the ultimate typing test!\n");

}

void printMenu() {
    system("cls");
    grtFunc();
    printf("1. Play\n");
    printf("2. Difficulty\n");
    printf("3. Mode\n");
    printf("4. Text size\n");
    printf("5. Exit\n");
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
    while (scanf("%d", &value) != 1 || value < 1 || value > 5)
    {
        printf("Incorrect input. Try again: ");
        int c;
        while ((c = getchar()) != '\n' && c != EOF) { }
    }
    return value;

}

int wordsCnt(const char *filename, char words[MAX_WORDS][MAX_LEN]){

    FILE *file = openFile(filename);
    int word_count = 0;

    if (file)
    {
        while(fgets(words[word_count], MAX_LEN, file) != NULL && word_count < MAX_WORDS){
            words[word_count][strcspn(words[word_count], "\n")] = 0;
            word_count++;
        }
    }   

    return word_count;
}

int bckSpace(int last_pos, int len_input, int j){
    if (last_pos > j) {
        last_pos--;
        len_input--;
        printf("\b \b");
    }
    return last_pos, len_input;
}

int regFunc(int i, int j, int last_pos, int len_input, char text[SHORT][MAX_LEN], int total_len, char input[MAX_LEN], int error){

    while(j < strlen(text[i]) && len_input < total_len){
    int c = getch();
    len_input++;

    if (c == 127 || c == 8) { 
        bckSpace(last_pos, len_input, j);
    }
    else if (c != EOF || c != '\n'){
        input[last_pos] = c;
        if (c == text[i][j]){
            printf(COLOR_GREEN "%c" COLOR_RESET, (char)c);
            j++;  
        } else {
            printf(COLOR_RED "%c" COLOR_RESET, c); 
            error ++;
            }
        last_pos++;
        }       
    }
}

int modeDifficulty(char words[MAX_WORDS][MAX_LEN]){
    int word_count = 0;
    printf("Choose difficulty:\n easy(1)     normal(2)       hard(3)\n ");
    switch (choiceFunc()){
    case 1:{
        char filename[] = "/home/jorik/Документы/Programming-C/semestr2/typefusion/words.txt";
        word_count = wordsCnt(filename, words);
        return word_count;
    }
    case 2:{
        char filename[] = "/home/jorik/Документы/Programming-C/semestr2/typefusion/words2.txt";
        word_count = wordsCnt(filename, words);
        return word_count;
    }
    case 3:{
        char filename[] = "/home/jorik/Документы/Programming-C/semestr2/typefusion/words3.txt";
        word_count = wordsCnt(filename, words);
        return word_count;
    }
    }
    if(word_count == 0) {
        printf("No words loaded! Exiting...\n");
        return 1;
    }
}

int modeSize(){
    
}

void modePlay(){

}

void endGame(int error){

    if (error == 0)
    {
        printf("\nResults: " COLOR_GREEN"\n[NICE!]\n" COLOR_RESET);    
    }

    else printf("\nReusluts: " COLOR_RED"\n[BAD!] Erorrs: %d\n" COLOR_RESET, error);
}



int main(int, char**){
    
    FILE *file;
    char words[MAX_WORDS][MAX_LEN];
    int curr_idx = 0;
    int random_idx;
    int diff;
    int mode;
    int c;
    char user_input[MAX_LEN];
    int word_count;
    int error = 0;

    srand(time(NULL));

    //while (flag)
    //{

        printMenu();

        // switch (navMenu()) {
        //     case 1:
        //         printf("HELLO 1");
        //         break;
        
        //     case 2:
        //         printf("HELLO 2");
        //         break;
        
        //     case 3:
        //         printf("HELLO 3");
        //         break;
        
        //     case 4:
        //         printf("HELLO 4");
        //         break;
        //     case 5:
        //         printf("BUY 5");
        //         break;
        // }

        //words difficulty init
        word_count = modeDifficulty(words);

        clearBuff();
        printf("Choose mode:\n short(1)     medium(2)       long(3)\n\n");
        switch (choiceFunc())
        {
        case 1:{

            char text[SHORT][MAX_LEN];
            int total_len = 0;

            for (int i = 0; i < SHORT; i++){
                random_idx = rand() % word_count;
                strcpy(text[i], words[random_idx]);
                printf("%s ", text[i]);
                total_len += strlen(text[i]);
            }

            total_len += SHORT - 1;
            printf("\n");
            clearBuff();

            for (int i = 0; i < SHORT; i++){

                int j = 0;
                int last_pos = 0;
                char input[MAX_LEN] = {0};
                int len_input = 0;

                regFunc(i, j, last_pos, len_input, text, total_len, input, error);
  
                if (i < SHORT - 1){
                    int c = getch();
                    if (c == ' ' && len_input < total_len) {
                        printf(" ");
                        len_input++;
                    } else{
                        printf(COLOR_BRIGHT_RED "%c" COLOR_RESET, (char)c); 
                        error++;
                    }
                }                
            }
            endGame(error);
            clearBuff();
            break;
        }

        case 2:{

            char text[MEDIUM][MAX_LEN];
            int total_len = 0;

            for (int i = 0; i < MEDIUM; i++){

                random_idx = rand() % word_count;
                strcpy(text[i], words[random_idx]);
                printf("%s ", text[i]);
                total_len += strlen(text[i]);

            }

            total_len += MEDIUM - 1;
            printf("\n");
            clearBuff();

            for (int i = 0; i < MEDIUM; i++){

                int j = 0;
                int last_pos = 0;
                char input[MAX_LEN] = {0};
                int len_input = 0;

                while(j < strlen(text[i]) && len_input <= total_len)
                {
                    int c = getch();
                    
                    len_input++;
                    if (c == 127 || c == 8) { 
                        if (last_pos > j) {
                            last_pos--;
                            printf("\b \b");
                        }
                    }
                    else if (c != EOF || c != '\n'){
                        input[last_pos] = c;
                        if (c == text[i][j]){

                            printf(COLOR_GREEN "%c" COLOR_RESET, (char)c);
                            j++;  

                        } else {
                            printf(COLOR_RED "%c" COLOR_RESET, c); 
                            error ++;
                        }
                        last_pos++;
                    }       
                }
                if (i < MEDIUM - 1){
                    int c = getch();
                    if (c == ' ' && len_input < total_len) {
                        printf(" ");
                        len_input++;
                    } else{
                        printf(COLOR_BRIGHT_RED "%c" COLOR_RESET, (char)c); 
                        error++;
                    }
                }  
            }
            endGame(error);
            break;
        }
        case 3:{

            char text[LONG][MAX_LEN];
            int total_len;

            for (int i = 0; i < LONG; i++){

                random_idx = rand() % word_count;
                strcpy(text[i], words[random_idx]);
                printf("%s ", text[i]);
                total_len += strlen(text[i]);

            }
            total_len += LONG - 1;
            printf("\n");
            clearBuff();

            for (int i = 0; i < LONG; i++){

                int j = 0;
                int last_pos = 0;
                char input[MAX_LEN] = {0};
                int len_input = 0;

                while(j < strlen(text[i])){

                    int c = getch();
                    len_input++;

                    if (c == 127 || c == 8) { 
                        if (last_pos > j) {
                            last_pos--;
                            printf("\b \b");
                        }
                    }

                    else if (c != EOF || c != '\n'){

                        input[last_pos] = c;
                        if (c == text[i][j]){
                            printf(COLOR_GREEN "%c" COLOR_RESET, (char)c);
                            j++;  
                        } else {
                            printf(COLOR_RED "%c" COLOR_RESET, c); 
                            error += 1;
                        }
                        last_pos++;
                    }       
                }
                if (i < MEDIUM - 1){
                    int c = getch();
                    if (c == ' ' && len_input < total_len) {
                        printf(" ");
                        len_input++;
                    } else{
                        printf(COLOR_BRIGHT_RED "%c" COLOR_RESET, (char)c); 
                        error++;
                    }
                } 
            }
            endGame(error);
            break;
            }
        }
}
