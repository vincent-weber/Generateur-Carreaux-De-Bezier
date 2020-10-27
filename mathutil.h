#ifndef MATHUTIL_H
#define MATHUTIL_H

/**
 * @brief calc_factoriel Calcule la valeur de factorielle d'un certain entier
 * @param n : l'entier pour lequel calculer la factorielle
 * @return  : la factorielle de n
 */
int calc_factoriel(int n);

/**
 * @brief poly_Berstein calcule la valeur du polynôme de Bernstein en fonction des 3 paramètres
 * @param n : 1er paramètre
 * @param i : 2e paramètre
 * @param t : 3e paramètre
 * @return : la valeur du polynôme de Bernstein en fonction des 3 paramètres
 */
float poly_Berstein(int n, int i, float t);

#endif // MATHUTIL_H
