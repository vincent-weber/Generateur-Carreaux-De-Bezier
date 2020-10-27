#ifndef COURBEPARAM_H
#define COURBEPARAM_H



#include "point.h"
#include <vector>

using namespace std;

class CourbeParam
{

private:

   vector<Point> pointList;

public:

    CourbeParam();
    ~CourbeParam();
    CourbeParam(vector<Point> pointList);
    vector<Point> get_pointList();
    void set_pointList(vector<Point> list);
    void add_point(Point P);
    Point eval(float t);



};

#endif // COURBEPARAM_H
