#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>

void menu();
void game_start();
void game_check();
void cls()
{
    system("cls");
}

int main()
{
    menu();
}

void game_check()
{
    int points=0;
    char mal[12] = "Malfeasance", *por = "Portruding", *jos = "Jostled",
         *gae = "Gaelet", *mor = "Morpheus", *sta = "Star", input[12];
    printf("1. %s\n2. %s\n3. %s\n4. %s\n5. %s\n", mal, por, jos, gae, mor);
    for(int i=0; i<5; i++)
    {
        printf("\nInput [%d]: ",i+1);
        scanf("%s",&input);
        printf("%s",input);
        switch(i)
        {
            case 0:
                if (input==mal)
                {
                    points++;
                    printf("\nPoints++");
                }
                break;
            case 1:
                if (input==por)
                {
                    points++;
                    printf("\nPoints++");
                }
                break;
            case 2:
                if (input==jos)
                {
                    points++;
                    printf("\nPoints++");
                }
                break;
            case 3:
                if (input==gae)
                {
                    points++;
                    printf("\nPoints++");
                }
                break;
            case 4:
                if (input==mor)
                {
                    points++;
                    printf("\nPoints++");
                }
                break;
        }
    }
    printf("\nPoints: %d",points);
    getch();
    menu();
}

void game_start()
{
    cls();
    game_check();
}

void menu()
{
    cls();
    printf("1. Start Game\n\nPress 'x' to exit");
    switch (getch())
    {
    case '1':
        game_start();
        break;
    case 'x':
    case 'X':
        break;
    default:
        menu();
    }
}