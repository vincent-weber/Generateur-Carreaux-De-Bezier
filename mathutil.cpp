#include "mathutil.h"

#include <cmath>

int calc_factoriel(int n)
{
    int result=1;
    if(n==0) return 1;

    for (int i=1; i<=n; i++)
    {
       result*=i;
    }
    return result;
}

float poly_Berstein(int n, int i, float t)
{

    float a = float(calc_factoriel(n));
    float b = (float(calc_factoriel(i)) * calc_factoriel(n-i));
    a = a / b;
    float c = pow(t, i) * pow(1-t, n-i);

    float result = a * c;
    return result;
}
