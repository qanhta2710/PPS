#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <horner.h>
#include "lagrange.h"
#include "utils.h"
// n là bậc đa thức
static double tinhMauSoL_ix(double *poly, int deg, double x0) {
    double res = poly[deg];
    for (int k = deg - 1; k >= 0; k--) {
        res = res * x0 + poly[k]; 
    }
    return res;
}
static void tinhHeSoL_ix(double *coeffs, double *x, int i, int n) {
    int deg = 0;
    double *current = (double *)calloc(n + 1, sizeof(double));
    current[0] = 1;
    double *res = (double *)calloc(n + 2, sizeof(double));
    for (int j = 0; j <= n; j++) {
        if (j != i) {
            nhanDaThucBangHorner(res, current, j, x[j]);
            deg++;
            for (int k = 0; k <= n; k++) {
                current[k] = res[k];
                res[k] = 0;
            }
        }
    }
    double denominator = tinhMauSoL_ix(current, deg, x[i]);
    for (int k = 0; k <= deg; k++) {
        coeffs[k] = current[k] / denominator;
    }
    free(current);
    free(res);
}

static void tinhTungThanhPhanCuaPx(double *dest, double *src, int deg, double y) {
    for (int i = 0; i <= deg; i++) {
        dest[i] += src[i] * y;
    }
}

void inDaThucLagrange(double *x, double *y, int n, int precision, double *coeffsP) {
    for (int i = 0; i <= n; i++) {
        double *coeffsL_i = (double *)calloc(n + 1, sizeof(double));
        tinhHeSoL_ix(coeffsL_i, x, i, n);
        tinhTungThanhPhanCuaPx(coeffsP, coeffsL_i, n, y[i]);
        free(coeffsL_i);
    }
    printf("Cong thuc da thuc noi suy Lagrange:\n");
    printLog("Cong thuc da thuc noi suy Lagrange:\n");
    for (int i = 0; i <= n; i++) {
        printf("L_%d(x) = %.*lf * ", i, precision, y[i]);
        printLog("L_%d(x) = %.*lf * ", i, precision, y[i]);
        for (int j = 0; j <= n; j++) {
            if (j != i) {
                printf("(x - %.*lf)", precision, x[j]);
                printLog("(x - %.*lf)", precision, x[j]);
            }
        }
        printf("/");
        printLog("/");
        for (int j = 0; j <= n; j++) {
            if (j != i) {
                printf("(%.*lf - %.*lf)", precision, x[i], precision, x[j]);
                printLog("(%.*lf - %.*lf)", precision, x[i], precision, x[j]);
            }
        }
        printf("\n");
        printLog("\n");
    }
    printf("P(x) = ");
    printLog("P(x) = ");
    for (int i = 0; i <= n; i++) {
        printf("L_%d(x) ", i);
        printLog("L_%d(x) ", i);
        if (i < n) {
            printf("+ ");
            printLog("+ ");
        }
    }
    printf("\n");
    printLog("\n");
    printf("Da thuc chuan tac: ");
    printLog("Da thuc chuan tac: ");
    int first = 1;
    for (int i = n; i >= 0; i--) {
        if (coeffsP[i] != 0) {
            if (!first && coeffsP[i] > 0) {
                printf(" + ");
                printLog(" + ");
            }
            if (coeffsP[i] < 0) {
                printf(" - ");
                printLog(" - ");
            }
            printf("%.*lf", precision, fabs(coeffsP[i]));
            printLog("%.*lf", precision, fabs(coeffsP[i]));
            if (i > 0) {
                printf("x");
                printLog("x");
            }
            if (i > 1) {
                printf("^%d", i);
                printLog("^%d", i);
            }
            first = 0;
        }
    }
    printf("\n");
    printLog("\n");
}