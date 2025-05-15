#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <termios.h>
#include <unistd.h>
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

void grtFunc(){
    
}

int main(int, char**){
    
    FILE *file;
    char words[MAX_WORDS][MAX_LEN];
    int word_count = 0;
    int random_idx;
    int curr_idx = 0;

    

    //while (flag)
    //{
        int diff;
        int mode;
        srand(time(NULL));
        printf("Welcome to");
        printf(COLOR_EMERALD" Type"COLOR_RESET);
        printf(COLOR_DARK_RED "Fusion" COLOR_RESET);
        printf(" — the ultimate typing test!\n");
        printf("Choose difficulty:\n easy(1)     normal(2)       hard(3)\n >");
        while (scanf("%d", &diff) != 1 || diff < 1 || diff > 3)
        {
            printf("Inncorrect input. Please, input digit 1 ... 3: ");
            int c;
            while ((c = getchar()) != '\n' && c != EOF) { }
        }
        switch (diff)
        {
        case 1:
            char filename[] = "/home/jorik/Документы/Programming-C/semestr2/typefusion/words.txt";
            file = openFile(filename);
            if (file == NULL){
                return 1;
            }
            while(fgets(words[word_count], MAX_LEN, file) != NULL && word_count < MAX_WORDS){
                words[word_count][strcspn(words[word_count], "\n")] = 0;
                word_count++;
            }
            fclose(file);
            if(word_count == 0){
                printf("File is empty!\n");
                return 0;
            } 
        case 2:
            char filename2[] = "/home/jorik/Документы/Programming-C/semestr2/typefusion/words2.txt";
            file = openFile(filename2);
            if (file == NULL){
                return 1;
            }
            while(fgets(words[word_count], MAX_LEN, file) != NULL && word_count < MAX_WORDS){
                words[word_count][strcspn(words[word_count], "\n")] = 0;
                word_count++;
            }
            fclose(file);
            if(word_count == 0){
                printf("File is empty!\n");
                return 0;
            } 
        case 3:
            char filename3[] = "/home/jorik/Документы/Programming-C/semestr2/typefusion/words3.txt";
            file = openFile(filename3);
            if (file == NULL){
                return 1;
            }
            while(fgets(words[word_count], MAX_LEN, file) != NULL && word_count < MAX_WORDS){
                words[word_count][strcspn(words[word_count], "\n")] = 0;
                word_count++;
            }
            fclose(file);
            if(word_count == 0){
                printf("File is empty!\n");
                return 0;
            } 
        }
        printf("Choose mode:\n short(1)     medium(2)       long(3)\n >");
        while (scanf("%d", &mode) != 1 || mode < 1 || mode > 3)
        {
            printf("Inncorrect input. Please, input digit 1 ... 3: ");
            int c;
            while ((c = getchar()) != '\n' && c != EOF) { }
        }
        int c;
        while ((c = getchar()) != '\n' && c != EOF) {}
        printf("Type this:\n");
        char user_input[MAX_LEN];
        int error = 0;
        switch (mode)
        {
        case 1:
            char text[SHORT][MAX_LEN];
            int total_len;
            for (int i = 0; i < SHORT; i++)
            {
                random_idx = rand() % word_count;
                strcpy(text[i], words[random_idx]);
                printf("%s ", text[i]);
                total_len += strlen(text[i]);
            }
            total_len = total_len + (SHORT - 1);
            printf("\n");

            for (int i = 0; i < SHORT; i++){
                int j = 0;
                int last_pos = 0;
                char input[MAX_LEN] = {0};
                int len_input;

                while(j < strlen(text[i]) && len_input <= total_len)
                {
                    int c = getch();
                    len_input++;
                    if (c == 127 || c == 8) { 
                        if (last_pos > j) {
                            last_pos--;
                            len_input--;
                            printf("\b \b");
                        }
                    }
                    else if (c != EOF || c != '\n'){
                        input[last_pos] = c;
                        if (c == text[i][j])
                        {
                            printf(COLOR_GREEN "%c" COLOR_RESET, (char)c);
                            j++;  
                        } else {
                            printf(COLOR_RED "%c" COLOR_RESET, text[i][j]); 
                            error += 1;
                            }
                        last_pos++;
                    }       
                }
                int c = getch();
                if (c == ' ') {
                    printf(" ");
                    continue;
                } else printf(COLOR_BRIGHT_RED "%c" COLOR_RESET, (char)c); 
            }
            if (error == 0)
            {
                printf("\nResults: " COLOR_GREEN"\n[NICE!]" COLOR_RESET);    
            }
            else printf("\nReusluts: " COLOR_RED"\n[BAD!] Erorrs: %d" COLOR_RESET, error);
            while ((c = getchar()) != '\n' && c != EOF) { }
            break;

        case 2:
        char text2[MEDIUM][MAX_LEN];
        for (int i = 0; i < MEDIUM; i++)
        {
            random_idx = rand() % word_count;
            strcpy(text[i], words[random_idx]);
            printf("%s ", text[i]);
        }
        printf("\n> ");

        for (int i = 0; i < MEDIUM; i++){
            int j = 0;
            int last_pos = 0;
            char input[MAX_LEN] = {0};

            while(j < strlen(text[i]))
            {
                int c = getch();
                if (c == 127 || c == 8) { 
                    if (last_pos > j) {
                        last_pos--;
                        printf("\b \b");
                    }
                }
                else if (c != EOF || c != '\n'){
                    input[last_pos] = c;
                    if (c == text[i][j])
                    {
                        printf(COLOR_GREEN "%c" COLOR_RESET, (char)c);
                        j++;  
                    } else {
                        printf(COLOR_RED "%c" COLOR_RESET, text[i][j]); 
                        error += 1;
                        }
                    last_pos++;
                    fflush(stdout);
                }       
            }
            int c = getch();
            if (c == ' ') {
                printf(" ");
                continue;
            } else printf(COLOR_RED "%c" COLOR_RESET, (char)c); 
        }
        if (error == 0)
        {
            printf("\nResults: " COLOR_GREEN"\n[NICE!]" COLOR_RESET);    
        }
        else printf("\nReusluts: " COLOR_RED"\n[BAD!] Erorrs: %d" COLOR_RESET, error);
        while ((c = getchar()) != '\n' && c != EOF) { }
        break;
        case 3:
            char text3[LONG][MAX_LEN];
            for (int i = 0; i < LONG; i++)
            {
                random_idx = rand() % word_count;
                strcpy(text[i], words[random_idx]);
                printf("%s ", text[i]);
            }
            printf("\n> ");

            for (int i = 0; i < LONG; i++){
                int j = 0;
                int last_pos = 0;
                char input[MAX_LEN] = {0};

                while(j < strlen(text[i]))
                {
                    int c = getch();
                    if (c == 127 || c == 8) { 
                        if (last_pos > j) {
                            last_pos--;
                            printf("\b \b");
                        }
                    }
                    else if (c != EOF || c != '\n'){
                        input[last_pos] = c;
                        if (c == text[i][j])
                        {
                            printf(COLOR_GREEN "%c" COLOR_RESET, (char)c);
                            j++;  
                        } else {
                            printf(COLOR_RED "%c" COLOR_RESET, text[i][j]); 
                            error += 1;
                            }
                        last_pos++;
                    }       
                }
                int c = getch();
                if (c == ' ') {
                    printf(" ");
                    continue;
                } else printf(COLOR_RED "%c" COLOR_RESET, (char)c); 
            }
            if (error == 0)
            {
                printf("\nResults: " COLOR_GREEN"\n[NICE!]" COLOR_RESET);    
            }
            else printf("\nReusluts: " COLOR_RED"\n[BAD!] Erorrs: %d" COLOR_RESET, error);
            while ((c = getchar()) != '\n' && c != EOF) { }
            break;
        }
}
