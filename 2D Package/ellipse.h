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

void drawEllipseMidPoint(HDC hdc, int xc, int yc, int horizontalRadius, int verticalradius, COLORREF rgb)
{

    double y = verticalradius, x = 0;
    double HRadiusSquare = pow(horizontalRadius, 2), verticalRadius = pow(verticalradius, 2);
    int d = verticalRadius - (HRadiusSquare * verticalRadius) + (0.25 * HRadiusSquare);
    draw4Pixels(hdc, xc, yc, round(x), round(y), rgb);
    while (verticalRadius * x <= HRadiusSquare * y)
    {
        x++;
        if (d > 0)
        {
            y--;
            d += verticalRadius * (2 * x + 3) + HRadiusSquare * (-2 * y + 2);
        }
        else
        {
            d += verticalRadius * (2 * x + 3);
        }
        draw4Pixels(hdc, xc, yc, round(x), round(y), rgb);
    }
    d = pow((x + 0.5), 2) * verticalRadius + HRadiusSquare * pow((y - 1), 2) - HRadiusSquare * verticalRadius;
    draw4Pixels(hdc, xc, yc, round(x), round(y), rgb);
    while (y != 0)
    {
        y--;
        if (d > 0)
        {
            d += HRadiusSquare * (-2 * y + 3);
        }
        else
        {
            x++;
            d += verticalRadius * (2 * x + 2) + HRadiusSquare * (-2 * y + 3);
        }
        draw4Pixels(hdc, xc, yc, round(x), round(y), rgb);
    }
}
