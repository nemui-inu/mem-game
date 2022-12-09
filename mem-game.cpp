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
void data_box();
void game_box();
void frame();
void bar_lines();
void mesh_lines();
void show_data();
void flush_data();
void flush();
bool function_points();

// for setting cursor to terminal coordinates

void gotoxy(int x, int y)
{
    COORD c;
    c.X = x;
    c.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
}

// cursor behavior

void hide_cursor()
{
    HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO info;
    info.dwSize = 100;
    info.bVisible = FALSE;
    SetConsoleCursorInfo(consoleHandle, &info);
}

int main()
{
    splash();
}

// for refreshing text instead of "\r"

void flush(int char_count)
{
    for (int i = 0; i < char_count; i++)
        printf(" ");
}

void flush_data()
{
    gotoxy(17, 10);
    flush(12);
    gotoxy(17 + 32, 10);
    flush(12);
    gotoxy(17 + (32 * 2), 10);
    flush(12);
    gotoxy(17 + (32 * 2) - 16, 10 + 5);
    flush(12);
    gotoxy(17 + (32) - (16), 10 + 5);
    flush(12);
}

void show_data(char data[][DEFAULT_SIZE])
{
    for (int i = 0; i < 5; i++)
    {
        switch (i)
        {
        case 0:
            gotoxy(15, 10);
            break;
        case 1:
            gotoxy(15 + 32, 10);
            break;
        case 2:
            gotoxy(15 + (32 * 2), 10);
            break;
        case 4:
            gotoxy(15 + (32 * 2) - 16, 10 + 5);
            break;
        case 3:
            gotoxy(15 + (32) - (16), 10 + 5);
            break;
        }
        printf("%d: %s\n", i + 1, data[i]);
    }
}

// simple bars and boxes using ASCII characters

void mesh_lines(int mesh_length)
{
    for (int i = 0; i < mesh_length; i++)
        printf("\xB2");
}

void bar_lines(int bar_length)
{
    for (int i = 0; i < bar_length; i++)
        printf("\xDB");
}

void frame()
{
    gotoxy(2, 1);
    bar_lines(116);
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
    bar_lines(116);
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
        gotoxy((pos_x + width + 1), pos_y - height);
        printf("\xB3");
        pos_y++;
    }
}

void data_box(int pos_x, int pos_y)
{
    // upper portion
    game_box(7, 3, 104, 2);

    // middle portion
    game_box(7, 7, 104, 11);
    int x = 13, y = 9;
    for (int i = 0; i < 3; i++)
    {
        game_box(x, y, 27, 2);
        if (i > 0)
        {
            game_box(x - 16, y + 5, 27, 2);
        }
        if (i == 2)
            x += 35;
        else
            x += 32;
    }

    // bottom portion
    game_box((7), 20, 104 / 4 - 3, 5);
    game_box((7 + 104 / 4), 20, 104 / 2, 1);
    game_box((7 + 104 / 4), 23, 104 / 2, 2);
    game_box((7 + 104 / 4 + 104 / 2) + 3, 20, 104 / 4 - 3, 5);
}

// fisher-yates shuffle for data

void shuffle(char data[][DEFAULT_SIZE], size_t length)
{
    char temp[1][DEFAULT_SIZE];

    while (length > 1)
    {
        size_t new_length = rand() % (length--);
        strcpy(temp[0], data[new_length]);
        strcpy(data[new_length], data[length]);
        strcpy(data[length], temp[0]);
    }
}

// bool for points (int)

bool function_points(char data[][DEFAULT_SIZE], char input[][DEFAULT_SIZE], int index)
{
    if (strcmp(data[index], input[index]) == 0)
    {
        gotoxy(104 - 16 + 2, 23);
        flush(20);
        gotoxy(104 - 16 + ((26 - 9) / 2), 23);
        printf("Points++\n");
        return TRUE;
    }
    else
        return FALSE;
}

// game code proper

int session_high_score;

