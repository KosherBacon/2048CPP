#include <termios.h>
#include <unistd.h>
#include <stdio.h>

#define BUFSIZE 100

char buf[BUFSIZE];
int bufp = 0;

/* reads from keypress, doesn't echo */
/*int getch(void)
{
    struct termios oldattr, newattr;
    int ch;
    tcgetattr( STDIN_FILENO, &oldattr );
    newattr = oldattr;
    newattr.c_lflag &= ~( ICANON | ECHO );
    tcsetattr( STDIN_FILENO, TCSANOW, &newattr );
    ch = getchar();
    tcsetattr( STDIN_FILENO, TCSANOW, &oldattr );
    return ch;
}*/

int getch(void)
{
    return (bufp > 0) ? buf[--bufp] : getchar();
}

/* reads from keypress, echoes */
int getche(void)
{
    struct termios oldattr, newattr;
    int ch;
    tcgetattr( STDIN_FILENO, &oldattr );
    newattr = oldattr;
    newattr.c_lflag &= ~( ICANON );
    tcsetattr( STDIN_FILENO, TCSANOW, &newattr );
    ch = getchar();
    tcsetattr( STDIN_FILENO, TCSANOW, &oldattr );
    return ch;
}

void ungetch(int c)
{
    if (bufp >= BUFSIZE)
    {
        printf("ungetch: too many characters\n");
    }
    else
    {
        buf[bufp++] = c;
    }
}

int kbhit(void)
{
    struct termios oldt, newt;
    int ch;

    tcgetattr( STDIN_FILENO, &oldt );
    newt = oldt;

    newt.c_cc[VMIN] = 0;
    newt.c_cc[VTIME] = 1;
    newt.c_lflag &= ~( ICANON | ECHO );
    tcsetattr( STDIN_FILENO, TCSANOW, &newt );

    ch = getchar();

    tcsetattr( STDIN_FILENO, TCSANOW, &oldt );

    return ch;
}
