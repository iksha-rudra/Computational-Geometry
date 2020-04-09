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

            if( _direction2(p1,p2,p3) > 0 )
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

int CGAlgorithms::_direction(Point pi,
                     Point pj,
                     Point pk)
{
    /* (pk - pi)(pj - pi)
    *  (p1 - p0)(p2 - p0) =  (x1 - x0)(y2 - y0) - (x2 - x0)(y1 - y0)
    */
    return (pk.x() - pi.x())*(pj.y() - pi.y()) - (pj.x() - pi.x())*(pk.y() - pi.y());
}

int CGAlgorithms::_direction2(Point p1, Point p2, Point p3)
{
    /*
     *  | x1 x2 x3 |
     *  | y1 y2 y3 |
     *  |  1  1  1 |
     *
     *  is +ve means p3 is left of p1-p2
     */
    return -(p1.x()*(p2.y()-p3.y())+p2.x()*(p3.y()-p1.y())+p3.x()*(p1.y()-p2.y()));
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

