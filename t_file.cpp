#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define DEFAULT_SIZE 12

void shuffle(char data[][DEFAULT_SIZE], size_t length)
{
    char target[1][DEFAULT_SIZE];
    
    while (length > 1) 
    {        
        size_t newLength = rand() % (length--);
        strcpy(target[0], data[newLength]);
        strcpy(data[newLength],data[length]);
        strcpy(data[length], target[0]);
    }
}

int fpoints(char data[][DEFAULT_SIZE], char input[][DEFAULT_SIZE], int index)
{
    if(strcmp(data[index], input[index]) == 0)
    {
        printf("Points++\n");
        return 1;
    }
    else
        return 0;
}

main()
{
    char data[][DEFAULT_SIZE] = {
        "Poshkin", "Feast", "Vamos"
        };
    
    size_t dataLength = sizeof data / sizeof *data;
    
    char input[dataLength][DEFAULT_SIZE] = {
        "Bocchi", "Nijika", "Ryou"
        };
    char dataInput[dataLength][DEFAULT_SIZE];

    srand((unsigned) time(NULL));
    
    shuffle(data, dataLength);
    
    int points = 0;
    
    for (int i = 0; i < dataLength; i++)
    {
        printf("Data [%d]: %s\n", i, data[i]);
        printf("Input[%d]: ", i);
        scanf("%s", &dataInput[i]);
        strcpy(input[i], dataInput[i]);
        points += fpoints(data, input, i);
    }

    for (int i = 0; i < dataLength; i++)
    {
        printf("Input [%d]: %s\n", i, input[i]);
    }

    if (points > 1)
        printf("You win");
    else
        printf("You lose");
}