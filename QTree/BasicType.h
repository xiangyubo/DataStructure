#ifndef __QTREE_POINT__
#define __QTREE_POINT__

template<typename T>
T MyMax(const T &a, const T &b)
{
    return a < b ? b : a;
}

template<typename T>
T MyMin(const T &a, const T &b)
{
    return a < b ? a : b;
}

//基本坐标
struct Point
{
    float x;
    float y;

    Point():x(0), y(0)
    {
        
    }

    Point(float xx, float yy):x(xx), y(yy)
    {
        
    }

    bool operator == (const Point &pos) const
    {
        return (*(int*)&x == *(int*)&pos.x) && (*(int*)&y == *(int*)&pos.y);
    }
};

//矩形
struct Rect
{
    Point leftUp;
    Point rightDown;

    Rect(const Point _lu, const Point _rd):leftUp(_lu), rightDown(_rd) 
    {
        if(!(leftUp.x < rightDown.x && leftUp.y > rightDown.y))
        {
            leftUp.x = leftUp.y = rightDown.x = rightDown.y = 0.0f;
        }
    }
    
    bool IsContain(const Point &pos) const
    {
        return leftUp.x <= pos.x && 
            leftUp.y > pos.y &&
            rightDown.x > pos.x && 
            rightDown.y <= pos.y;
    }
    
    bool IsIntersect(const Rect &rt) const
    {
        if(leftUp.x > rt.rightDown.x)  return false;
        if(leftUp.y < rt.rightDown.y)  return false;
        if(rightDown.x < rt.leftUp.x)  return false;
        if(rightDown.y > rt.leftUp.y)  return false;
        return true;
    }
};

#endif