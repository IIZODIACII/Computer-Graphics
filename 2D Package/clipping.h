#include<bits/stdc++.h>

using namespace std;
/**  Helpers   **/
void vIntersect(int x1, int y1, int x2, int y2, int x_edge, int &x_in, int &y_in)
{
    x_in = x_edge;
    y_in = y1 + (x_in-x1) * (y2 - y1) / (x2 - x1);
}

void hIntersect(int x1, int y1, int x2, int y2, int y_edge, int &x_in, int &y_in)
{
    y_in = y_edge;
    x_in = x1 + (y_in-y1) /(float)((y2 - y1) / (x2 - x1));
}
void cpy(int newPoints[][2], int newSize,int polyPoints[][2], int &size)
{
    size = newSize;
    for (int j = 0; j < size; j++)
    {
        polyPoints[j][0] = newPoints[j][0];
        polyPoints[j][1] = newPoints[j][1];
        if(j == size - 1)
        {
            polyPoints[j+1][0] = newPoints[0][0];
            polyPoints[j+1][1] = newPoints[0][1];
        }
    }
}
void drawSquare(HDC hdc, int xLeft, int yTop, int xRight, int yBottom)
{
    lineMidPoint(hdc,xLeft,yBottom,xLeft,yTop,RGB(0,0,0));
    lineMidPoint(hdc,xLeft,yTop,xRight,yTop,RGB(0,0,0));
    lineMidPoint(hdc,xRight,yTop,xRight,yBottom,RGB(0,0,0));
    lineMidPoint(hdc,xLeft,yBottom,xRight,yBottom,RGB(0,0,0));
}
void drawPoly(HDC hdc,int polyPoints[][2],int size, COLORREF color)
{
    for(int i = 0; i < (size); i++)
    {
        int k = (i+1) % (size);
        cout<<polyPoints[i][0]<<" "<<polyPoints[i][1]<<" "<<polyPoints[k][0]<<" "<<polyPoints[k][1]<<endl;
        intLineDDA(hdc,polyPoints[i][0],polyPoints[i][1],polyPoints[k][0],polyPoints[k][1],color);
    }
}
/***************************************************/

void leftClip(int polyPoints[][2], int &size, int xLeft)
{
    int newPoints[10][2], newSize = 0;
    for (int i = 0; i < size; i++)
    {
        int k = (i+1) % size;
        int firstPoint_X = polyPoints[i][0], firstPoint_Y = polyPoints[i][1];
        int secondPoint_X = polyPoints[k][0], secondPoint_Y = polyPoints[k][1];

        if(firstPoint_X > xLeft && secondPoint_X > xLeft)
        {
            newPoints[newSize][0] = secondPoint_X;
            newPoints[newSize++][1] = secondPoint_Y;
        }
        else if ((firstPoint_X < xLeft && secondPoint_X > xLeft))
        {
            int x,y;
            vIntersect(firstPoint_X,firstPoint_Y,secondPoint_X,secondPoint_Y,xLeft,x,y);

            newPoints[newSize][0] = x;
            newPoints[newSize++][1] = y;

            newPoints[newSize][0] = secondPoint_X;
            newPoints[newSize++][1] = secondPoint_Y;

        }
        else if ((firstPoint_X > xLeft && secondPoint_X < xLeft))
        {
            int x,y;
            vIntersect(firstPoint_X,firstPoint_Y,secondPoint_X,secondPoint_Y,xLeft,x,y);

            newPoints[newSize][0] = x;
            newPoints[newSize++][1] = y;
        }
    }
    cpy(newPoints,newSize,polyPoints,size);
}

void rightClip(int polyPoints[][2], int &size, int xRight)
{
    int newPoints[10][2], newSize = 0;
    for (int i = 0; i < size; i++)
    {
        int k = (i+1) % size;
        int firstPoint_X = polyPoints[i][0], firstPoint_Y = polyPoints[i][1];
        int secondPoint_X = polyPoints[k][0], secondPoint_Y = polyPoints[k][1];

        if(firstPoint_X < xRight && secondPoint_X < xRight)
        {
            newPoints[newSize][0] = secondPoint_X;
            newPoints[newSize++][1] = secondPoint_Y;

        }
        else if (firstPoint_X > xRight && secondPoint_X < xRight)
        {
            int x,y;
            vIntersect(firstPoint_X,firstPoint_Y,secondPoint_X,secondPoint_Y,xRight,x,y);

            newPoints[newSize][0] = x;
            newPoints[newSize++][1] = y;

            newPoints[newSize][0] = secondPoint_X;
            newPoints[newSize++][1] = secondPoint_Y;
        }
        else if ((firstPoint_X < xRight && secondPoint_X > xRight))
        {
            int x,y;
            vIntersect(firstPoint_X,firstPoint_Y,secondPoint_X,secondPoint_Y,xRight,x,y);

            newPoints[newSize][0] = x;
            newPoints[newSize++][1] = y;
        }
    }
    cpy(newPoints,newSize,polyPoints,size);
}

