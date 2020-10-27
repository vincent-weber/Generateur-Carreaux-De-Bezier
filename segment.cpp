#include <cmath>

#include "segment.h"

Segment::Segment()
{
	pointList = new Point[2];
}

Segment::~Segment()
{
	delete [] pointList;
	pointList = nullptr;
}

Segment::Segment(const Segment & s)
{
	pointList = new Point[2];

	for (unsigned i=0; i<2; ++i)
		pointList[i] = s.pointList[i];

}

void Segment::setStart(const Point & p)
{
	pointList[0] = p;
}

void Segment::setEnd(const Point & p)
{
	pointList[1] = p;
}

void Segment::setN(unsigned r, const Point & p)
{
	if (r>1)
		r=1;
	pointList[r] = p;
}

Point Segment::getN(unsigned r) const
{
	if (r>1)
		r=1;

	return pointList[r];
}

Point Segment::getStart() const
{
	return getN(0);
}


Point Segment::getEnd() const
{
	return getN(1);
}

float Segment::length() const
{
	float res=0.0f;

	for (unsigned i=0; i<3; ++i)
		res += pow((pointList[1]).getN(i) - (pointList[0]).getN(i), 2.0f);

	return sqrt(res);
}

Segment& Segment::operator= (const Segment &s)
{
	for (unsigned i=0; i<2; ++i)
		pointList[i] = s.pointList[i];

return *this;
}

std::ostream& operator<<(std::ostream& out, const Segment& s)
{
	return out << s.pointList[0] << " -- " << s.pointList[1];
}

Point Segment:: eval(float t) {
    float diviseur = 1.0f / t;
    float x = (this->getEnd().getX() - this->getStart().getX()) / diviseur;
    float y = (this->getEnd().getY() - this->getStart().getY()) / diviseur;
    float z = (this->getEnd().getZ() - this->getStart().getZ()) / diviseur;
    Point pointEval;
    pointEval.setX(x);
    pointEval.setY(y);
    pointEval.setZ(z);
    return pointEval;
}
