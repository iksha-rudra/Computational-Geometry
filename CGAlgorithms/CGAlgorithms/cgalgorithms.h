#ifndef CGAL_H
#define CGAL_H

#include <vector>
#include <DataStructures/point.h>

class CGAlgorithms
{
public:
    CGAlgorithms();

    typedef std::vector<Point> PointList;

    static bool SegmentsIntersect(Point p1,
                                  Point p2,
                                  Point p3,
                                  Point p4);

    static PointList grahamScanCH(PointList points);

    static int _direction(Point pi, Point pj, Point pk);

    static int _direction2(Point p1, Point p2, Point p3);

private:



    static bool _onSegment(Point pi, Point pj, Point pk);

    static int _min(int a, int b);

    static int _max(int a, int b);

    static Point _findMinY(PointList points);

    static void _removePointFromList(PointList& points,
                      Point point);

    static double _polarAngle(Point source, Point target);
};

#endif // CGAL_H
