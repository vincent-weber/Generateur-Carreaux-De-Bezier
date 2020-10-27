#include <QDebug>
#include "courbeparam.h"

CourbeParam::CourbeParam()
{

}


CourbeParam::~CourbeParam()
{
     pointList.clear();
}

CourbeParam::CourbeParam(vector<Point> list)
{
    set_pointList(list);
}

vector<Point> CourbeParam::get_pointList()
{
    return pointList;
}

void CourbeParam::set_pointList(vector<Point> list)
{
    pointList.clear();
    for (unsigned i=0; i < list.size(); ++i)
    {
        add_point(list[i]);
    }
}

void CourbeParam::add_point(Point P)
{
    pointList.push_back(P);
}


