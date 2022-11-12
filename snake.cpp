#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <sys/select.h>
#include <unistd.h>

using namespace std;
bool gameOver;
const int width = 20;
const int height = 20;
int x, y, fruitX, fruitY, score, tailX[100], tailY[100], nTail;
enum direction
{
    STOP = 0,
    LEFT,
    RIGHT,
    UP,
    DOWN
};
direction dir;

int kbhit(void)
{
    struct timeval tv;
    fd_set read_fd;
    tv.tv_sec = 0;
    tv.tv_usec = 0;
    FD_ZERO(&read_fd);
    FD_SET(0, &read_fd);
    if (select(1, &read_fd, NULL, NULL, &tv) == -1)
        return 0;
    if (FD_ISSET(0, &read_fd))
        return 1;
    return 0;
}

void setUp()
{
    gameOver = false;
    dir = STOP;
    x = width / 2;
    y = height / 2;
    // srand(time(NULL));
    fruitX = rand() % width;
    fruitY = rand() % height;
    if (fruitX == 0)
        fruitX += 2;
    else if (fruitX == 1)
        fruitX += 1;
    if (fruitY == 0)
        fruitY += 2;
    else if (fruitY == 1)
        fruitY += 1;
    score = 0;
}
void draw()
{
    system("clear");
    for (int i = 1; i <= width; i++)
        cout << "#";
    cout << endl;
    for (int i = 2; i < height; i++)
    {
        for (int j = 1; j <= width; j++)
        {
            if (j == 1 || j == width)
                cout << "#";
            else if (i == y && j == x)
                cout << "O";
            else if (j == fruitX && i == fruitY)
                cout << "F";
            else
            {
                bool print=false;
                for(int k=1; k<=nTail; k++)
                {
                    if(tailX[k]==j && tailY[k]==i)
                    {
                        cout<<"o";
                        print=true;
                        break;
                    }
                }    
                if(!print)
                    cout << " ";
            }
        }
        cout << endl;
    }
    for (int i = 1; i <= width; i++)
        cout << "#";
    cout << endl;
    cout << "Score: " << score << endl;
    cout << fruitX << fruitY << "Helloo" << endl;
    cout << x << y << "HIII";
}
void input()
{
    if (kbhit())
    {
        char ch = getchar();
        switch (ch)
        {
        case 'a':
            dir = LEFT;
            break;
        case 'd':
            dir = RIGHT;
            break;
        case 'w':
            dir = UP;
            break;
        case 's':
            dir = DOWN;
            break;
        case 'x':
            gameOver = true;
            break;
        }
    }
}
void logic()
{
    tailX[1]=x;
    tailY[1]=y;
    int prevX=tailX[1];
    int prevY=tailY[1];
    int prev2X, prev2Y;
    for(int i=2; i<=nTail; i++)
    {
        prev2X=tailX[i];
        prev2Y=tailY[i];
        tailX[i]=prevX;
        tailY[i]=prevY;
        prevX=prev2X;
        prevY=prev2Y;
    }
    switch (dir)
    {
    case LEFT:
        x--;
        break;
    case RIGHT:
        x++;
        break;
    case UP:
        y--;
        break;
    case DOWN:
        y++;
        break;
    default:
        break;
    }
    if (x > (width-1) || x < 2 || y > (height-1) || y < 2)
        gameOver = true;
    for(int i=0; i<nTail; i++)
        if(tailX[i]==x && tailY[i]==y)
            gameOver=true;
    if (x == fruitX && y == fruitY)
    {
        score += 10;
        // srand(time(NULL));
        fruitX = rand() % width;
        fruitY = rand() % height;
        if (fruitX == 0)
            fruitX += 2;
        else if (fruitX == 1)
            fruitX += 1;
        if (fruitY == 0)
            fruitY += 2;
        else if (fruitY == 1)
            fruitY += 1;
        nTail++;
    }
    
}
int main()
{
    setUp();
    while (!gameOver)
    {
        draw();
        input();
        logic();
        usleep(400000);
    }
    return 0;
}
