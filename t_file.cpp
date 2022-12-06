#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <windows.h>

#define DEFAULT_SIZE 12

int sessionHighScore;

void gotoxy(int x, int y)
{
    COORD c;
    c.X = x;
    c.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
}
void cursor(int isCursorOn)
{
    if (isCursorOn)
        printf("\e[?25h");
    else
        printf("\e[?25l");
}

void flush(int numberOfCharacters)
{
    for (int i = 0; i < numberOfCharacters; i++)
        printf(" ");
}

void flushData()
{
            gotoxy(17, 10);
            flush(12);
            gotoxy(17+32, 10);
            flush(12);
            gotoxy(17+(32*2), 10);
            flush(12);
            gotoxy(17+(32*2)-16, 10+5);
            flush(12);
            gotoxy(17+(32)-(16), 10+5);
            flush(12);
}

void showData(char data[][DEFAULT_SIZE])
{
    for (int i = 0; i < 5; i++)
    {
        switch(i)
        {
            case 0:
                gotoxy(15, 10);
                break;
            case 1:
                gotoxy(15+32, 10);
                break;
            case 2:
                gotoxy(15+(32*2), 10);
                break;
            case 4:
                gotoxy(15+(32*2)-16, 10+5);
                break;
            case 3:
                gotoxy(15+(32)-(16), 10+5);
                break;
        }
        printf("%d: %s\n", i + 1, data[i]);
    }
}

void barlines(int barLength)
{
    for (int i = 0; i < barLength; i++)
        printf("\xDB");
}

void frame() // 116x28
{
    gotoxy(2, 1);
    barlines(116);
    for (int i = 2; i < 28; i++)
    {
        gotoxy(2, i);
        printf("\xDB");
        gotoxy(3, i);
        printf("\xDB");
        gotoxy(4, i);
        printf("\xDB");
        gotoxy(117, i);
        printf("\xDB");
        gotoxy(116, i);
        printf("\xDB");
        gotoxy(115, i);
        printf("\xDB");
    }
    gotoxy(2, 28);
    barlines(116);
}

void game_box(int pos_x, int pos_y, int width, int height)
{
    // width=27, length= 2
    gotoxy(pos_x, pos_y);        // 9, 3
    printf("\xDA");              // upper-left corner
    for (int i = 0; i < width; i++) // upper line //27
        printf("\xC4");
    printf("\xBF");             // upper-right corner
    for (int i = 0; i < height; i++) // left-hand side //2
    {
        if (i == 0)
            pos_y++;
        gotoxy(pos_x, pos_y);
        printf("\xB3");
        ++pos_y;
    }
    gotoxy(pos_x, pos_y);
    printf("\xC0");              // bottom-left corner
    for (int i = 0; i < width; i++) // bottom line // 27
        printf("\xC4");
    printf("\xD9");             // bottom-right corner
    for (int i = 0; i < height; i++) // right-hand side //2
    {
        gotoxy((pos_x + width+1), pos_y - height); //28 //2
        printf("\xB3");
        pos_y++;
    }
}

void dataBox(int pos_x, int pos_y) // 104x11 //+105, -11
{
    // upper portion

    game_box(7, 3, 104, 2);
    
    // middle portion

    game_box(7, 7, 104, 11); // big box
     
    int x = 13, y = 9;

    for (int i = 0; i < 3; i++)
    {
        game_box(x, y, 27, 2);
        if (i>0)
        {
            game_box(x-16, y+5, 27, 2);
        }
        if (i == 2)
            x += 35;
        else
            x += 32;
    }

    // bottom portion

    game_box((7), 20, 104/4-3, 5);
    game_box((7+104/4), 20, 104/2, 1);
    game_box((7+104/4), 23, 104/2, 2);
    game_box((7+104/4+104/2)+3, 20, 104/4-3, 5);
}

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
        strcpy(data[newLength], data[length]);
        strcpy(data[length], target[0]);
    }
}

int fpoints(char data[][DEFAULT_SIZE], char input[][DEFAULT_SIZE], int index)
{
    if (strcmp(data[index], input[index]) == 0)
    {
        gotoxy(104-16+2, 23);
        flush(20);
        gotoxy(104-16+((26-9)/2), 23);
        printf("Points++\n");
        return 1;
    }
    else
        return 0;
}

void exit()
{
    system("cls");
    frame();
    gotoxy(47, 15);
    system("cls");
    frame();
    gotoxy(28, 13);                                                              // 116x28
    printf("\"So comes snow after fire, and even dragons have their ending!\""); // 62
    gotoxy(72, 16);
    printf("-- J. R. R. Tolken"); // 18
    Sleep(3000);
    system("cls");
    return;
}

