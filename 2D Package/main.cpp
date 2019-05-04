#if defined(UNICODE) && !defined(_UNICODE)
    #define _UNICODE
#elif defined(_UNICODE) && !defined(UNICODE)
    #define UNICODE
#endif

#include <tchar.h>
#include <windows.h>
#include "lines.h"
#include "clipping.h"
#include "curves.h"

/*  Declare Windows procedure  */
LRESULT CALLBACK WindowProcedure (HWND, UINT, WPARAM, LPARAM);

/*  Make the class name into a global variable  */
TCHAR szClassName[ ] = _T("CodeBlocksWindowsApp");

int WINAPI WinMain (HINSTANCE hThisInstance,
                     HINSTANCE hPrevInstance,
                     LPSTR lpszArgument,
                     int nCmdShow)
{
    HWND hwnd;               /* This is the handle for our window */
    MSG messages;            /* Here messages to the application are saved */
    WNDCLASSEX wincl;        /* Data structure for the windowclass */

    /* The Window structure */
    wincl.hInstance = hThisInstance;
    wincl.lpszClassName = szClassName;
    wincl.lpfnWndProc = WindowProcedure;      /* This function is called by windows */
    wincl.style = CS_DBLCLKS;                 /* Catch double-clicks */
    wincl.cbSize = sizeof (WNDCLASSEX);

    /* Use default icon and mouse-pointer */
    wincl.hIcon = LoadIcon (NULL, IDI_APPLICATION);
    wincl.hIconSm = LoadIcon (NULL, IDI_APPLICATION);
    wincl.hCursor = LoadCursor (NULL, IDC_ARROW);
    wincl.lpszMenuName = NULL;                 /* No menu */
    wincl.cbClsExtra = 0;                      /* No extra bytes after the window class */
    wincl.cbWndExtra = 0;                      /* structure or the window instance */
    /* Use Windows's default colour as the background of the window */
    wincl.hbrBackground = (HBRUSH) COLOR_BACKGROUND;

    /* Register the window class, and if it fails quit the program */
    if (!RegisterClassEx (&wincl))
        return 0;

    /* The class is registered, let's create the program*/
    hwnd = CreateWindowEx (
           0,                   /* Extended possibilites for variation */
           szClassName,         /* Classname */
           _T("Code::Blocks Template Windows App"),       /* Title Text */
           WS_OVERLAPPEDWINDOW, /* default window */
           CW_USEDEFAULT,       /* Windows decides the position */
           CW_USEDEFAULT,       /* where the window ends up on the screen */
           544,                 /* The programs width */
           375,                 /* and height in pixels */
           HWND_DESKTOP,        /* The window is a child-window to desktop */
           NULL,                /* No menu */
           hThisInstance,       /* Program Instance handler */
           NULL                 /* No Window Creation data */
           );

    /* Make the window visible on the screen */
    ShowWindow (hwnd, nCmdShow);

    /* Run the message loop. It will run until GetMessage() returns 0 */
    while (GetMessage (&messages, NULL, 0, 0))
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
int x1,y1,x2,y2,u0,v0,u1,v1,counter = 0;
COLORREF color = RGB(0,0,0);
int polyPoints[5][2];
int xLeft = 100,yTop = 200, xRight = 200, yBottom = 100;

LRESULT CALLBACK WindowProcedure (HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    HDC hdc = GetDC(hwnd);
    /**
        CLIPPING
    lineMidPoint(hdc,xLeft,yBottom,xLeft,yTop,color);
    lineMidPoint(hdc,xLeft,yTop,xRight,yTop,color);
    lineMidPoint(hdc,xRight,yTop,xRight,yBottom,color);
    lineMidPoint(hdc,xLeft,yBottom,xRight,yBottom,color);
    **/
    switch (message)                  /* handle the messages */
    {
        case WM_DESTROY:
            PostQuitMessage (0);       /* send a WM_QUIT to the message queue */
            break;
//        case WM_LBUTTONDOWN:
//            x1 = LOWORD(lParam);
//            y1 = HIWORD(lParam);
//            break;
        case WM_LBUTTONUP:
            /**
            x2 = LOWORD(lParam);
            y2 = HIWORD(lParam);
            CLIPPING
            if(counter < 4)
            {
                polyPoints[counter][0] = x2;
                polyPoints[counter++][1] = y2;
            }
            else
            {
                polyPoints[counter][0] = x2;
                polyPoints[counter++][1] = y2;
                cout<<"OLD\n";
                for(int i = 0; i < (counter); i++)
                {
                    int k = (i+1) % (counter);
                    cout<<polyPoints[i][0]<<" "<<polyPoints[i][1]<<" "<<polyPoints[k][0]<<" "<<polyPoints[k][1]<<endl;
//                    intLineDDA(hdc,polyPoints[i][0],polyPoints[i][1],polyPoints[k][0],polyPoints[k][1],RGB(255,0,0));
                }
                cout<<"NEW\n";
                clip(polyPoints,counter,xLeft,yTop,xRight,yBottom);
                for(int i = 0; i < 5; i++)
                {
                    int k = (i+1) % 5;
                    cout<<polyPoints[i][0]<<" "<<polyPoints[i][1]<<" "<<polyPoints[k][0]<<" "<<polyPoints[k][1]<<endl;
                    intLineDDA(hdc,polyPoints[i][0],polyPoints[i][1],polyPoints[k][0],polyPoints[k][1],RGB(0,0,255));
                }
                counter = 0;
            }
            CLIIPING
            **/
                /** Line  **/
//            lineParam(hdc, x1,y1,x2,y2, color);
//            simpleLineDDA(hdc, x1, y1, x2, y2, color);
//            intLineDDA(hdc, x1, y1, x2, y2, color);
//            lineMidPoint(hdc, x1, y1, x2, y2, color);
                /** Line  **/
            break;
        default:                      /* for messages that we don't deal with */
            return DefWindowProc (hwnd, message, wParam, lParam);
    }

    return 0;
}