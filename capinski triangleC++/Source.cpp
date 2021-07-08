#include<iostream>
#include<windows.h>
#include <cmath>
#include <stdlib.h>     /* srand, rand */

struct point {
    float x, y;
};

void ShowConsoleCursor(bool showFlag)
{
    HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);

    CONSOLE_CURSOR_INFO     cursorInfo;

    GetConsoleCursorInfo(out, &cursorInfo);
    cursorInfo.bVisible = showFlag; // set the cursor visibility
    SetConsoleCursorInfo(out, &cursorInfo);
}

void printPoints(point p[], size_t size) {
    using namespace std;
    for (size_t i = 0; i < size; i++)
    {
        cout << p[i].x << " " << p[i].y << endl;
    }
}

int main() {

    using namespace std;

#define PI 3.14
    auto seed = time(NULL);
    while(1)
    {
        srand(seed);//random random.
        ShowConsoleCursor(false);
        //Get a console handle
        HWND myconsole = GetConsoleWindow();
        //Get a handle to device context
        HDC mydc = GetDC(myconsole);

        int min_area = 8 * 12600;
        //Choose any color
        int R = rand() % 255 + 1, G = rand() % 255 + 1, B = (int)G * G / R;
        int rgb_init[3] = { R,G,B };
        COLORREF COLOR = RGB(R, G, B);

        //Draw pixels
        //for (double i = 0; i < 25; i += 0.05)//0<x<50,0<y25
        //{
        //    SetPixel(mydc, (int)(50 + 25 * cos(i)), pixel, COLOR);
        //    pixel += 1;
        //}


        //need three random points
        point points[3];
        int area;
        int prod[3];
        size_t counter = 0;
        do {
        points[0].x = rand() % 1000;
        points[0].y = rand() % 500;
        points[1].x = rand() % 1000;
        points[1].y = rand() % 500;
        points[2].x = rand() % 1000;
        points[2].y = rand() % 500;
        //printPoints(points, 3);

        prod[0] = points[0].x * (points[1].y - points[2].y);
        prod[1] = points[1].x * (points[2].y - points[0].y);
        prod[2] = points[2].x * (points[0].y - points[1].y);
        area = (prod[0] + prod[1] + prod[2])/2;
        counter++;
        } while (abs(area) < min_area);
       
        for (size_t i = 0; i < 3; i++)
        {
            SetPixel(mydc, (int)points[i].y, (int)points[i].x, COLOR);
        }
        point cur = points[rand() % 3];//random starting point
        size_t len = 100000;
        for (size_t i = 0; i < len; i++)//pixels
        {
            point target;
            do{
                target = points[rand() % 3];

            } while (target.x == cur.x && target.y == cur.y);
            point half_diff_vec{ (target.x - cur.x) / 2, (target.y - cur.y) / 2 };
            cur.x = half_diff_vec.x + cur.x;//im sure i could work out the math better
            cur.y = half_diff_vec.y + cur.y;

            SetPixel(mydc, (int)cur.x, (int)cur.y, COLOR);
            if (0)
            {


                R = R - 255 * (i / len) > 0 ? R - 255 * (i / len) : -1 * (R - 255 * (i / len));
                if (R > 255)
                    R %= 255;
                G = 230 * (i) / len + 25;
                B = rand() % 2 ? 255 * sin(PI * i / len) : 255 * cos(PI * i / len);
                if (B < 0)
                    B *= -1;
            }
            else if (0){
                R = 255*cur.x / 1000;
                G = 85 * (cur.x / 1000 + cur.y / 500 + i/len);
                B = 255 * (cur.y / 500);

            }
            else if (1) {
                R = 255 * cur.x / 1000;
                G = 85 * (cur.x / 1000 + cur.y / 500 + i / len);
                B = 255 * (cur.y / 500);

                R = R - 255 * (i / len) > 0 ? R - 255 * (i / len) : -1 * (R - 255 * (i / len));
                if (R > 255)
                    R %= 255;
                G = 230 * (i) / len + 25;
                B = rand() % 2 ? 255 * sin(PI * i / len) : 255 * cos(PI * i / len);
                if (B < 0)
                    B *= -1;
            }
            COLOR = RGB(R, G, B);

            Sleep(.6);//waits one second b4 ploting next point
        }
        ReleaseDC(myconsole, mydc);
        cout << len << ", " << min_area << '\n';
        cout << seed << ", " << counter << '\n';
        cout << '(' << rgb_init[0] << ',' << rgb_init[1] << ',' << rgb_init[2] << ") --> (" << R << ',' << G << ',' << B << ")\n";
        seed = time(0);
        Sleep(2000);
        system("cls");
    }
        cin.ignore();
        return 0;

}