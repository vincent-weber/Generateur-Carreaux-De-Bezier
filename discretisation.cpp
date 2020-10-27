#include "discretisation.h"
#include <QDebug>

Discretisation::Discretisation()
{

}

Point* Discretisation::discretiser_segment(Segment param, int nb_points) {
    Point* points = new Point[nb_points];
    for (int i = 0 ; i < nb_points ; ++i) {
        points[i] = param.eval((float)i / nb_points);
    }
    return points;
}

vector<Point>Discretisation:: discretiser_courbe_bezier(courbeBezier& cBezier, int nb_points)
{

    std::vector<Point> listPoints;
    float offset = 1.f / float(nb_points - 1);

    listPoints.push_back(cBezier.eval(0));
    float currentPosition = offset;
    for (int i = 0 ; i < nb_points - 2 ; ++i) {
        listPoints.push_back(cBezier.eval(currentPosition));
        currentPosition+=offset;
    }
    listPoints.push_back(cBezier.eval(1));

    return listPoints;
}

/**
 * @brief Discretisation::discretiser_carreau_bezier. Discrétise de force tous les points appartenant aux
 * extrémités du carreau de Bézier, c'est-à-dire quand u vaut 0 et 1 (1e et 3e boucles for)
 * puis tous les points à l'intérieur (2e boucle for)
 * @param carreau
 * @param nb_u
 * @param nb_v
 * @return
 */
vector<Point> Discretisation::discretiser_carreau_bezier(CarreauBezier& carreau, int nb_u, int nb_v) {
    std::vector<Point> listPoints;

    float offset_u = 1.0f / (nb_u-1);
    float offset_v = 1.0f / (nb_v-1);
    for (float v = 0, i = 0 ; i < nb_v ; v += offset_v, ++i) {
        listPoints.push_back(carreau.eval(0,v));
    }

    for (float u = offset_u, i = 0 ; i < nb_u-2 ; u += offset_u, ++i) {
        for (float v = 0, j = 0 ; j < nb_v ; v += offset_v, ++j) {
            listPoints.push_back(carreau.eval(u,v));
        }
    }

    for (float v = 0, i = 0 ; i < nb_v ; v += offset_v, ++i) {
        listPoints.push_back(carreau.eval(1,v));
    }
    return listPoints;

}
