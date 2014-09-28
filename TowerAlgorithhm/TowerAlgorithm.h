#include<vector>
#include"BasicType.h"
using std::vector;

class TowerMap
{
private:
    struct Node
    {
        Rectangle rect;
        vector<Position*> entities;

        Node(const Rectangle &rt = Rectangle(Position(), Position())):rect(rt) {}
    };
    Rectangle rect;
    vector<vector<Node>> towerMap;

public:
    TowerMap(const std::size_t row, const std::size_t col, const float l, const float h);
    void insert(const Position *);
    void remove(const Position *);
    vector<Position> find_in_rect(const Rectangle &rect);
};