#include <cmath>
#include <iostream>
using namespace std;

void draw4Pixels(HDC hdc, int xc, int yc, int x, int y, COLORREF color)
{
    SetPixel(hdc, xc + x, yc + y, color);
    SetPixel(hdc, xc + x, yc - y, color);
    SetPixel(hdc, xc - x, yc - y, color);
    SetPixel(hdc, xc - x, yc + y, color);
    savePoint(xc + x, yc + y);
    savePoint(xc + x, yc - y);
    savePoint(xc - x, yc - y);
    savePoint(xc - x, yc + y);
}

void drawEllipseDirect(HDC hdc, int xc, int yc, int horizontalRadius, int verticalRadius, COLORREF rgb)
{
    double x = horizontalRadius;
    double y = 0;
    double HRadiusSquare = pow(horizontalRadius, 2);
    double VRadiusSquare = pow(verticalRadius, 2);
    draw4Pixels(hdc, xc, yc, x, y, rgb);

    while ((VRadiusSquare * x) > (HRadiusSquare * y))
    {
        y++;
        x = sqrt((double)(HRadiusSquare * (1 - (pow(y, 2) / (VRadiusSquare)))));
        draw4Pixels(hdc, xc, yc, round(x), round(y), rgb);
    }

    x = 0;
    y = verticalRadius;
    while ((VRadiusSquare * x) < (HRadiusSquare * y))
    {
        x++;
        y = sqrt((double)(VRadiusSquare * (1 - (pow(x, 2) / (HRadiusSquare)))));
        draw4Pixels(hdc, xc, yc, round(x), round(y), rgb);
    }
}

void drawEllipsePolar(HDC hdc, int xc, int yc, int horizontalRadius, int verticalRadius, COLORREF rgb)
{
    double x = horizontalRadius;
    double y = 0;
    double theta = 0;
    double d = 0.001;
    while (theta <= 1.57) // PI / 2 = 1.57
    {
        x = horizontalRadius * cos(theta);
        y = verticalRadius * sin(theta);
        theta += d;
        draw4Pixels(hdc, xc, yc, round(x), round(y), rgb);
    }
}

void drawEllipseMidPoint(HDC hdc, int xc, int yc, int horzRad, int vertRad, COLORREF rgb)
{
    float dx, dy, d1, d2, x, y;
    x = 0;
    y = vertRad;

    // region 1
    d1 = (vertRad * vertRad) - (horzRad * horzRad * vertRad) +
         (0.25 * horzRad * horzRad);
    dx = 2 * vertRad * vertRad * x;
    dy = 2 * horzRad * horzRad * y;

    
    while (dx < dy)
    {

        // Print points based on 4-way symmetvertRad
        draw4Pixels(hdc, xc, yc, x, y, rgb);

    
        // decision parameter based on algorithm
        if (d1 < 0)
        {
            x++;
            dx = dx + (2 * vertRad * vertRad);
            d1 = d1 + dx + (vertRad * vertRad);
        }
        else
        {
            x++;
            y--;
            dx = dx + (2 * vertRad * vertRad);
            dy = dy - (2 * horzRad * horzRad);
            d1 = d1 + dx - dy + (vertRad * vertRad);
        }
    }

    // region 2
    d2 = ((vertRad * vertRad) * ((x + 0.5) * (x + 0.5))) +
         ((horzRad * horzRad) * ((y - 1) * (y - 1))) -
         (horzRad * horzRad * vertRad * vertRad);


    while (y >= 0)
    {

      
        draw4Pixels(hdc, xc, yc, x, y, rgb);

        
        if (d2 > 0)
        {
            y--;
            dy = dy - (2 * horzRad * horzRad);
            d2 = d2 + (horzRad * horzRad) - dy;
        }
        else
        {
            y--;
            x++;
            dx = dx + (2 * vertRad * vertRad);
            dy = dy - (2 * horzRad * horzRad);
            d2 = d2 + dx - dy + (horzRad * horzRad);
        }
    }
}