void topClip(int polyPoints[][2], int &size, int yTop)
{
    int newPoints[10][2], newSize = 0;
    for (int i = 0; i < size; i++)
    {
        int k = (i+1) % size;
        int firstPoint_X = polyPoints[i][0], firstPoint_Y = polyPoints[i][1];
        int secondPoint_X = polyPoints[k][0], secondPoint_Y = polyPoints[k][1];

        if(firstPoint_Y < yTop && secondPoint_Y < yTop)
        {
            newPoints[newSize][0] = secondPoint_X;
            newPoints[newSize++][1] = secondPoint_Y;
        }
        else if (firstPoint_Y > yTop && secondPoint_Y < yTop)
        {
            int x,y;
            hIntersect(firstPoint_X,firstPoint_Y,secondPoint_X,secondPoint_Y,yTop,x,y);

            newPoints[newSize][0] = x;
            newPoints[newSize++][1] = y;

            newPoints[newSize][0] = secondPoint_X;
            newPoints[newSize++][1] = secondPoint_Y;
        }
        else if(firstPoint_Y < yTop && secondPoint_Y > yTop)
        {
            int x,y;
            hIntersect(firstPoint_X,firstPoint_Y,secondPoint_X,secondPoint_Y,yTop,x,y);

            newPoints[newSize][0] = x;
            newPoints[newSize++][1] = y;
        }
    }
    cpy(newPoints,newSize,polyPoints,size);

}

void bottomClip(int polyPoints[][2], int &size, int yBottom)
{
    int newPoints[10][2], newSize = 0;
    for (int i = 0; i < size; i++)
    {
        int k = (i+1) % size;
        int firstPoint_X = polyPoints[i][0], firstPoint_Y = polyPoints[i][1];
        int secondPoint_X = polyPoints[k][0], secondPoint_Y = polyPoints[k][1];

        if(firstPoint_Y > yBottom && secondPoint_Y > yBottom)
        {
            newPoints[newSize][0] = secondPoint_X;
            newPoints[newSize++][1] = secondPoint_Y;

        }
        else if ((firstPoint_Y < yBottom && secondPoint_Y > yBottom))
        {
            int x,y;
            hIntersect(firstPoint_X,firstPoint_Y,secondPoint_X,secondPoint_Y,yBottom,x,y);

            newPoints[newSize][0] = x;
            newPoints[newSize++][1] = y;

            newPoints[newSize][0] = secondPoint_X;
            newPoints[newSize++][1] = secondPoint_Y;
        }
        else if  (firstPoint_Y > yBottom && secondPoint_Y < yBottom)
        {
            int x,y;
            hIntersect(firstPoint_X,firstPoint_Y,secondPoint_X,secondPoint_Y,yBottom,x,y);

            newPoints[newSize][0] = x;
            newPoints[newSize++][1] = y;
        }
    }
    cpy(newPoints,newSize,polyPoints,size);
}

void clip(HWND hwnd,int polyPoints[][2], int &size, int xLeft, int yTop, int xRight, int yBottom)
{
    int h,w;
    RECT rect;
    if(GetWindowRect(hwnd, &rect))
    {
        w = rect.right - rect.left;
        h = rect.bottom - rect.top;
    }

    HDC hdc = GetDC(hwnd);
    cout<<"OLD\n";
    drawPoly(hdc,polyPoints,size,RGB(255,0,0));

    COLORREF color = RGB(0,0,255);
    leftClip(polyPoints,size,xLeft);
    Sleep(800);

//    InvalidateRect(hwnd, &rect, TRUE);
    BitBlt(hdc, 0,0, w, h, 0,0,0, WHITENESS);

    drawSquare(hdc,xLeft,yTop,xRight,yBottom);
    cout<<"\n";
    drawPoly(hdc,polyPoints,size,color);
//    ValidateRect(hwnd, &rect);

    rightClip(polyPoints,size,xRight);
    Sleep(800);

//    InvalidateRect(hwnd, NULL, TRUE);
    BitBlt(hdc, 0,0, w, h, 0,0,0, WHITENESS);
    drawSquare(hdc,xLeft,yTop,xRight,yBottom);
    cout<<"\n";
    drawPoly(hdc,polyPoints,size,color);

    bottomClip(polyPoints,size,yBottom);
    Sleep(800);

//    InvalidateRect(hwnd, NULL, TRUE);
    BitBlt(hdc, 0,0, w, h, 0,0,0, WHITENESS);
    drawSquare(hdc,xLeft,yTop,xRight,yBottom);
    cout<<"\n";
    drawPoly(hdc,polyPoints,size,color);

    topClip(polyPoints,size,yTop);
    Sleep(800);

//    InvalidateRect(hwnd, NULL, TRUE);
    BitBlt(hdc, 0,0, w, h, 0,0,0, WHITENESS);
    drawSquare(hdc,xLeft,yTop,xRight,yBottom);
    cout<<"Final\n";
    drawPoly(hdc,polyPoints,size,color);
}
