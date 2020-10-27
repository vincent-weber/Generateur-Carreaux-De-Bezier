#ifndef CARREAUBEZIER_H
#define CARREAUBEZIER_H

#include "surfaceparam.h"
#include "mathutil.h"

/**
 * @brief The CarreauBezier class
 * Cette classe permet de stocker les coordonnées des points de contrôle qui
 * serviront à discrétiser un carreau de Bézier.
 */
class CarreauBezier : public SurfaceParam
{

private:
    /**
     * @brief m : le nombre de points de contrôle sur un axe
     */
    int m;

    /**
     * @brief n : le nombre de points de contrôle sur l'autre axe
     */
    int n;

public:
    CarreauBezier();

    /**
     * @brief CarreauBezier Construit un object CarreauBezier à partir des points de contrôle
     * et de leur nombre par axe.
     * @param points_controle : les points de contrôle, organisés sous forme de matrice
     * @param m : le nombre de points de contrôle sur un axe
     * @param n : le nombre de points de contrôle sur l'autre axe
     */
    CarreauBezier (vector<vector<Point>> points_controle, int m, int n);


    /**
     * @brief eval : Fonction utilisée pour la discrétisation d'un carreau de Bézier
     * @param u : Le premier paramètre, entre 0 et 1
     * @param v : Le deuxième paramètre, entre 0 et 1
     * @return un point qui appartient au carreau de Bézier en fonction de u et de v
     */
    Point eval(float u, float v);
};

#endif // CARREAUBEZIER_H
