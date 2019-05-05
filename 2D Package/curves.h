#include<bits/stdc++.h>

using namespace std;

    /**    Helpers     **/

void multiply(int mat[][4],int arr[],int* res,int size)
{
    for(int i = 0; i < size; i++){
        for(int j = 0; j < size; j++)
            res[i] += (mat[i][j] * arr[j]);
    }
}

/**************************************/

void bezierCurve(HDC hdc, int x0, int y0, int u0, int v0, int x1, int y1, int u1, int v1, COLORREF color)
{
    int size = 4;
    int xArr[] = {x0, u0, x1, u1}, yArr[] = {y0, v0, y1, v1};
    int bezierMat[4][4] = {1, 0, 0, 0, -3, 3, 0, 0, 3, -6, 3, 0, -1, 3, -3, 1};

    int alphaX[size], alphaY[size];

    memset(alphaX,0,sizeof alphaX);
    memset(alphaY,0,sizeof alphaY);

    multiply(bezierMat, xArr, alphaX,size);
    multiply(bezierMat, yArr, alphaY, size);

    double x, y;
    for (double t = 0; t <= 1; t += 0.0001)
    {
        x = alphaX[0] + alphaX[1] * t  + alphaX[2] * t * t + alphaX[3] * t * t * t;
        y = alphaY[0] + alphaY[1] * t  + alphaY[2] * t * t + alphaY[3] * t * t * t;

        SetPixel(hdc, round(x), round(y), color);
        savePoint(round(x), y);

    }
}
void hermiteCurve(HDC hdc, int x0, int y0, int u0, int v0, int x1, int y1, int u1, int v1, COLORREF color)
{
    int size = 4;
    int xArr[] = {x0, u0, x1, u1}, yArr[] = {y0, v0, y1, v1};
    int hermiteMat[4][4] = {2, 1, -2, 1, -3, -2, 3, -1, 0, 1, 0, 0, 1, 0, 0, 0};
    int alphaX[size], alphaY[size];

    memset(alphaX,0,sizeof alphaX);
    memset(alphaY,0,sizeof alphaY);

    multiply(hermiteMat, xArr, alphaX,size);
    multiply(hermiteMat, yArr, alphaY, size);

//    for(int i = 0; i < 4; i++)
//        cout<<"alphaX = "<<alphaX[i]<<" ";
//    cout<<endl;
//    for(int i = 0; i < 4; i++)
//        cout<<"alphay = "<<alphaY[i]<<" ";
//    cout<<endl;

    double x, y;
    for (double t = 0; t <= 1; t += 0.0001)
    {
        x = alphaX[0] * t * t * t + alphaX[1] * t * t  + alphaX[2] * t + alphaX[3];
        y = alphaY[0] * t * t * t + alphaY[1] * t * t  + alphaY[2] * t + alphaY[3];

        SetPixel(hdc, round(x), round(y), color);
                         savePoint(round(x), y);

    }
}

void spline(HDC hdc, int xArr[], int yArr[], int size, COLORREF color)
{
    int u0 = (xArr[3] - xArr[0]), v0 = (yArr[3] - yArr[0]), u1, v1; // get the firs control points
    for (int i = 2; i < size - 1; i++)
    {
        // get the second control point
        u1 = (xArr[i + 1] - xArr[i - 1]);
        v1 = (yArr[i + 1] - yArr[i - 1]);

        hermiteCurve(hdc, xArr[i - 1], yArr[i - 1], u0, v0, xArr[i], yArr[i], u1, v1, color);

        u0 = u1;
        v0 = v1;
    }
}
