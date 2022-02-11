#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int numberRand(int start, int end){
    int number = rand() % end + start;
    printf("%d - value\n", number);
    return number;
}

int main(){
    srand(time(NULL));
    int number = numberRand(1, 10), attempt;
    while(1){
        printf("try to guess the number between 1 to 10:\n");
        scanf("%d", &attempt);
        if(number == attempt)
            break;
        else if(number > attempt)
            printf("\nthe attempt is NOT correct, the number is higher that attempt\n");
            else
            printf("the attempt is NOT correct, the number is lower that attempt\n");
    }
    printf("\nthe attempt is correct, congratulations!!!\n");
    return 0;
}