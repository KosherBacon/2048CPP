#include <iostream>
#include <stdlib.h>
#include <string>
#include <cstring>
#include <vector>
#include <math.h>
#include <stdio.h>
#include <time.h>
#include <curses.h>

#define aSize 4
#define ESC 27

using namespace std;

// Global Variables
int board[aSize][aSize];

inline double random(double x0, double x1)
{
    return x0 + (x1 - x0) * rand() / ((double) RAND_MAX);
}

// Returns whether or not a 4 tile will be placed
bool useFourTile()
{
    if (random(0, 1) < 0.1)
    {
        return true;
    }
    return false;
}

// Updates the console to show the latest board
void updateConsole()
{
    string output = "";
    for (int i = 0; i < aSize; i++)
    {
        for (int j = 0; j < aSize; j++)
        {
            output += to_string(board[i][j]);
            // Fill gaps with empty spaces
            int spaces = 8 - to_string(board[i][j]).length();
            for (int k = 0; k < spaces; k++)
            {
                output += " ";
            }
        }
        output += "\n";
    }
    output += "\r";
    printw(output.c_str());
    //cout << output << "\r";
}

// Returns vector of unused board spaces
vector<int> unusedSpaces()
{
    vector<int> temp;
    for (int i = 0; i < aSize; i++)
    {
        for (int j = 0; j < aSize; j++)
        {
            if (board[i][j] == 0)
            {
                temp.push_back(i * aSize + j);
            }
        }
    }
    return temp;
}

// Fill a new spot with a 2 or 4
void fillNewSpot()
{
    int temp = unusedSpaces().size();
    int randVec = (int) (temp * random(0,1));
    int pos = unusedSpaces()[randVec];

    div_t divresult;
    divresult = div(pos, aSize);

    board[divresult.quot][divresult.rem] = useFourTile() ? 4 : 2;
}

int main(int argc, char *argv[])
{
    srand(time(NULL));
    // Initialize empty board
    for (int i = 0; i < aSize; i++)
    {
        for (int j = 0; j < aSize; j++)
        {
            board[i][j] = 0;
        }
    }

    // Fill 2 first spots and update
    for (int i = 0; i < 2; i++)
    {
        fillNewSpot();
    }

    initscr();
    noecho();
    keypad(stdscr, true);

    updateConsole();

    bool stop = false;

    while (true)
    {
        switch (getch())
        {
            case KEY_UP:
                printw("UP\n");
                break;
            case KEY_DOWN:
                printw("DOWN\n");
                break;
            case KEY_LEFT:
                printw("LEFT\n");
                break;
            case KEY_RIGHT:
                printw("RIGHT\n");
                break;
            case ESC:
                stop = true;
                break;
        }

        if (stop)
        {
            break;
        }

        refresh();
    }
    endwin();

    //for (auto c : unusedSpaces())
    //{
    //    cout << c << " " << endl;
    //}
    return EXIT_SUCCESS;
}
