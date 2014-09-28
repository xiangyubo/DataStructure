#include"TowerAlgorithm.h"
TowerMap::TowerMap(const std::size_t row, const std::size_t col, const float l, const float h):
    rect(Position(0.0, row*h), Position(col*l, 0.0))
{
    towerMap.resize(row);
    for(std::size_t i = 0; i < towerMap.size(); ++i)
    {
        towerMap[i].resize(col);
        for(std::size_t j = 0; j < towerMap[i].size(); ++j)
        {
            towerMap[i][j] = Node(Rectangle(Position(j*l, i*h + h), Position(j*l + l, i*h)));
        }
    }
}

void TowerMap::insert(const Position *pos)
{
    if(rect.is_contain(*pos) == true)
    {
        std::size_t row = pos->y / towerMap[0][0].rect.lu.y;
        std::size_t col = pos->x / towerMap[0][0].rect.rd.x;
        towerMap[row][col].entities.push_back(const_cast<Position*>(pos));
    }
}

void TowerMap::remove(const Position *pos)
{
    if(rect.is_contain(*pos) == true)
    {
        std::size_t row = pos->y / towerMap[0][0].rect.lu.y;
        std::size_t col = pos->x / towerMap[0][0].rect.rd.x;
        for(auto it = towerMap[row][col].entities.begin(); 
            it != towerMap[row][col].entities.end(); ++it)
        {
            if(*it == pos)
            {
                towerMap[row][col].entities.erase(it);
                break;
            }
        }
    }
}

vector<Position> TowerMap::find_in_rect(const Rectangle &rt)
{
    vector<Position> ans;
    std::size_t lurow = rt.lu.y / towerMap[0][0].rect.lu.y;
    std::size_t lucol = rt.lu.x / towerMap[0][0].rect.rd.x;
    std::size_t rdrow = rt.rd.y / towerMap[0][0].rect.lu.y;
    std::size_t rdcol = rt.rd.x / towerMap[0][0].rect.rd.x;

    for(std::size_t i = rdrow; i <= lurow; ++i)
    {
        for(std::size_t j = lucol; j <= rdcol; ++j)
        {
            for(auto it = towerMap[i][j].entities.begin();
                it != towerMap[i][j].entities.end(); ++it)
            {
                if(rt.is_contain(**it) == true)
                {
                    ans.push_back(**it);
                }
            }
        }
    }
    return ans;
}