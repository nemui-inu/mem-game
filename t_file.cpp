#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <windows.h>

#define DEFAULT_SIZE 12

void newline(int length)
{
    for (int i = 0; i < length; i++)
    {
        printf("\n");
    }
}

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

void exit()
{
    system("cls");
    printf("bye");
}

void game()
{
    char data[][DEFAULT_SIZE] = {
    "Marimbo", "Fiesta", "Vamos",
    "Tuxedo", "Palermo", "Green",
    "Standard", "Implication", "Explicit",
    "Illicit", "Impressive", "Embargo",
    "Innuendo", "Error", "Malfunction",
    "Special", "Astounding", "Jostled",
    "Shift", "Specimen", "Sigh"
    };
    size_t dataLength = sizeof data / sizeof *data;
    
    char input[dataLength][DEFAULT_SIZE];

    int prev_points, points = 0, lives = 3, gameLoop = 1, round = 1;

    srand((unsigned) time(NULL));
    
    while(gameLoop)
    {
        shuffle(data, dataLength);

        if(lives != 0)
        {
            prev_points = points;
            printf("Round: %d\n", round);
            printf("Total points: %d\n", points);
            printf("Lives:");
            for(int n = 0; n < lives; n++)
                printf(" \x03");
            printf("\n\n");
            
            for (int i = 0; i < 5; i++)
            {
                printf("Data [%d]: %s\n", i+1, data[i]);
            }

            printf("\n-\n\n");

            for (int i = 5; i > 0; i--)
            {
                printf("\r%d seconds before input", i);
                Sleep(1000);
            }

            system("cls");

            for (int i = 0; i < 5; i++)
            {
                if (lives < 1) break;
                
                printf("Input[%d]: ", i+1);
                scanf("%s", &input[i]);
                if (fpoints(data, input, i))
                {
                    points++;

                    if(lives < 3){
                        lives++;
                        printf("+\x03\n");
                    }

                    if (points >= 10 && points == prev_points + 5 )
                    {
                        printf("streak bonus (x2 score)");
                        points *= 2;
                    }
                }
                else
                {
                    printf("-\x03\n");
                    lives--;
                }
            }
        }
        else
            break;
        
        printf("Total points: %d\n", points);
            
        if (lives == 0)
        {
            printf("\nG A M E   O V E R");
            newline(2);
            printf("Press any key to retry, 'q' to quit");
            
            if(getch() == 'q')
                exit();
            else
            {
                system("cls");
                game();
            }
        }
        else
        {
            printf("You win\n");
        }
        printf("\n-\n\n");
        round++;
    }
    return;
}

main()
{
    game();
}