#ifndef SURFACEPARAM_H
#define SURFACEPARAM_H

#include "point.h"
#include <vector>

using namespace std;

/**
 * @brief The SurfaceParam class : Classe qui définit les éléments génériques à toutes
 * surfaces paramétriques, notamment les carreaux de Bézier.
 */
class SurfaceParam
{
private:

    /**
    * @brief pointList : la matrice des points de contrôle de la surface.
    */
   vector<vector<Point>> pointList;

public:

    SurfaceParam();
    ~SurfaceParam();
    /**
     * @brief SurfaceParam
     * @param pointList : la matrice des points de contrôle de la surface.
     */
    SurfaceParam(vector<vector<Point>> pointList);
    vector<vector<Point>> get_pointList();
    void set_pointList(vector<vector<Point>> list);
};

#endif // SURFACEPARAM_H
