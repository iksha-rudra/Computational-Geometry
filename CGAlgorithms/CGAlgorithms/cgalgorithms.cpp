#include "cgalgorithms.h"
#include <bits/stdc++.h>
#include "DataStructures/minheap.h"
#include "DataStructures/linkedstack.h"
#include "math.h"

#define M_PI 3.14159265358979323846

CGAlgorithms::CGAlgorithms()
{

}

bool CGAlgorithms::SegmentsIntersect(Point p1,
                             Point p2,
                             Point p3,
                             Point p4)
{
    int d1 = _direction(p3,p4,p1);
    int d2 = _direction(p3,p4,p2);
    int d3 = _direction(p1,p2,p3);
    int d4 = _direction(p1,p2,p4);

    if( ( d1>0 && d2<0 ) ||
        ( d1<0 && d2>0 ) ||
        ( d3>0 && d4<0 ) ||
        ( d3<0 && d4>0 ) )
    {
        return true;
    }
    else if( !d1 && _onSegment(p3,p4,p1) )
    {
        return true;
    }
    else if( !d2 && _onSegment(p3,p4,p2) )
    {
        return true;
    }
    else if( !d3 && _onSegment(p1,p2,p3) )
    {
        return true;
    }
    else if( !d4 && _onSegment(p1,p2,p4) )
    {
        return true;
    }
    else
    {
        return false;
    }
}

CGAlgorithms::PointList CGAlgorithms::grahamScanCH(PointList points)
{
    PointList conveHullList;

    MinHeap H;

    LinkedStack S;

    Point p0 = _findMinY(points);

    _removePointFromList(points,p0);

    for(unsigned i=0; i<points.size(); i++)
    {
        double polarAngle = _polarAngle(p0,points.at(i));

        H.insert(points.at(i),polarAngle, p0);
    }

    S.push(p0);
    S.push(H.extractMin());
    S.push(H.extractMin());

    while( !H.isEmpty() )
    {
        Point p3 = H.extractMin();

        while( !S.isEmpty() )
        {
            Point p2 = S.top();
            Point p1 = S.nextToTop();

            if( _direction(p1,p2,p3) > 0 )
            {
                S.pop();
            }
            else
            {
                S.push(p3);
                break;
            }
        }
    }

    while( !S.isEmpty() )
    {
        conveHullList.push_back(S.pop());
    }

    return conveHullList;
}

CGAlgorithms::PointList CGAlgorithms::_quickHull(PointList points,
                                                 Point p1,
                                                 Point p2)
{
    if( points.empty() )
    {
        PointList hullList;

        hullList.push_back(p1);

//        hullList.push_back(p2);

        return hullList;
    }

    int maxArea = INT_MIN;

    int area;

    Point p3;

    Point pSelect;

    PointList leftPoints;

    PointList rightPoints;

    PointList hullList;

    PointList leftHullList;

    PointList rightHullList;

    for(unsigned i=0; i < points.size(); i++)
    {
        pSelect = points.at(i);

        area = _area(p1,p2,pSelect);

        if( area > maxArea )
        {
            maxArea = area;

            p3 = pSelect;
        }
        else if( area == maxArea)
        {

        }
    }

    for(unsigned i=0; i < points.size(); i++)
    {
        pSelect = points.at(i);

        area = _area(p1,p3,pSelect);

        if( area > 0 )
        {
            leftPoints.push_back(pSelect);
        }
    }

    for(unsigned i=0; i < points.size(); i++)
    {
        pSelect = points.at(i);

        area = _area(p3,p2,pSelect);

        if( area > 0 )
        {
            rightPoints.push_back(pSelect);
        }
    }

    leftHullList = _quickHull(leftPoints,p1,p3);

    rightHullList = _quickHull(rightPoints,p3,p2);

    for(unsigned i=0; i<leftHullList.size();i++)
    {
        hullList.push_back(leftHullList.at(i));
    }

    for(unsigned i=0; i<rightHullList.size();i++)
    {
        hullList.push_back(rightHullList.at(i));
    }

    return hullList;
}

CGAlgorithms::PointList CGAlgorithms::quickHull(PointList points)
{
    Point p1;

    Point p11;

    Point p2;

    Point p22;

    Point p3;

    PointList hullList;

    PointList leftHullList;

    PointList rightHullList;

    _findMinX(points,p1,p11);

    _findMaxX(points,p2,p22);

    PointList leftPoints;

    PointList rightPoints;

    int area;

    for(unsigned i=0; i < points.size(); i++)
    {
        p3 = points.at(i);

        area = _area(p1,p2,p3);

        if( area > 0 )
        {
            leftPoints.push_back(p3);
        }
        else if( area < 0 )
        {
            rightPoints.push_back(p3);
        }
    }

    leftHullList = _quickHull(leftPoints,p11,p22);

    rightHullList = _quickHull(rightPoints,p2,p1);

    for(unsigned i=0; i<leftHullList.size();i++)
    {
        hullList.push_back(leftHullList.at(i));
    }

    for(unsigned i=0; i<rightHullList.size();i++)
    {
        hullList.push_back(rightHullList.at(i));
    }

    return hullList;
}

