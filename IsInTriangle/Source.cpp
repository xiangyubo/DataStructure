#include<iostream>
using namespace std;

struct Vector
{
    float x;
    float y;
    Vector(const float _x= 0.0, const float _y = 0.0):
        x(_x), y(_y)
    {}

    float operator *(const Vector &a) const
    {
        return x*a.y - y*a.x;
    }
};

struct Point
{
    float x;
    float y;
    Point(const float _x= 0.0, const float _y = 0.0):
        x(_x), y(_y)
    {}

    Vector operator - (const Point &a) const
    {
        return Vector(x - a.x, y - a.y);
    }
};

bool is_in_triangle(const Point a, const Point b, const Point c, const Point d)
{
    Vector da = a - d;
    Vector db = b - d;
    Vector dc = c - d;

    float ta = da * db;
    float tb = db * dc;
    float tc = dc * da;

    if(ta >= 0 && tb >= 0 && tc >= 0 || ta < 0 && tb < 0 && tc < 0)
        return true;
    return false;
}

int main()
{
    Point a(-1, 0);
    Point b(4, 0);
    Point c(0, 3);
    Point d(-1, 0);

    cout<<is_in_triangle(a, b, c, d)<<endl;
    return 0;
}