#include <stdio.h>
#include <conio.h>
#include <windows.h>

// game size is 120x30 (xy)

void main_menu();
void splash();
void loading();
void game_exit();
void instructions();
void game_start();
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
void cursor(int v)
{
    if (v == 0)
    {
        printf("\e[?25l");
    }
    else
    {
        printf("\e[?25h");
    }
}

int main()
{
    splash();
}

void barlines(int z)
{
    for (int i = 0; i < z; i++)
        printf("\xDB");
}

void meshlines(int a)
{
    for (int i = 0; i < a; i++)
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

void game_box(int pos_x, int pos_y)
{
    // width=27, length= 3
    gotoxy(pos_x, pos_y);        // 9, 3
    printf("\xDA");              // upper-left corner
    for (int i = 0; i < 27; i++) // upper line
        printf("\xC4");
    printf("\xBF");             // upper-right corner
    for (int i = 0; i < 2; i++) // left-hand side
    {
        if (i == 0)
            pos_y++;
        gotoxy(pos_x, pos_y);
        printf("\xB3");
        ++pos_y;
    }
    gotoxy(pos_x, pos_y);
    printf("\xC0");              // bottom-left corner
    for (int i = 0; i < 27; i++) // bottom line
        printf("\xC4");
    printf("\xD9");             // bottom-right corner
    for (int i = 0; i < 2; i++) // right-hand side
    {
        gotoxy((pos_x + 28), pos_y - 2);
        printf("\xB3");
        pos_y++;
    }
}

void game_start()
{
    int x = 9;
    system("cls");
    frame();
    for (int i = 0; i < 3; i++)
    {
        game_box(x, 3);
        if (i==1 || i==2)
        {
            game_box(x-18, 8);
        }
        if (i == 2)
            x += 38;
        else
            x += 36;
    }
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
    Sleep(3000);
    system("cls");
    system("color F");
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