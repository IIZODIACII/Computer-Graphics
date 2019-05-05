#include <bits/stdc++.h>
using namespace std;

/**  Helpers   **/
void swap(int &a, int &b, int &c, int &d)
{
    int temp = a;
    a = b;
    b = temp;

    temp = c;
    c = d;
    d = temp;
}
/***************************************************/

void lineParam(HDC hdc, int x1, int y1, int x2, int y2, COLORREF color)
{
    double dx = x2 - x1, dy = y2 - y1;
    double dt = 1.0 / (max(abs(dx), abs(dy)) + 1);

    for (double t = 0; t <= 1; t += dt)
    {
        int x = round(x1 + t * dx);
        int y = round(y1 + t * dy);
        SetPixel(hdc, x, y, color);
        savePoint(x, y);
    }
}
void simpleLineDDA(HDC hdc, int x1, int y1, int x2, int y2, COLORREF color)
{

    int dy = y2 - y1;
    int dx = x2 - x1;
    if (abs(dy) > abs(dx)) // if slope < 1 --> add or sub 1 from x & add or sub the slope from y
    {
        int yinc = dy > 0 ? 1 : -1;
        double x = x1;
        double xinc = (double)dx / dy * yinc;
        for (int y = y1; y != y2; y += yinc)
        {
            x += xinc;
            SetPixel(hdc, round(x), y, color);
            savePoint(round(x), y);
        }
    }
    else // if slope > 1 --> add or sub y from x & add or sub the slope from x
    {
        int xinc = dx > 0 ? 1 : -1;
        double y = y1;
        double yinc = (double)dy / dx * xinc;
        for (int x = x1; x != x2; x += xinc)
        {
            SetPixel(hdc, x, round(y), color);
            savePoint(x, round(y));
            y += yinc;
        }
    }
}
void intLineDDA(HDC hdc, int x1, int y1, int x2, int y2, COLORREF color)
{
    // cout << "what up?";
    int dy = y2 - y1;
    int dx = x2 - x1;
    double m = (double)dy / dx;
    dy = abs(dy);
    dx = abs(dx);
    int x, y, e, e1 = 2 * dx, e2 = 2 * dy;

    if (dx > dy) // slope is between 0 & 1 or between 0 & -1
    {
        //        cout<<"dx = "<<dx<<" dy = "<<dy<<endl;

        e = 2 * dy - dx;
        if (x1 > x2) // to unify and make a single while loop
            swap(x1, x2, y1, y2);

        x = x1;
        y = y1;
        SetPixel(hdc, x, y, color);
        savePoint(x, y);
        // if  0 <= slope <= 1 we sub e1 from e if e >= 0 else add e2 and increment x,y
        /**
          \
            \
              \
                \
                  \
                    \
                      \
                        \
        **/
        if (m >= 0 && m <= 1)
        {
            //            cout << "m >= 0 && m <= 1\n";

            while (x < x2)
            {
                x++;
                if (e >= 0)
                {
                    y++;
                    e -= e1;
                }
                e += e2;
                SetPixel(hdc, x, y, color);
                savePoint(x, y);
            }
        }
        // if 0 >= slope >= -1 we add e1 from e if e >= 0 else sub e2 and increment x, decrement y
        /**
                              /
                            /
                          /
                        /
                      /
                    /
                  /
        **/
        else if (m <= 0 && m >= -1)
        {
            //            cout << "m<=0 && m >= -1\n";
            while (x < x2)
            {
                x++;
                if (e <= 0)
                {
                    y--;
                    e += e1;
                }
                e -= e2;

                SetPixel(hdc, x, y, color);
                savePoint(x, y);
            }
        }
    }

    else
    {
        //        cout<<"dx = "<<dx<<" dy = "<<dy<<endl;

        e = 2 * dx - dy;
        if (y1 > y2) // to unify and make a single while loop
            swap(x1, x2, y1, y2);

        x = x1;
        y = y1;
        SetPixel(hdc, x, y, color);
        savePoint(x, y);

        //        if slope > 1 we sub e2 from e if e >= 0 else add e1 and increment x,y
        /**
                  \
                   \
                    \
                     \
        **/
        if (m > 1)
        {
            //            cout << "m>1\n";
            while (y < y2)
            {
                y++;
                if (e >= 0)
                {
                    x++;
                    e -= e2;
                }
                e += e1;

                SetPixel(hdc, x, y, color);
                savePoint(x, y);
            }
        }
        //if slope <= -1 we add e2 from e if e >= 0 else sub e1 and increment y, decrement x
        /**
                        /
                       /
                      /
                     /
        **/
        else if (m <= -1)
        {
            //            cout << "m<=1\n";
            x = x1;
            y = y1;
            while (y < y2)
            {
                y++;
                if (e <= 0)
                {
                    x--;
                    e += e2;
                }
                e -= e1;

                SetPixel(hdc, x, y, color);
                savePoint(x, y);
            }
        }
    }
}

void lineMidPoint(HDC hdc, int x1, int y1, int x2, int y2, COLORREF color)
{
    int dx = x2 - x1;
    int dy = y2 - y1;
    int x = x1;
    int y = y1;
    double m = (double)dy / dx;

    SetPixel(hdc, x, y, color);
    savePoint(x, y);

    if (abs(dx) > abs(dy))
    {
        if (x1 > x2)
        {
            swap(x1, x2, y1, y2);
            dx *= -1;
            dy *= -1;
        }
        x = x1;
        y = y1;

        if (m >= 0 && m <= 1)
        {
            //            cout << "m >= 0 && m <= 1\n";
            int d = dx - 2 * dy;
            int d1 = 2 * (dx - dy);
            int d2 = -2 * dy;
            SetPixel(hdc, x, y, color);
            savePoint(x, y);

            while (x < x2)
            {
                x++;
                if (d < 0)
                {
                    d += d1;
                    y++;
                }
                else
                    d += d2;
                SetPixel(hdc, x, y, color);
                savePoint(x, y);
            }
        }
        else if (m <= 0 && m >= -1)
        {
            //            cout << "m<=0 && m >= -1\n";

            int d = -1 * dx - 2 * dy;
            int d1 = -2 * (dx - dy);
            int d2 = -2 * dy;

            while (x < x2)
            {
                x++;
                if (d > 0)
                {
                    y--;
                    d += d1;
                }
                else
                    d += d2;
                SetPixel(hdc, x, y, color);
                savePoint(x, y);
            }
        }
    }
    else
    {
        if (y1 > y2)
        {
            swap(x1, x2, y1, y2);
            dx *= -1;
            dy *= -1;
        }
        x = x1;
        y = y1;
        if (m > 1)
        {
            //            cout << "m>1\n";
            int d = 2 * dx - dy;
            int d1 = 2 * (dx - dy);
            int d2 = 2 * dx;
            while (y != y2)
            {
                y++;
                if (d > 0)
                {
                    d += d1;
                    x++;
                }
                else
                {
                    d += d2;
                }
                SetPixel(hdc, x, y, color);
                savePoint(x, y);
            }
        }
        else if (m <= -1)
        {
            //            cout << "m<=1\n";
            int d = 2 * dx + dy;
            int d1 = 2 * (dx + dy);
            int d2 = 2 * dx;
            SetPixel(hdc, x, y, color);
            savePoint(x, y);

            while (y < y2)
            {
                y++;
                if (d < 0)
                {
                    d += d1;
                    x--;
                }
                else
                    d += d2;
                SetPixel(hdc, x, y, color);
                savePoint(x, y);
            }
        }
    }
}
