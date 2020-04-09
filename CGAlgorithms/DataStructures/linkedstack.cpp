#include "linkedstack.h"
#include <stdio.h>

LinkedStack::LinkedStack():
    m_head(nullptr)
{

}

void LinkedStack::_print(LinkedStack::Node *temp)
{
    if( temp )
    {
        printf("%d-->",temp->data);

        _print(temp->link);
    }
}

void LinkedStack::_reversePrint(LinkedStack::Node *temp)
{
    if(temp)
    {
        _reversePrint(temp->link);

        printf("%d-->",temp->data);
    }
}

void LinkedStack::display()
{
    Node *temp = m_head;

    _print(temp);
}

void LinkedStack::displayReverse()
{
    Node *temp = m_head;

    _reversePrint(temp);
}

void LinkedStack::push(Point item)
{
    Node *newNode = new Node(item);

    newNode->link = m_head;

    m_head = newNode;
}

Point LinkedStack::pop()
{
    Point item(0,0);

    if( !m_head )
    {
        printf("Underflow\n");

        return item;
    }

    Node *temp = m_head;

    item = temp->data;

    m_head = m_head->link;

    delete temp;

    return item;
}

Point LinkedStack::top()
{
    Point item(0,0);

    if( !m_head )
    {
        printf("Underflow\n");
    }
    else
    {
        item = m_head->data;
    }

    return item;
}

Point LinkedStack::nextToTop()
{
    Point item(0,0);

    if( !m_head || !m_head->link )
    {
        printf("Underflow\n");
    }

    item = m_head->link->data;

    return item;
}

bool LinkedStack::isEmpty()
{
    bool empty = true;

    if( m_head )
    {
        empty = false;
    }

    return empty;
}
