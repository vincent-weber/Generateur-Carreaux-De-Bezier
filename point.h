/* R. Raffin
 * M1 Informatique, Aix-Marseille Université
 * définition d'une classe Point
 * l'utilisation du tableau de float pour les coordonnées est là pour ne pas trop avoir peur de C++
 * mais c'(est une mauvaise façon d'écrire, préférez les objets de std::, comme std::vector par exemple
 * Cet objet est d'ailleurs directement utilsable comme un float[]
 * Si on veut généraliser le Point, il peut être d'une quelconque dimension (i.e. un nombre quelconque de coordonnées)
 */

#ifndef POINT_H
#define POINT_H

#include <iostream>

class Point
{
private:
	float * coords;

public:
	Point();
	~Point();
	Point(const Point&);

	Point& operator= (const Point &);


	float getN(unsigned) const;
	float getX() const;
	float getY() const;
	float getZ() const ;
	void get(float *) const;

	void setN(unsigned, const float&);
	void setX(const float&);
	void setY(const float&);
	void setZ(const float&);
	void set(const float *);

	friend std::ostream& operator<<(std::ostream&, const Point&);
    Point operator *(Point p) {
        Point result;
        result.setX(this->getX() * p.getX());
        result.setY(this->getY() * p.getY());
        result.setZ(this->getZ() * p.getZ());
        return result;
    }
    Point operator *(float coef) {
        Point result;
        result.setX(this->getX() * coef);
        result.setY(this->getY() * coef);
        result.setZ(this->getZ() * coef);
        return result;
    }

};

#endif // POINT_H
