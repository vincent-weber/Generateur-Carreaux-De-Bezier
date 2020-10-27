#include <QDebug>
#include <iostream>

#include "courbebezier.h"
#include "courbeparam.h"

courbeBezier::courbeBezier()
{

}

courbeBezier::courbeBezier(vector<Point> list)
{
   set_pointList(list);

}


Point courbeBezier:: eval(float t)
{
    if (t<0 || t>1) {
          qDebug() << "Erreur dans  " << __FUNCTION__ << " t doit être entre 0 et 1 ";
          exit (1);
    }

    Point P;
    vector<Point> list = get_pointList();
    int degre = list.size()-1; // degré = nb pt de contrôle -1


    float xP=0.f, yP=0.f, zP=0.f; // coordonées du pt
    float berstein;
    for (int i=0; i<=degre; ++i)
    {
        berstein = poly_Berstein(degre, i, t);
        xP += berstein * list[i].getX();
        yP += berstein * list[i].getY();
        zP += /*berstein **/ list[i].getZ();
    }

    P.setX(xP);
    P.setY(yP);
    P.setZ(zP);

    return P;
}

