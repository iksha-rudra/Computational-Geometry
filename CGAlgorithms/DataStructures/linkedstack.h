#ifndef LINKEDSTACK_H
#define LINKEDSTACK_H

#include "DataStructures/point.h"
#include <stdio.h>

class LinkedStack
{
public:
    LinkedStack();

    struct Node
    {
        Point data;

        struct Node *link;

        Node(Point d)
        {
            data = d;

            link = nullptr;
        }
    };

    void display();

    void push(Point item);

    Point pop();

    Point top();

    Point nextToTop();

    bool isEmpty();

    void displayReverse();

private:

    Node *m_head;

    void _print(LinkedStack::Node *temp);

    void _reversePrint(LinkedStack::Node *temp);
};

#endif // LINKEDSTACK_H
