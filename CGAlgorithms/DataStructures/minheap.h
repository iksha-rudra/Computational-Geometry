#ifndef HEAP_H
#define HEAP_H

#include <vector>
#include "point.h"

using namespace std;

class MinHeap
{

public:
    MinHeap();

    struct Node
    {
        Point info;

        double key;

        Node(Point info, int key):
            info(info),key(key)
        {

        }
    };

    bool extractMin(Point& info, double& key);

    Point extractMin();

    bool checkMin(Point& info, double& key);

    void insert(Point info, double key);

    void insert(Point info,
                double key,
                Point refPoint);

    bool isEmpty();

protected:

    vector<Node> m_Array;

    int m_size;

    bool decreaseKey(int index, double key);

    bool increaseKey(int index, double key);

    void heapify(int i, int n);

    int parent(int i);

    int left(int i);

    int right(int i);

    void swap(Node &a, Node &b);
};

#endif // HEAP_H
