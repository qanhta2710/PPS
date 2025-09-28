#include <stdio.h>
#include "horner.h"
#include "utils.h"
void nhanDaThucBangHorner(double *res, double *poly, int deg, double c) {
    res[deg + 1] = poly[deg];
    for (int k = deg; k >= 1; k--) {
        res[k] = poly[k - 1] - poly[k] * c;
    }
    res[0] = (-c) * poly[0];
}

void tinhDaThucTaixBangHorner(double *poly, int deg, double x0, int precision) {
    double res = poly[deg];
    printf("Buoc 1: f(x) = %.*lf\n", precision, res);
    printLog("Buoc 1: f(x) = %.*lf\n", precision, res);
    for (int k = deg - 1; k >= 0; k--) {
        printf("Buoc %d: f(x) = %.*lf * %.*lf + %.*lf\n", deg - k + 1, precision, res, precision, x0, precision, poly[k]);
        printLog("Buoc %d: f(x) = %.*lf * %.*lf + %.*lf\n", deg - k + 1, precision, res, precision, x0, precision, poly[k]);
        res = res * x0 + poly[k]; 
    }
    printf("f(%.*lf) = %.*lf", precision, x0, precision, res);
    printLog("f(%.*lf) = %.*lf", precision, x0, precision, res);
}


