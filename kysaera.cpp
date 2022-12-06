#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <windows.h>

#define DEFAULT_SIZE 12

void menu();
void splash();
void loading();
void instructions();
void exit();
void game();
void shuffle();
void databox();
void gamebox();
void frame();
void barlines();
void meshlines();
void showData();
void flushData();
void flush();
bool fpoints();

// for setting cursor to terminal coordinates

void gotoxy(int x, int y) 
{
    COORD c;
    c.X = x;
    c.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
}

// cursor behavior

void hideCursor()
{
   HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
   CONSOLE_CURSOR_INFO info;
   info.dwSize = 100;
   info.bVisible = FALSE;
   SetConsoleCursorInfo(consoleHandle, &info);
}

int main()
{
    hideCursor();
    splash();
}

// for refreshing text instead of "\r"

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

// simple bars and boxes using ASCII characters

void meshlines(int meshLength)
{
    for (int i = 0; i < meshLength; i++)
        printf("\xB2");
}

void barlines(int barLength)
{
    for (int i = 0; i < barLength; i++)
        printf("\xDB");
}

void frame()
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
    // upper-left corner
    gotoxy(pos_x, pos_y);       
    printf("\xDA");
    // upper line              
    for (int i = 0; i < width; i++) 
        printf("\xC4");
    // upper-right corner
    printf("\xBF");             
    // left-hand side 
    for (int i = 0; i < height; i++) 
    {
        if (i == 0)
            pos_y++;
        gotoxy(pos_x, pos_y);
        printf("\xB3");
        ++pos_y;
    }
    // bottom-left corner
    gotoxy(pos_x, pos_y);
    printf("\xC0");              
    // bottom line
    for (int i = 0; i < width; i++) 
        printf("\xC4");
    // bottom-right corner
    printf("\xD9");
    // right-hand side             
    for (int i = 0; i < height; i++) 
    {
        gotoxy((pos_x + width+1), pos_y - height);
        printf("\xB3");
        pos_y++;
    }
}

void dataBox(int pos_x, int pos_y)
{
    // upper portion
    game_box(7, 3, 104, 2);
    
    //middle portion
    game_box(7, 7, 104, 11); 
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

// modern fisher-yates shuffle for data

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

// bool for points (int)

bool fpoints(char data[][DEFAULT_SIZE], char input[][DEFAULT_SIZE], int index)
{
    if (strcmp(data[index], input[index]) == 0)
    {
        gotoxy(104-16+2, 23);
        flush(20);
        gotoxy(104-16+((26-9)/2), 23);
        printf("Points++\n");
        return TRUE;
    }
    else
        return FALSE;
}

// game code proper

int sessionHighScore;

void game()
{
    system("cls");
    
    // 7893600 permutations  
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

    // clock for random number
    srand((unsigned)time(NULL));

    while (1)
    {
        // refresh input data every loop
        char input[dataLength][DEFAULT_SIZE] = {
            " ", " ", " ", " ", " "};

        frame();
        dataBox(7, 6);
        
        shuffle(data, dataLength);

        if (lives != 0)
        {
            prev_points = points;
            gotoxy(9, 5);
            printf("Session highest score: %d\n", sessionHighScore);
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
                 // heart
                 printf(" \x03"); 
            }

            flushData();
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
                // double guard for immediate terminate input when life hits 0
                if (lives < 1)
                    break;
                gotoxy((7+104/4)+2, 25);
                flush(50);
                gotoxy((7+104/4)+2, 25);
                printf("Input[%d]: ", i + 1);
                scanf("%s", &input[i]);
                
                // show input on boxes
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
                    printf("%.12s", input[i]);
                }

                if (fpoints(data, input, i))
                {
                    points++;

                    if (lives < 5)
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
        }
        if (points > sessionHighScore)
            sessionHighScore = points;
        if (lives == 0)
        {
            flushData();
            showData(data);            
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
                menu();
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

void instructions()
{
    system("cls");
    frame();
    getch();
    menu();
}

void loading(int loadingBarLength)
{
    int loaderDelay = 200;

    for (int i = 0; i < loadingBarLength; i++)
    {
        printf("\xDB");
        Sleep(loaderDelay);
        if (loaderDelay > 0)
            loaderDelay -= 20;
    }
}

void splash()
{
    system("cls");
    system("color 3");
    frame();
    gotoxy(45, 13);
    printf("*** KYSAERA SPLASH ART ***"); // 26
    gotoxy(48, 14);
    printf("\"Memories of a Poet\""); // 20
    gotoxy(44, 20);
    loading(28);
    gotoxy(44, 22);
    printf("Press any key to continue..."); // 28
    getch();
    menu();
}

void menu()
{
    system("cls");
    system("color 3");
    frame();
    gotoxy(25, 11);
    meshlines(10);
    printf(" 1. Start");
    gotoxy(25, 14);
    meshlines(10);
    printf(" 2. Instructions");
    gotoxy(25, 17);
    meshlines(10);
    printf(" 3. Exit");

    switch (getch())
    {
    case '1':
        game();
        break;
    case '2':
        instructions();
        break;
    case '3':
        exit();
        break;
    default:
        menu();
    }    
}