#if defined(UNICODE) && !defined(_UNICODE)
#define _UNICODE
#elif defined(_UNICODE) && !defined(UNICODE)
#define UNICODE
#endif

#include <tchar.h>
#include <windows.h>
#include "menu.h"
#include "ellipse.h"
#include "lines.h"
#include "curves.h"
#include "clipping.h"
/*  Declare Windows procedure  */
LRESULT CALLBACK WindowProcedure(HWND, UINT, WPARAM, LPARAM);

int id;

/*  Make the class name into a global variable  */
TCHAR szClassName[] = _T("CodeBlocksWindowsApp");
int WINAPI WinMain(HINSTANCE hThisInstance, HINSTANCE hPrevInstance, LPSTR lpszArgument, int nCmdShow)
{
    HWND hwnd;        /* This is the handle for our window */
    MSG messages;     /* Here messages to the application are saved */
    WNDCLASSEX wincl; /* Data structure for the windowclass */

    /* The Window structure */
    wincl.hInstance = hThisInstance;
    wincl.lpszClassName = szClassName;
    wincl.lpfnWndProc = WindowProcedure; /* This function is called by windows */
    wincl.style = CS_DBLCLKS;            /* Catch double-clicks */
    wincl.cbSize = sizeof(WNDCLASSEX);

    /* Use default icon and mouse-pointer */
    wincl.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    wincl.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
    wincl.hCursor = LoadCursor(NULL, IDC_ARROW);
    wincl.lpszMenuName = MAKEINTRESOURCE(ID); /* No menu */
    wincl.cbClsExtra = 0;                     /* No extra bytes after the window class */
    wincl.cbWndExtra = 0;                     /* structure or the window instance */
    /* Use Windows's default colour as the background of the window */
    wincl.hbrBackground = (HBRUSH)COLOR_BACKGROUND;

    /* Register the window class, and if it fails quit the program */
    if (!RegisterClassEx(&wincl))
        return 0;

    /* The class is registered, let's create the program*/
    hwnd = CreateWindowEx(
        0,                                       /* Extended possibilites for variation */
        szClassName,                             /* Classname */
        _T("Code::Blocks Template Windows App"), /* Title Text */
        WS_OVERLAPPEDWINDOW,                     /* default window */
        CW_USEDEFAULT,                           /* Windows decides the position */
        CW_USEDEFAULT,                           /* where the window ends up on the screen */
        600,                                     /* The programs width */
        600,                                     /* and height in pixels */
        HWND_DESKTOP,                            /* The window is a child-window to desktop */
        NULL,                                    /* No menu */
        hThisInstance,                           /* Program Instance handler */
        NULL                                     /* No Window Creation data */
    );

    /* Make the window visible on the screen */
    ShowWindow(hwnd, nCmdShow);

    /* Run the message loop. It will run until GetMessage() returns 0 */
    while (GetMessage(&messages, NULL, 0, 0))
    {
        /* Translate virtual-key messages into character messages */
        TranslateMessage(&messages);
        /* Send message to WindowProcedure */
        DispatchMessage(&messages);
    }

    /* The program return-value is 0 - The value that PostQuitMessage() gave */
    return messages.wParam;
}

/*  This function is called by the Windows function DispatchMessage()  */
int horizontalRadius, verticalRadius, counter = 0;
COLORREF color = RGB(1, 126, 230);
int arrX[10], arrY[10];
int xLeft = 100, yTop = 200, xRight = 200, yBottom = 100;

LRESULT CALLBACK WindowProcedure(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    HDC hdc = GetDC(hwnd);
    switch (message) /* handle the messages */
    {
    case WM_COMMAND:
        id = LOWORD(wParam);
        if(id == CLIP)
        {
            drawSquare(hdc,xLeft,yTop,xRight,yBottom);
        }
        break;
    case WM_LBUTTONUP:
        if (counter == 0)
            ReleaseDC(hwnd, hdc);
        arrX[counter] = LOWORD(lParam);
        arrY[counter] = HIWORD(lParam);
        if (counter == 1)
        {
            horizontalRadius = abs(arrX[0] - arrX[1]);
            verticalRadius = abs(arrY[0] - arrY[1]);
        }
        counter++;

        if (counter == 2)
        {
            if (id == LINE_DDA)
            {
                intLineDDA(hdc, arrX[0], arrY[0], arrX[1], arrY[1], color);
                counter = 0;
            }
            else if (id == LINE_PARAMETRIC)
            {

                lineParam(hdc, arrX[0], arrY[0], arrX[1], arrY[1], color);
                counter = 0;
            }
            else if (id == LINE_MIDPOINT)
            {

                lineMidPoint(hdc, arrX[0], arrY[0], arrX[1], arrY[1], color);
                counter = 0;
            }
        }

        else if (counter == 3)
        {
            if (id == ELLIPSE_DIRECT)
            {
                drawEllipseDirect(hdc, arrX[0], arrY[0], horizontalRadius, verticalRadius, color);
                counter = 0;
            }
            else if (id == ELLIPSE_POLAR)
            {
                drawEllipsePolar(hdc, arrX[0], arrY[0], horizontalRadius, verticalRadius, color);
                counter = 0;
            }
            else if (id == ELLIPSE_MIDPOINT)
            {

                drawEllipseMidPoint(hdc, arrX[0], arrY[0], horizontalRadius, verticalRadius, color);
                counter = 0;
            }
        }

        else if (counter == 4)
        {
            if (id == BEZIER_QUADRATIC_CURVE)
            {

                bezierCurve(hdc, arrX[0], arrY[0], arrX[1], arrY[1], arrX[2], arrY[2], arrX[3], arrY[3], color);
                counter = 0;
            }
            else if (id == HERMITE_CURVE)
            {
                counter = 0;
                hermiteCurve(hdc, arrX[0], arrY[0], arrX[1], arrY[1], arrX[2], arrY[2], arrX[3], arrY[3], color);
            }
        }

        else if (counter == 5)
        {
            if (id == SPLINES)
            {
                spline(hdc, arrX, arrY, 4, color);
                counter = 0;
            }
            if (id == CLIP)
            {
                int polyPoints[counter][2];
                for(int i = 0; i <= counter; i++)
                {
                    polyPoints[i][0] = arrX[i];
                    polyPoints[i][1] = arrY[i];
                }
                clip(hwnd,polyPoints,counter,xLeft,yTop,xRight,yBottom);
            }
        }

        break;
    case WM_DESTROY:
        PostQuitMessage(0); /* send a WM_QUIT to the message queue */
        break;
    default: /* for messages that we don't deal with */
        return DefWindowProc(hwnd, message, wParam, lParam);
    }

    return 0;
}