void game()
{
    char data[][DEFAULT_SIZE] = {
        "Alpha", "Beta", "Casca",
        "Delta", "Enma", "Fortune",
        "Gamma", "Hilda", "India",
        "Jarhead", "Kelvin", "Lima",
        "Mission", "Norway", "Opus",
        "Parry", "Quelling", "Spotlight",
        "Tankard", "Under", "Vintas",
        "Wonder", "Xbox", "Zebra"};
    
    size_t dataLength = sizeof data / sizeof *data;

    int prev_points, points = 0, lives = 3, round = 1;

    
    srand((unsigned)time(NULL));

    while (1)
    {
        char input[dataLength][DEFAULT_SIZE] = {
            " ", " ", " ", " ", " "};

        frame();
        dataBox(7, 6);
        
        shuffle(data, dataLength);

        gotoxy(9, 5);
        printf("Session highest score: %d\n", sessionHighScore);

        if (lives != 0)
        {
            prev_points = points;
            gotoxy(((104-7)/2)+7, 5);
            printf("Round: %d", round);
            gotoxy(9, 22);
            printf("Total points: %d\n", points);
            gotoxy((104-15)+7, 5);
            printf("Difficulty: ???");
            gotoxy((7+104/4)+2, 21);            
            printf("Lives:");
            for (int n = 0; n < lives; n++)
            {
                 printf(" \x03"); 
            }

            showData(data);

            for (int i = 5; i >= 0 ; i--)
            {
                gotoxy(104-16+6, 23);
                printf("MEMORIZE (%ds)", i);

                Sleep(1000);
            }
            
            gotoxy(104-14, 22);
            flush(19);
            gotoxy((104-14), 23);
            flush(15);
            gotoxy(104-16+7, 23);
            printf("INPUT PHASE ");

            flushData();


            for (int i = 0; i < 5; i++)
            {
                if (lives < 1)
                    break;
                gotoxy((7+104/4)+2, 25);
                flush(20);
                gotoxy((7+104/4)+2, 25);
                printf("Input[%d]: ", i + 1);
                scanf("%s", &input[i]);
                
                for (int i = 0; i < 5; i++)
                {
                    switch(i)
                    {
                        case 0:
                            gotoxy(17, 10);
                            break;
                        case 1:
                            gotoxy(17+32, 10);
                            break;
                        case 2:
                            gotoxy(17+(32*2), 10);
                            break;
                        case 4:
                            gotoxy(17+(32*2)-16, 10+5);
                            break;
                        case 3:
                            gotoxy(17+(32)-(16), 10+5);
                            break;
                    }
                    printf("%s", input[i]);
                }

                if (fpoints(data, input, i))
                {
                    points++;

                    if (lives < 6)
                    {
                        lives++;
                        gotoxy(104-16+2, 23);
                        flush(20);
                        gotoxy(104-16+12, 23);
                        printf("+\x03\n");
                    }

                    if (points >= 10 && points == prev_points + 5)
                    {
                        gotoxy(9, 24);
                        printf("STREAK!! (X2)");
                        points *= 2;
                    }
                }
                else
                {
                    gotoxy(104-16+2, 23);
                    flush(20);
                    gotoxy(104-16+12, 23);
                    printf("-\x03\n");
                    lives--;
                }

                gotoxy((7+104/4)+2, 21);
                flush(30);
                gotoxy((7+104/4)+2, 21);            
                printf("Lives:");
                for (int n = 0; n < lives; n++)
                {
                    printf(" \x03"); 
                }

                gotoxy(9, 22);
                printf("Total points: %d\n", points);
            }

            flushData();
            showData(data);
            flushData();

        }
        
        if (points > sessionHighScore)
            sessionHighScore = points;


        if (lives == 0)
        {
            gotoxy((7+104/4)+2, 21);
            flush(30);
            gotoxy((7+104/4)+((52-17)/2), 21);            
            printf("G A M E   O V E R"); //17
            gotoxy((7+104/4)+2, 25);
            flush(30);
            gotoxy((7+104/4)+((52-35)/2), 25);
            printf("Press any key to retry, 'q' to quit"); //35

            if (getch() == 'q')
            {
                exit();
                break;
            }
            else
            {
                system("cls");
                game();
            }
        }
        else
        {
            gotoxy(9, 24);
            flush(15);
            gotoxy(9, 24);
            printf("ROUND WON, ROUND++");
            getch();
            system("cls");
        }
        round++;
    }
    return;
    getch();
}

main()
{
    game();
}