void game()
{
    system("cls");
    system("color 3");
    
    frame();
    gotoxy(((7 + 104 / 4)) + (((104 / 2) - 24) / 2), 21);
    printf("\"Press any key to begin...\"");
    getch();

    // 7,893,600 permutations
    char data[][DEFAULT_SIZE] = {
        "Alpha", "Beta", "Casca",
        "Delta", "Enma", "Fortune",
        "Gamma", "Hilda", "India",
        "Jarhead", "Kelvin", "Lima",
        "Mission", "Norway", "Opus",
        "Parry", "Quelling", "Spotlight",
        "Tankard", "Under", "Vintas",
        "Wonder", "Xenon", "Zebra"};

    size_t data_length = sizeof data / sizeof *data;

    int points = 0, lives = 3, max_lives = 3, round = 1,
        point_streak = 0, streak_counter = 0;

    // clock for random number
    srand((unsigned)time(NULL));

    while (1)
    {
        system("color 3");

        // refresh input data every loop
        char input[data_length][DEFAULT_SIZE] = {
            " ", " ", " ", " ", " "};

        frame();
        data_box(7, 6);

        shuffle(data, data_length);
        
        if (lives != 0)
        {   
            gotoxy(9, 24);
            flush(20);
            gotoxy(9, 24);
            printf("Combo: %d", streak_counter);                 
            gotoxy(9, 5);
            printf("Session highest score: %d\n", session_high_score);
            gotoxy(((104 - 7) / 2) + 7, 5);
            printf("Round: %d", round);
            gotoxy(9, 22);
            printf("Total points: %d\n", points);
            gotoxy((104 - 15) + 7, 5);
            printf("Difficulty: ???");
            gotoxy((7 + 104 / 4) + 2, 21);
            flush(50);
            gotoxy((7 + 104 / 4) + 2, 21);
            printf("Lives:");
            for (int n = 0; n < lives; n++)
            {
                // heart
                printf(" \x03");
            }

            flush_data();
            show_data(data);

            for (int i = 5; i >= 0; i--)
            {
                gotoxy(104 - 16 + 6, 23);
                printf("MEMORIZE (%ds)", i);

                Sleep(1000);
            }

            system("color 9");

            gotoxy(104 - 14, 22);
            flush(19);
            gotoxy((104 - 14), 23);
            flush(15);
            gotoxy(104 - 16 + 7, 23);
            printf("INPUT PHASE ");

            flush_data();

            for (int i = 0; i < 5; i++)
            {
                // guard to immediately terminate input phase if life hits 0
                if (lives < 1)
                    break;
                
                gotoxy((7 + 104 / 4) + 2, 25);
                flush(50);
                gotoxy((7 + 104 / 4) + 2, 25);
                printf("Input[%d]: ", i + 1);
                scanf("%s", &input[i]);

                // show input on boxes
                for (int i = 0; i < 5; i++)
                {
                    switch (i)
                    {
                    case 0:
                        gotoxy(15, 10);
                        break;
                    case 1:
                        gotoxy(15 + 32, 10);
                        break;
                    case 2:
                        gotoxy(15 + (32 * 2), 10);
                        break;
                    case 4:
                        gotoxy(15 + (32 * 2) - 16, 10 + 5);
                        break;
                    case 3:
                        gotoxy(15 + (32) - (16), 10 + 5);
                        break;
                    }
                    printf("%d. %.12s", i + 1, input[i]);
                }

                if (function_points(data, input, i))
                {
                    system("color B");

                    points += 5;
                    point_streak += 5;

                    if (lives < max_lives)
                    {
                        lives++;
                        gotoxy(104 - 16 + 2, 23);
                        flush(20);
                        gotoxy(104 - 16 + 12, 23);
                        printf("+\x03");
                    }
                }
                else
                {
                    system("color C");
                    gotoxy(104 - 16 + 2, 23);
                    flush(20);
                    gotoxy(104 - 16 + 12, 23);
                    printf("-\x03\n");
                    lives--;
                }

                gotoxy((7 + 104 / 4) + 2, 21);
                flush(30);
                gotoxy((7 + 104 / 4) + 2, 21);
                printf("Lives:");
                for (int n = 0; n < lives; n++)
                {
                    printf(" \x03");
                }

                gotoxy(9, 22);
                printf("Total points: %d\n", points);

            }

            // watches out for a streak
            if (point_streak == 25)
                streak_counter++;
            else
                streak_counter = 0;
        
            point_streak = 0;
            gotoxy(9, 24);
            flush(20);
            gotoxy(9, 24);
            printf("Combo: %d", streak_counter);

            // streak bonus
            if (streak_counter > 1)
            {
                gotoxy(9, 24);
                printf("STREAK!! (X2)");
                gotoxy(9, 25);
                printf("MAX LIVES UP");
                max_lives++;
                points *= 2;
            }

            flush_data();
            show_data(data);
        }

        if (points > session_high_score)
            session_high_score = points;
        if (lives == 0)
        {
            system("color 4");
            flush_data();
            show_data(data);
            gotoxy((7 + 104 / 4) + 2, 21);
            flush(30);
            gotoxy((7 + 104 / 4) + ((52 - 17) / 2), 21);
            printf("G A M E   O V E R");
            gotoxy((7 + 104 / 4) + 2, 25);
            flush(30);
            gotoxy((7 + 104 / 4) + ((52 - 35) / 2), 25);
            printf("Press any key to retry, 'q' to quit");

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
            system("color A");
            gotoxy(9, 24);
            flush(15);
            gotoxy(9, 24);
            printf("SURVIVED!, ROUND++");
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
    system("color C");
    frame();
    gotoxy(47, 15);
    system("cls");
    frame();
    gotoxy(28, 13);                                                             
    printf("\"So comes snow after fire, and even dragons have their ending!\""); 
    gotoxy(72, 16);
    printf("-- J. R. R. Tolken"); 
    Sleep(3000);
    system("cls");
    return;
}

void instructions()
{
    system("cls");
    system("color B");
    frame();
    gotoxy(7, 3);
    printf("INSTRUCTIONS");
    gotoxy(10, 5);
    printf("The game consists of two phases:");
    gotoxy(13, 7);
    printf("1. Memorize Phase");
    gotoxy(16, 9);
    printf("During this phase, you will memorize the five (5) random words presented on screen.");
    gotoxy(16, 10);
    printf("After five (5) seconds, the words will then disappear and you will enter the next phase.");
    gotoxy(13, 12);
    printf("2. Input Phase");
    gotoxy(16, 14);
    printf("During this phase, you will fill in the 'now-missing' words within the boxes in");
    gotoxy(16, 15);
    printf("correct order. As you enter your input, corresponding points and lives will be given.");
    gotoxy(10, 17);
    printf("Points and Life System");
    gotoxy(13, 19);
    printf("Five (5) points will be given (+) when the player enters a correct word (correct case,");
    gotoxy(13, 20);
    printf("spelling, and order). When player the scores consecutive perfect scores (5), the current");
    gotoxy(13, 21);
    printf("score will be doubled");
    gotoxy(13, 23);
    printf("The player starts with three (3) lives (\x03). It will deduct (-\x03) for a every wrong input");
    gotoxy(13, 24);
    printf("and will reward the player (+\x03) for every correct input. Initially, the maximum number of");
    gotoxy(13, 25);
    printf("(\x03) is three (3). However, as you score consecutive perfect scores, this value will increase.");
    getch();
    menu();
}

// pseudo loading bar for show
void loading(int load_bar_length)
{
    int load_delay = 200;

    for (int i = 0; i < load_bar_length; i++)
    {
        printf("\xDB");
        Sleep(load_delay);
        if (load_delay > 0)
            load_delay -= 20;
    }
}

void splash()
{
    hide_cursor();
    system("cls");
    system("color 3");
    frame();
    gotoxy((120 - 15)/2, 7);
    printf("M E M - G A M E");
    gotoxy((120 - 7)/2, 9);
    printf("v.0.0.1");
    gotoxy((120 - 26)/2, 16);
    printf("A memory game written in C");
    gotoxy((120 - 16)/2, 18);
    printf("By Jethro Garcia");
    gotoxy((120 - 32)/2, 22);
    loading(32);
    gotoxy((120 - 28)/2, 24);
    printf("Press any key to continue...");
    getch();
    menu();
}

void menu()
{
    system("cls");
    system("color 3");
    frame();
    gotoxy(25, 11);
    mesh_lines(10);
    printf(" 1. Start");
    gotoxy(25, 14);
    mesh_lines(10);
    printf(" 2. Instructions");
    gotoxy(25, 17);
    mesh_lines(10);
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