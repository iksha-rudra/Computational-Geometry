#ifndef POINT_H
#define POINT_H


class Point
{
public:
    Point(int x, int y);
    Point();

    int x();
    int y();

    void setX(int x);
    void setY(int y);

private:
    int m_x;
    int m_y;
};

#endif // POINT_H
