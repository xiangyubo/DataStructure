template<typename T>
class CMemoryPool
{
    public:
        const static int EXPANSION_SIZE = 32;

        CMemoryPool(unsigned int nItemCount = EXPANSION_SIZE)
        {
            ExpandFreeList(nItemCount);
        }
        
        ~CMemoryPool()
        {
            CMemoryPool<T>* pNext = NULL;
            for(pNext = m_pFreeList; pNext != NULL; pNext = m_pFreeList)
            {
                m_pFreeList = m_pFreeList->m_pFreeList;
                delete [](char*)pNext;
            }
        }

        void* Alloc(unsigned int)
        {
            if(m_pFreeList == NULL)
            {
                ExpandFreeList();
            }
            
            CMemoryPool<T>* pHead = m_pFreeList;
            m_pFreeList = m_pFreeList->m_pFreeList;
            return pHead;
        }

        void Free(void* p)
        {
            CMemoryPool<T>* pHead = static_cast<CMemoryPool<T>*>(p);
            pHead->m_pFreeList = m_pFreeList;
            m_pFreeList = pHead;
        }

    protected:
        void ExpandFreeList(unsigned nItemCount = EXPANSION_SIZE)
        {
            unsigned int nSize = sizeof(T) > sizeof(CMemoryPool<T>*) ? sizeof(T) : sizeof(CMemoryPool<T>*);
            CMemoryPool<T>* pLastItem = reinterpret_cast<CMemoryPool<T>*>(new char[nSize]);
            m_pFreeList = pLastItem;
            for(int i=0; i<nItemCount-1; ++i)
            {
                pLastItem->m_pFreeList = reinterpret_cast<CMemoryPool<T>*>(new char[nSize]);
                pLastItem = pLastItem->m_pFreeList;
            }

            pLastItem->m_pFreeList = NULL;
        }

    private:
        CMemoryPool<T>* m_pFreeList;
};