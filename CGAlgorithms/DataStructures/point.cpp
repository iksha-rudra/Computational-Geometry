#include "point.h"

Point::Point()
{
    m_x = 0;
    m_y = 0;
}

Point::Point(int x, int y)
{
    m_x = x;
    m_y = y;
}

int Point::x()
{
    return m_x;
}

int Point::y()
{
    return m_y;
}

void Point::setX(int x)
{
    m_x = x;
}

void Point::setY(int y)
{
    m_y = y;
}

