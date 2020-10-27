#ifndef DISCRETISATION_H
#define DISCRETISATION_H

#include <vector>
#include "point.h"
#include "segment.h"
#include "courbeparam.h"
#include "courbebezier.h"
#include "carreaubezier.h"


/**
 * @brief The Discretisation class : Permet de discrétiser différents éléments géométriques
 * à partir d'un objet de la classe correspondante et permet de définir la précision du rendu
 *
 */
class Discretisation
{
public:
    Discretisation();
    /**
     * @brief discretiser_segment : Permet de discrétiser un segment
     * @param param : l'objet Segment contenant le point de départ et d'arrivée
     * @param nb_points : définit le nombre de points à envoyer au rendu OpenGL
     * @return : la liste de points appartenant au segment à envoyer au rendu
     */
    Point* discretiser_segment(Segment param, int nb_points);

    /**
     * @brief discretiser_courbe_bezier : Permet de discrétiser une courbe de Bézier
     * @param cBezier : l'objet CourbeBezier contenant les points de contrôle
     * @param nb_points : définit le nombre de points à envoyer au rendu OpenGL
     * @return : la liste de points appartenant à la courbe de Bézier à envoyer au rendu
     */
    vector<Point> discretiser_courbe_bezier(courbeBezier& cBezier, int nb_points);

    /**
     * @brief discretiser_carreau_bezier : Permet de discrétiser un carreau de Bézier
     * @param carreau : l'objet CarreauBezier contenant la matrice des points de contrôle
     * @param nb_u : définit la qualité du rendu sur le premier axe (nb_u*nb_v = nombre de points à envoyer au rendu OpenGL)
     * @param nb_v : définit la qualité du rendu sur le deuxième axe (nb_u*nb_v = nombre de points à envoyer au rendu OpenGL)
     * @return : la liste de points appartenant au carreau de Bézier à envoyer au rendu
     */
    vector<Point> discretiser_carreau_bezier(CarreauBezier& carreau, int nb_u, int nb_v);
};

#endif // DISCRETISATION_H
