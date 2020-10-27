#include "carreaubezier.h"
#include <QDebug>

CarreauBezier::CarreauBezier()
{

}

CarreauBezier::CarreauBezier(vector<vector<Point>> listPoints, int n, int m) {
    set_pointList(listPoints);
    this->m = m;
    this->n = n;
}

Point CarreauBezier::eval(float u, float v) {

    if (u < 0) u = 0;
    if (u > 1) u = 1;
    if (v < 0) v = 0;
    if (v > 1) v = 1;

    vector<vector<Point>> points = get_pointList();

    Point P;
    float xP = 0.0f, yP = 0.0f, zP = 0.0f;
    for (int i = 0 ; i < n ; ++i) {
        for (int j = 0 ; j < m ; ++j) {
            float bernstein1 = poly_Berstein(n-1,i,u);
            float bernstein2 = poly_Berstein(m-1,j,v);
            xP += bernstein1 * bernstein2 * points[i][j].getX();
            yP += bernstein1 * bernstein2 * points[i][j].getY();
            zP += bernstein1 * bernstein2 * points[i][j].getZ();
        }
    }
    P.setX(xP);
    P.setY(yP);
    P.setZ(zP);

    return P;
}
