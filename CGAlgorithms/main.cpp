#include <iostream>
#include "CGAlgorithms/cgalgorithms.h"
#include <stdio.h>

using namespace std;

int main()
{
    CGAlgorithms::PointList list;

    list.push_back(Point(2, 4));
    list.push_back(Point(0, 3));
    list.push_back(Point(1, 1));
    list.push_back(Point(2, 2));
    list.push_back(Point(4, 4));

    list.push_back(Point(0, 0));
    list.push_back(Point(1, 2));
    list.push_back(Point(3, 1));
    list.push_back(Point(3, 3));
    list.push_back(Point(-1, 1));

    list.push_back(Point(2, 3));
    list.push_back(Point(-2, 2));

    printf("Graham Scan\n*****************\n");

    CGAlgorithms::PointList hull = CGAlgorithms::grahamScanCH(list);

    for( unsigned i=0; i < hull.size(); i++)
    {
        printf("(%d,%d)\n", hull.at(i).x(), hull.at(i).y() );
    }

    printf("Quick Hull\n*****************\n");

    hull.clear();

    hull = CGAlgorithms::quickHull(list);

    for( unsigned i=0; i < hull.size(); i++)
    {
        printf("(%d,%d)\n", hull.at(i).x(), hull.at(i).y() );
    }

    return 0;
}

