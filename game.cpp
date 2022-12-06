#include <stdio.h>
#include <conio.h>
#include <windows.h>
#include <time.h>

// game size is 120x30 (xy)

void main_menu();
void splash();
void loading();
void game_exit();
void instructions();
void game_start();
void game();
void fpoints();
void shuffle();
void newline();
void statusBar();
void dataBox();
void game_box();
void frame();
void meshlines();
void barlines();
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

main()
{
    splash();
}

void barlines(int barLength)
{
    for (int i = 0; i < barLength; i++)
        printf("\xDB");
}

void meshlines(int meshLength)
{
    for (int i = 0; i < meshLength; i++)
        printf("\xB2");
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

#define DEFAULT_SIZE 12

int sessionHighScore;

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
        printf("Points++\n");
        return 1;
    }
    else
        return 0;
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

    char input[dataLength][DEFAULT_SIZE];

    int prev_points, points = 0, lives = 3, round = 1;

    srand((unsigned)time(NULL));

    while (1)
    {
        shuffle(data, dataLength);

        printf("Session highest score: %d\n", sessionHighScore);

        if (lives != 0)
        {
            prev_points = points;
            printf("Round: %d\n", round);
            printf("Total points: %d\n", points);
            printf("Lives:");
            for (int n = 0; n < lives; n++)
                printf(" \x03");
            printf("\n\n");

            for (int i = 0; i < 5; i++)
            {
                printf("Data [%d]: %s\n", i + 1, data[i]);
            }

            printf("\n-\n\n");

            for (int i = 5; i > 0; i--)
            {
                printf("\r%d second(s) before input phase", i);
                Sleep(1500);
            }

            system("cls");

            for (int i = 0; i < 5; i++)
            {
                if (lives < 1)
                    break;

                printf("Input[%d]: ", i + 1);
                scanf("%s", &input[i]);
                if (fpoints(data, input, i))
                {
                    points++;

                    if (lives < 3)
                    {
                        lives++;
                        printf("+\x03\n");
                    }

                    if (points >= 10 && points == prev_points + 5)
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

            printf("\n\n");

            for (int i = 0; i < 5; i++)
            {
                printf("Data [%d]: %s\n", i + 1, data[i]);
            }

            if (points > sessionHighScore)
                sessionHighScore = points;
        }
        else
            break;

        printf("\nTotal points: %d\n", points);

        if (points > sessionHighScore)
            sessionHighScore = points;

        if (lives == 0)
        {
            printf("\nG A M E   O V E R");
            newline(2);
            printf("Press any key to retry, 'q' to quit");

            if (getch() == 'q')
                game_exit();
            else
            {
                system("cls");
                game();
            }
        }
        else
        {
            printf("You win\n");
            getch();
            system("cls");
        }
        printf("\n-\n\n");
        round++;
    }
    return;
}

void game_start()
{
    system("cls");
    frame();
    dataBox(7, 6);
    game();
    getch();
    main_menu();
}

void instructions()
{
    system("cls");
    frame();
    getch();
    main_menu();
}

void game_exit()
{
    system("cls");
    frame();
    gotoxy(47, 15);
    printf("Do really wish to quit? (Q)");
    if (getch() != 'q')
        main_menu();
    system("cls");
    frame();
    gotoxy(28, 13);                                                              // 116x28
    printf("\"So comes snow after fire, and even dragons have their ending!\""); // 62
    gotoxy(72, 16);
    printf("-- J. R. R. Tolken"); // 18
    Sleep(1500);
    system("cls");
}

void loading(int p)
{
    int loader = 200;

    for (int i = 0; i < p; i++)
    {
        printf("\xDB");
        Sleep(loader);
        if (loader > 0)
            loader -= 20;
    }
}

void splash()
{
    system("cls");
    system("color 3");
    cursor(0);
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
    main_menu();
}

void main_menu()
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
        game_start();
        break;
    case '2':
        instructions();
        break;
    case '3':
        game_exit();
        break;
    default:
        main_menu();
    }
}