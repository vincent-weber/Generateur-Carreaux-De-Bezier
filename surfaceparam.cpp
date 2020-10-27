#include <QDebug>
#include "surfaceparam.h"

SurfaceParam::SurfaceParam()
{

}


SurfaceParam::~SurfaceParam()
{
     pointList.clear();
}

SurfaceParam::SurfaceParam(vector<vector<Point>> list)
{
    set_pointList(list);
}

vector<vector<Point>> SurfaceParam::get_pointList()
{
    return pointList;
}

void SurfaceParam::set_pointList(vector<vector<Point>> list)
{
    pointList = list;
}
