#include <stdio.h>

void SelectSort(int n, int A[]){

    for(int i = 0; i < n - 1; i++){
        int min = i;
        for(int j = i + 1; j < n; j++){
            if( A[j] < A[min] ){
                min = j;
            }
        }
        if( min != i){
            int tmp = A[i];
            A[i] = A[min];
            A[min] = tmp;
        }
    }
} 

int main(int, char**){
    int a[] = {4, 2};
    printf("Hello, from sort!\n"); //werwerwerwerwerwer
    printf("qwerty\n"); //qweqweqweqweqwe
    SelectSort(3, a);
}
