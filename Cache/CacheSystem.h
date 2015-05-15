#ifndef __CACHE_SYSTEM__
#define __CACHE_SYSTEM__

#include <map>
#include <list>
#include <vector>

static const float HitRatioLimit = 0.8f;

// ************************
//  CacheSystem缓冲类，管理
//  大量而重复的资源，实现
//  享元模式。起步阶段内存
//  指数增长，后面依据命中
//  淘汰\增长。
// ************************
template<typename Key, typename Data>
class CacheSystem
{
protected:
    // ************************
    //  CacheUnitInfo缓冲单元信
    //  息结构体用来构造淘汰链
    //  表的单元。
    // ************************
    struct CacheUnitInfo
    {
        //淘汰指标，最近最久未使用
        int lru;

        //对应的键
        Key key;
    };

protected:
    //数据缓冲，使用vector
    std::vector<Data>    _dataCache;

    //键->数据索引的表
    std::map<Key, int>   _key2Data;

    //淘汰链，保持降序排列
    std::list<CacheUnitInfo> _eliminateList;

    //整个缓冲的命中率，用于判断
    //高内存时是否有必要扩大内存
    float   _hitRatio;

    //命中次数
    int _hitNum;

    //查询次数
    int _totalNum;

    //指数增加分界线，之前直接指
    //数增长，之后判断命中率扩展
    int _threshold;

public:
    //初始化增长分界线
    CacheSystem(int thr = 1024)
    {
        _dataCache.reserve(32);
        _hitRatio = 0.0f;
        _hitNum = 0;
        _totalNum = 0;
        _threshold = thr>32?thr:1024;
    }

    virtual ~CacheSystem()
    {
        _dataCache.clear();
        _eliminateList.clear();
        _key2Data.clear();
    }

    //获取数据
    Data* GetData(Key key)
    {
        _totalNum++;
        if(_key2Data.find(key) != _key2Data.end())
        {
            _hitNum++;
        }
        else
        {
            int index = Expand();
            Data data = LoadDataFrom(key);
            _key2Data[key] = index;
            if(index < _dataCache.size())
            {
                _dataCache[index] = data;
            }
            else
            {
                _dataCache.push_back(data);
            }
            CacheUnitInfo unit;
            unit.lru = 0;
            unit.key = key;
            _eliminateList.push_back(unit);

        }
        int index = _key2Data[key];
        return &_dataCache[index];
    }

    //归还数据
    void ReturnData(Data* &ptr)
    {
        ptr = nullptr;
    }

    //不同数据类型的不同加载方式
    virtual Data LoadDataFrom(Key key) = 0;

    //扩展内存，返回值为最小可用索引
    virtual int Expand() final
    {
        if(_dataCache.capacity() < _threshold)
        {
            if(_dataCache.size() == _dataCache.capacity())
            {
                //内存占用量较低，用完时直接扩展
                _dataCache.reserve(2*_dataCache.capacity());
            }
        }
        else if(_dataCache.capacity() >= _threshold)
        {
            _hitRatio = (float)_hitNum / _totalNum;
            if(_dataCache.size() == _dataCache.capacity())
            {
                if(_hitRatio >= HitRatioLimit)
                {
                    //内存占用较高且命中率高，扩展机制
                    _dataCache.reserve(2*_dataCache.capacity());
                }
                else
                {
                    //内存占用较高且命中率不高，淘汰机制
                    CacheUnitInfo elim = _eliminateList.front();
                    _eliminateList.pop_front();
                    int index = _key2Data[elim.key];
                    _key2Data.erase(elim.key);
                    return index;
                }
            }
        }
        return _dataCache.size();
    }

    //调整淘汰链
    void AdjustEliminateList(Key key)
    {
        bool flag = false;
        for(auto it = _eliminateList.begin(); 
            it != _eliminateList.end(); )
        {
            if(key != it->key)
            {
                it->lru++;
                ++it
            }
            else if(flag == false)
            {
                flag = true;
                it->lru = 0;
                CacheUnitInfo temp(*it);
                it = _eliminateList.erase(it);
                _eliminateList.push_back(temp);
            }
        }
    }
};

#endif