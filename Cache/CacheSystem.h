#ifndef __CACHE_SYSTEM__
#define __CACHE_SYSTEM__

#include <map>
#include <list>
#include <vector>

static const float HitRatioLimit = 0.8f;

// ************************
//  CacheSystem�����࣬����
//  �������ظ�����Դ��ʵ��
//  ��Ԫģʽ���𲽽׶��ڴ�
//  ָ��������������������
//  ��̭\������
// ************************
template<typename Key, typename Data>
class CacheSystem
{
protected:
    // ************************
    //  CacheUnitInfo���嵥Ԫ��
    //  Ϣ�ṹ������������̭��
    //  ��ĵ�Ԫ��
    // ************************
    struct CacheUnitInfo
    {
        //��ָ̭�꣬������δʹ��
        int lru;

        //��Ӧ�ļ�
        Key key;
    };

protected:
    //���ݻ��壬ʹ��vector
    std::vector<Data>    _dataCache;

    //��->���������ı�
    std::map<Key, int>   _key2Data;

    //��̭�������ֽ�������
    std::list<CacheUnitInfo> _eliminateList;

    //��������������ʣ������ж�
    //���ڴ�ʱ�Ƿ��б�Ҫ�����ڴ�
    float   _hitRatio;

    //���д���
    int _hitNum;

    //��ѯ����
    int _totalNum;

    //ָ�����ӷֽ��ߣ�֮ǰֱ��ָ
    //��������֮���ж���������չ
    int _threshold;

public:
    //��ʼ�������ֽ���
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

    //��ȡ����
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

    //�黹����
    void ReturnData(Data* &ptr)
    {
        ptr = nullptr;
    }

    //��ͬ�������͵Ĳ�ͬ���ط�ʽ
    virtual Data LoadDataFrom(Key key) = 0;

    //��չ�ڴ棬����ֵΪ��С��������
    virtual int Expand() final
    {
        if(_dataCache.capacity() < _threshold)
        {
            if(_dataCache.size() == _dataCache.capacity())
            {
                //�ڴ�ռ�����ϵͣ�����ʱֱ����չ
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
                    //�ڴ�ռ�ýϸ��������ʸߣ���չ����
                    _dataCache.reserve(2*_dataCache.capacity());
                }
                else
                {
                    //�ڴ�ռ�ýϸ��������ʲ��ߣ���̭����
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

    //������̭��
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