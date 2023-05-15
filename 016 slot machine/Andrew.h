#ifndef _ANDREW_H_
#define	_ANDREW_H_
// base code file

#include <iostream>
#include <iomanip>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <termios.h>
#include <cmath>

using namespace std;

// goes to coordinates (x, y) in console (far left starts at 1)
void gotoxy(int x, int y)
{
    printf("%c[%d;%df", 0x1B, y, x);
}

// generates a random number between 0 and r inclusive
int random(int r)
{
    return rand() % r + 1;
}

// receives character from input
char getch(void) {
    char buf = 0;
    struct termios old = {0};
    fflush(stdout);
    if(tcgetattr(0, &old) < 0)
        perror("tcsetattr()");
    old.c_lflag &= ~ICANON;
    old.c_lflag &= ~ECHO;
    old.c_cc[VMIN] = 1;
    old.c_cc[VTIME] = 0;
    if(tcsetattr(0, TCSANOW, &old) < 0)
        perror("tcsetattr ICANON");
    if(read(0, &buf, 1) < 0)
        perror("read()");
    old.c_lflag |= ICANON;
    old.c_lflag |= ECHO;
    if(tcsetattr(0, TCSADRAIN, &old) < 0)
        perror("tcsetattr ~ICANON");
    return buf;
}

// returns 1 when the keyboard is hit, otherwise returns 0
int kbhit()
{
    termios term;
    tcgetattr(0, &term);

    termios term2 = term;
    term2.c_lflag &= ~ICANON;
    tcsetattr(0, TCSANOW, &term2);

    int byteswaiting;
    ioctl(0, FIONREAD, &byteswaiting);

    tcsetattr(0, TCSANOW, &term);

    return byteswaiting;
}

// draws line of specified coordinates, length, and character
void drawLine(int x, int y, int len, char sym) {
    gotoxy(x,y);
    for (int i = 0; i < len; i++) {
        cout << sym;
    }
}

// draws box of specified coordinates, width, height, and character
void drawBox(int x, int y, int wid, int height, char sym) {
    for (int i = 0; i < height; i++) {
        drawLine(x, y+i, wid, sym);
    }
}

// draws framed box of specified coordinates, width, height, and character
// returns coordinates of center
void drawFramedBox(int x, int y, int wid, int height, char sym) {
    drawBox(x, y, wid, height, sym);
    drawBox(x+1, y+1, wid-2, height-2, ' ');
    gotoxy(x+wid, y+height);
}

#endif