int CGAlgorithms::_direction(Point pi,
                     Point pj,
                     Point pk)
{
    /* (pk - pi)(pj - pi)
    *  (p1 - p0)(p2 - p0) =  (x1 - x0)(y2 - y0) - (x2 - x0)(y1 - y0)
    */
    return (pk.x() - pi.x())*(pj.y() - pi.y()) - (pj.x() - pi.x())*(pk.y() - pi.y());
}

int CGAlgorithms::_area(Point p1, Point p2, Point p3)
{
    /*
     *  | x1 x2 x3 |
     *  | y1 y2 y3 |
     *  |  1  1  1 |
     *
     *  is +ve means p3 is left of p1-p2
     */
    return (p1.x()*(p2.y()-p3.y())+p2.x()*(p3.y()-p1.y())+p3.x()*(p1.y()-p2.y()));
}

bool CGAlgorithms::_onSegment(Point pi,
                      Point pj,
                      Point pk)
{
    if( (( _min(pi.x(),pj.x()) <= pk.x() ) &&
         ( _max(pi.x(),pj.x()) >= pk.x() )) &&
        (( _min(pi.y(),pj.y()) <= pk.y() ) &&
         ( _max(pi.y(),pj.y()) >= pk.y() )) )
    {
        return true;
    }
    else
    {
        return false;
    }
}

int CGAlgorithms::_min(int a, int b)
{
    return (a<b)?a:b;
}

int CGAlgorithms::_max(int a, int b)
{
    return (a>b)?a:b;
}

Point CGAlgorithms::_findMinY(PointList points)
{
    Point p0(INT_MAX,INT_MAX);

    for(unsigned i=0; i < points.size(); i++)
    {
        if( points.at(i).y() < p0.y() )
        {
            p0.setY(points.at(i).y());
            p0.setX(points.at(i).x());
        }
        else if(points.at(i).y() == p0.y() )
        {
            if( points.at(i).x() < p0.x() )
            {
               p0.setX(points.at(i).x());
            }
        }
    }

    return p0;
}

bool CGAlgorithms::_findMinX(PointList points,
                              Point& p1, Point& p11)
{
    bool twoPoints = false;

    p1.setX(INT_MAX);
    p1.setY(INT_MAX);

    p11.setX(INT_MIN);
    p11.setY(INT_MIN);

    for(unsigned i=0; i < points.size(); i++)
    {
        if( points.at(i).x() < p1.x() )
        {
            p1.setY(points.at(i).y());

            p1.setX(points.at(i).x());

            p11 = p1;

            twoPoints = false;
        }
        else if(points.at(i).x() == p1.x() )
        {
            twoPoints = true;

            if( points.at(i).y() < p1.y() )
            {
               p1.setY(points.at(i).y());
            }
            else if ( points.at(i).y() > p11.y() )
            {
               p11.setY(points.at(i).y());
            }
        }
    }

    return twoPoints;
}

bool CGAlgorithms::_findMaxX(PointList points,
                             Point &p2, Point &p22)
{
    bool twoPoints = false;

    p2.setX(INT_MIN);
    p2.setY(INT_MIN);

    p22.setX(INT_MIN);
    p22.setY(INT_MIN);

    for(unsigned i=0; i < points.size(); i++)
    {
        if( points.at(i).x() > p2.x() )
        {
            p2.setY(points.at(i).y());

            p2.setX(points.at(i).x());

            p22 = p2;

            twoPoints = false;
        }
        else if(points.at(i).x() == p2.x() )
        {
            twoPoints = true;

            if( points.at(i).y() < p2.y() )
            {
               p2.setY(points.at(i).y());
            }
            else if ( points.at(i).y() > p22.y() )
            {
               p22.setY(points.at(i).y());
            }
        }
    }

    return twoPoints;
}

void CGAlgorithms::_removePointFromList(PointList &points, Point point)
{
    for(unsigned i=0; i< points.size(); i++)
    {
        if( ( points.at(i).x() == point.x() ) &&
            ( points.at(i).y() == point.y() ) )
        {
            points.erase(points.begin()+i);
        }
    }
}

double CGAlgorithms::_polarAngle(Point source, Point target)
{
    int deltaX = target.x() - source.x();
    int deltaY = target.y() - source.y();

    return (180.0/M_PI)*atan2(deltaY,deltaX);
}

