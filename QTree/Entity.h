#include "BasicType.h"

class Entity
{
    Point   pos;
    int     id;

public:
    Point GetPos()
    {
        return pos;
    }

    Point GetPos() const
    {
        return pos;
    }

    void SetPos(float x, float y)
    {
        pos.x = x;
        pos.y = y;
    }

    void SetPos(const Point &p)
    {
        pos =  p;
    }

    void SetId(int _id)
    {
        id = _id;
    }

    int GetId()
    {
        return id;
    }
};