#ifndef COURBEBEZIER_H
#define COURBEBEZIER_H

#include <vector>
#include "courbeparam.h"
#include "point.h"
#include "mathutil.h"

using namespace std;

/**
 * @brief The courbeBezier class
 * Cette classe permet de stocker les coordonnées des points de contrôle qui
 * serviront à discrétiser une courbe de Bézier.
 */
class courbeBezier: public CourbeParam
{
public:
    courbeBezier();

    /**
     * @brief courbeBezier : permet d'instancier un objet CourbeBezier à partir
     * des points de contrôle souhaités et d'ensuite pouvoir le discrétiser
     * @param list
     */
    courbeBezier (vector<Point> list);


    /**
     * @brief eval : Fonction utilisée pour la discrétisation d'un carreau de Bézier
     * @param t : Le paramètre entre 0 et 1
     * @return : le point appartenant à la courbe correspondant au paramètre t
     */
    Point eval(float t);
};

#endif // COURBEBEZIER_H
