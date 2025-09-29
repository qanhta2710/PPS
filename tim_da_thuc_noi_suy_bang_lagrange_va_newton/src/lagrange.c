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
                printf("L_%d(x) = ", i);
        printLog("L_%d(x) = ", i);
        int first_L = 1;
        for (int j = n; j >= 0; j--) {
            if (coeffsL_i[j] != 0) {
                if (!first_L && coeffsL_i[j] > 0) {
                    printf(" + ");
                    printLog(" + ");
                } else if (coeffsL_i[j] < 0) {
                    printf(" - ");
                    printLog(" - ");
                } else if (!first_L) {
                    printf(" + ");
                    printLog(" + ");
                }


                printf("%.*lf", precision, fabs(coeffsL_i[j]));
                printLog("%.*lf", precision, fabs(coeffsL_i[j]));

                if (j > 0) {
                    printf("x");
                    printLog("x");
                }
                if (j > 1) {
                    printf("^%d", j);
                    printLog("^%d", j);
                }
                first_L = 0;
            }
        }
        printf("\n");
        printLog("\n");
        printf("Thanh phan y_%d*L_%d(x) = ", i, i);
        printLog("Thanh phan y_%d*L_%d(x) = ", i, i);
        int first_yL = 1;
        for (int j = n; j >= 0; j--) {
            double current_coeff = y[i] * coeffsL_i[j];
            if (current_coeff != 0) {
                 if (!first_yL && current_coeff > 0) {
                    printf(" + ");
                    printLog(" + ");
                } else if (current_coeff < 0) {
                    printf(" - ");
                    printLog(" - ");
                }

                printf("%.*lf", precision, fabs(current_coeff));
                printLog("%.*lf", precision, fabs(current_coeff));

                if (j > 0) printf("x");
                if (j > 1) printf("^%d", j);
                printLog(j > 0 ? "x" : "");
                if (j > 1) printLog("^%d", j);

                first_yL = 0;
            }
        }
        printf("\n\n");
        printLog("\n\n");
        tinhTungThanhPhanCuaPx(coeffsP, coeffsL_i, n, y[i]);
        free(coeffsL_i);
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