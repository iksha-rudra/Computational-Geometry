#include "minheap.h"
#include <bits/stdc++.h>

MinHeap::MinHeap():
    m_size(0)
{

}

bool MinHeap::extractMin(Point &info, double &key)
{
    Node min(Point(-1,-1),-1);

    if( !m_size )
    {
        return false;
    }
    else
    {
        min = m_Array[0];

        m_size--;

        m_Array[0] = m_Array[m_size];

        heapify(0, m_size);
    }

    info = min.info;

    key = min.key;

    return true;
}

Point MinHeap::extractMin()
{
    Point min(-1,-1);

    if( !m_size )
    {
        return min;
    }
    else
    {
        min = m_Array[0].info;

        m_size--;

        m_Array[0] = m_Array[m_size];

        heapify(0, m_size);
    }

    return min;
}

bool MinHeap::checkMin(Point &info, double &key)
{
    Node min(Point(-1,-1),-1);

    if( !m_size )
    {
        return false;
    }
    else
    {
        min = m_Array[0];
    }

    info = min.info;

    key = min.key;

    return true;
}

void MinHeap::insert(Point info, double key)
{
    Node temp(info,INT_MAX);

    m_Array.push_back(temp);

    m_size++;

    decreaseKey(m_size-1,key);
}

void MinHeap::insert(Point info,
                     double key,
                     Point refPoint)
{
    bool duplicate = false;

    for(int i=0; i < m_size; i++)
    {
        if(m_Array[i].key == key )
        {
            int deltaX = refPoint.x()-info.x();

            int deltaY = refPoint.y()-info.y();

            int disNew = sqrt(deltaX*deltaX + deltaY*deltaY);

            Point keyPoint = m_Array[i].info;

            deltaX = refPoint.x()-keyPoint.x();

            deltaY = refPoint.y()-keyPoint.y();

            int disExist = sqrt(deltaX*deltaX + deltaY*deltaY);

            if( disNew > disExist)
            {
                m_Array[i].info = info;
            }

            duplicate = true;

            break;
        }
    }

    if( duplicate )
    {
        return;
    }

    Node temp(info,INT_MAX);

    m_Array.push_back(temp);

    m_size++;

    decreaseKey(m_size-1,key);
}

bool MinHeap::isEmpty()
{
    if( !m_size )
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool MinHeap::decreaseKey(int index, double key)
{
    if( index < 0 && m_size >= index)
    {
        return false;
    }

    if(m_Array[index].key < key)
    {
        return false;
    }

    m_Array[index].key = key;

    while( index > 0 &&
           m_Array[parent(index)].key > m_Array[index].key )
    {
        swap(m_Array[parent(index)] , m_Array[index]);

        index = parent(index);
    }

    return true;
}

bool MinHeap::increaseKey(int index, double key)
{
    if( index < 0 && m_size >= index)
    {
        return false;
    }

    if(m_Array[index].key > key)
    {
        return false;
    }

    m_Array[index].key = key;

    heapify(index, m_size);

    return true;
}

void MinHeap::heapify(int i, int n)
{
    int l = left(i);

    int r = right(i);

    int smallest;

    if ( l < n && m_Array[l].key < m_Array[i].key)
    {
        smallest = l;
    }
    else
    {
        smallest = i;
    }

    if( r < n && m_Array[r].key < m_Array[smallest].key)
    {
        smallest = r;
    }

    if( smallest != i)
    {
        swap(m_Array[i],m_Array[smallest]);
    }
    else
    {
        return;
    }

    heapify(smallest,n);
}

int MinHeap::parent(int i)
{
    return (i-1)/2;
}

int MinHeap::left(int i)
{
    return (2*i+1);
}

int MinHeap::right(int i)
{
    return (2*i+2);
}

void MinHeap::swap(MinHeap::Node &a, MinHeap::Node &b)
{
    Node temp = a;

    a = b;

    b = temp;
}
