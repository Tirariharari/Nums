#include <iostream>
#include <math.h>

using namespace std;

float iteration_x (float x, float y)
{
    x = 0.7 - cos (y-1);
    return x;
}

float iteration_y (float x, float y)
{
    y = 1 - sin (x)/2;
    return y;
}

int main()
{
    float e_x = 1;
    float e_y = 1;
    float x0 = 1;
    float x1 = 0;
    float y0 = 1;
    float y1 = 0;
    int i = 0;
    while (e_x > 0.00001 || e_y > 0.00001){
        x1 = iteration_x(x0, y0);
        e_x = fabs(x1-x0);
        x0 = x1;
        y1 = iteration_y(x0, y0);
        e_y = fabs(y1-y0);
        y0 = y1;
        i++;
        cout <<"At " << i << " iteration x = " << x1 << " E = " << e_x;
        cout << " and y = " << y1 << " E = " << e_y << endl;
    }
    cout << "Result : x = " << x1 << " y = " << y1 << endl;
    return 0;
}
