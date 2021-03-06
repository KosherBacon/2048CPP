#include <iostream>
#include <stdlib.h>
#include <string>
#include <cstring>
#include <vector>
#include <math.h>
#include <stdio.h>
#include <time.h>
#include <ncurses.h>

#define aSize 4
#define ESC 27
#define sSize 14

using namespace std;

// Global Variables
int board[aSize][aSize];
enum direction {UP, DOWN, LEFT, RIGHT};
int score[sSize] {2, 4, 8, 16, 32, 64, 128, 256, 512, 1024, 2048, 4096, 8192};

inline double random(double x0, double x1)
{
    return x0 + (x1 - x0) * rand() / ((double) RAND_MAX);
}

// Returns whether or not a 4 tile will be placed
bool useFourTile()
{
    if (random(0, 1) < 0.9)
    {
        return false;
    }
    return true;
}

// Updates the console to show the latest board
string refreshBoardString()
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
    return output += "\r";
}

void printScreen(string output)
{
    mvprintw(0, 0, output.c_str());
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
    if (temp == 0)
    {
        return;
    }
    int randVec = (int) (temp * random(0,1));
    int pos = unusedSpaces()[randVec];

    div_t divresult;
    divresult = div(pos, aSize);

    board[divresult.quot][divresult.rem] = useFourTile() ? 4 : 2;
}

inline string findReplace(string &s, string find, string replace)
{
    return s.replace(s.find(find), find.length(), replace);
}

// Combine Left, Right, Up, and Down
void move(int direction)
{
    string nums, result;
    switch (direction)
    {
        case LEFT:
            for (int i = 0; i < aSize; i++)
            {
                for (int j : board[i])
                {
                    nums += to_string(j);
                }
                // Remove all 0's from the string
                nums = findReplace(nums, "0", "");
                // Iterate through scores to combine terms
                for (int var : score)
                {
                    nums = findReplace(nums, to_string(var) + to_string(var), to_string(2 * var));
                }
                nums = "";
            }
            break;
        case RIGHT:
            break;
        case UP:
            break;
        case DOWN:
            break;
    }
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
    printScreen(refreshBoardString());

    bool stop = false;

    while (true)
    {
        switch (getch())
        {
            case KEY_UP:
                move(UP);
                fillNewSpot();
                printScreen(refreshBoardString());
                break;
            case KEY_DOWN:
                move(DOWN);
                fillNewSpot();
                printScreen(refreshBoardString());
                break;
            case KEY_LEFT:
                move(LEFT);
                fillNewSpot();
                printScreen(refreshBoardString());
                break;
            case KEY_RIGHT:
                move(RIGHT);
                fillNewSpot();
                printScreen(refreshBoardString());
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
