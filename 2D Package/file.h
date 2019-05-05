#include <bits/stdc++.h>
#include <windows.h>
#include <fstream>
#include <vector>
#ifndef FILE_H
#define FILE_H
using namespace std;

struct point
{
    int x;
    int y;
};

static vector<point> points;

void savePoint(int x, int y)
{
    points.push_back({x, y});
};

void printAllPoints()
{
    cout << "hello from print";
    for (point i : points)
        cout << " x : " << i.x << " y : " << i.y << endl;
};

void setAllPoints(HDC hdc)
{
    cout << "Setting pixels ";
    for (point i : points)
      SetPixel(hdc, i.x, i.y, RGB(1, 126, 230));
};

void saveToFile()
{
    ofstream outFile("points.txt");
    for (point i : points)
        outFile << i.x << "," << i.y << endl;
    outFile.close();
}

void LoadFromFile(HDC hdc)
{
    points.clear();
    ifstream infile("points.txt");
    if (infile.is_open())
    {
       int x , y;
       char comma;
        while (infile >> x >> comma >> y)
           points.push_back({x,y});
    }
    infile.close();
    setAllPoints(hdc);
}
#endif
