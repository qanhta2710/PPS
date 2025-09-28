#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "utils.h"
#include "newton.h"
#include "horner.h"
// n là bậc của đa thức

double **bangTySaiPhan(double *x, double *y, int n, int precision, const char *output) {
    double **table = (double **)malloc((n + 1) * sizeof(double*));
    for (int i = 0; i <= n; i++) {
        table[i] = (double *)calloc(n + 1, sizeof(double));
    }
    for (int i = 0; i <= n; i++) {
        table[i][0] = y[i];
    }
    for (int j = 1; j <= n; j++) {
        for (int i = 0; i <= n - j; i++) {
            table[i][j] = (table[i + 1][j - 1] - table[i][j - 1]) / (x[i + j] - x[i]);
        }
    }
    printf("\nBang ty sai phan: \n");
    printLog("\nBang ty sai phan: \n");
    printf("\n%-10s%-15s", "x", "y");
    printLog("\n%-10s%-15s", "x", "y");
    for (int j = 1; j <= n; j++) {
        printf("TSP%-12d", j);
        printLog("TSP%-12d", j);
    }
    printf("\n----------------------------------------------------------------\n");
    printLog("\n----------------------------------------------------------------\n");
    for (int i = 0; i <= n; i++) {
        printf("%-10g%-15g", x[i], table[i][0]);
        printLog("%-10g%-15g", x[i], table[i][0]);
        for (int j = 1; j <= n; j++) {
            if (j <= n - i) {
                printf("%-15g", table[i][j]);
                printLog("%-15g", table[i][j]);
            } else {
                printf("%-15s", "");
                printLog("%-15s", "");
            }
        }
        printf("\n");
        printLog("\n");
    }

    if (output != NULL) {
        FILE *f = fopen(output, "w");
        if (f == NULL) {
            fprintf(stderr, "Khong the mo file %s\n", output);
            return table;
        }
        fprintf(f, "Bang ty sai phan: \n");
        fprintf(f, "\n%-10s%-15s", "x", "y");
        for (int j = 1; j <= n; j++) {
            fprintf(f, "TSP%-12d", j);
        }
        fprintf(f, "\n----------------------------------------------------------------\n");
        for (int i = 0; i <= n; i++) {
            fprintf(f, "%-10g%-15g", x[i], table[i][0]);
            for (int j = 1; j <= n - i; j++) {
                if (j <= n - i) {
                    fprintf(f, "%-15g", table[i][j]);
                } else {
                    fprintf(f, "%-15s", "");
                }
            }
            fprintf(f, "\n");
        }
        fclose(f);
    }
    return table;
}

void inDaThucNewtonTien(double *x, double *y, double **table, int n, int precision, double *coeffs) {
    double *tmp = (double *)calloc(n + 1, sizeof(double));
    double *new_tmp = (double *)calloc(n + 1, sizeof(double));
    printf("Da thuc noi suy Newton dang tien: ");
    printLog("Da thuc noi suy Newton dang tien: ");
    printf("f(x) = %.*lf + ", precision, table[0][0]);
    printLog("f(x) = %.*lf + ", precision, table[0][0]);
    for (int i = 1; i <= n; i++) {
        printf("%.*lf", precision, table[0][i]);
        printLog("%.*lf", precision, table[0][i]);
        for (int j = 0; j < i; j++) {
            printf("(x - %.*lf)", precision, x[j]);
            printLog("(x - %.*lf)", precision, x[j]);
        }
        if (i < n) {
            printf(" + ");
            printLog(" + ");
        }
    }
    tmp[0] = 1;
    for (int j = 0; j <= n; j++) {
        double fj = table[0][j];
        for (int k = 0; k <= j; k++) {
            coeffs[k] += fj * tmp[k];
        }
        if (j < n) {
            nhanDaThucBangHorner(new_tmp, tmp, j, x[j]);
            for (int k = 0; k <= j + 1; k++) {
                tmp[k] = new_tmp[k];
            }
        }
    }
    printf("\n");
    printLog("\n");
    printf("Da thuc dang chuan tac: ");
    printLog("Da thuc dang chuan tac: ");
    int first = 1;
    for (int i = n; i >= 0; i--) {
        if (coeffs[i] != 0) {
            if (!first && coeffs[i] > 0) {
                printf(" + ");
                printLog(" + ");
            }
            if (coeffs[i] < 0) {
                printf(" - ");
                printLog(" - ");
            }
            printf("%.*lf", precision, fabs(coeffs[i]));
            printLog("%.*lf", precision, fabs(coeffs[i]));
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
    free(tmp);
    free(new_tmp);
}

void inDaThucNewtonLui(double *x, double *y, double **table, int n, int precision, double *coeffs) {
    double *tmp = (double *)calloc(n + 1, sizeof(double));
    double *new_tmp = (double *)calloc(n + 1, sizeof(double));
    printf("Da thuc noi suy Newton dang lui: ");
    printLog("Da thuc noi suy Newton dang lui: ");
    printf("f(x) = %.*lf + ", precision, table[n][0]);
    printLog("f(x) = %.*lf + ", precision, table[n][0]);
    for (int i = 1; i <= n; i++) {
        printf("%.*lf", precision, table[n - i][i]);
        printLog("%.*lf", precision, table[n - i][i]);
        for (int j = n; j > n - i; j--) {
            printf("(x - %.*lf)", precision, x[j]);
            printLog("(x - %.*lf)", precision, x[j]);
        }
        if (i < n) {
            printf(" + ");
            printLog(" + ");
        }
    }
    printf("\n");
    printLog("\n");
    tmp[0] = 1;
    for (int j = 0; j <= n; j++) {
        double fj = table[n - j][j];
        for (int k = 0; k <= n; k++) {
            coeffs[k] += fj * tmp[k];
        }
        if (j < n) {
            nhanDaThucBangHorner(new_tmp, tmp, j, x[n - j]);
            for (int k = 0; k <= j + 1; k++) {
                tmp[k] = new_tmp[k];
            }
        }
    }
    printf("Da thuc dang chuan tac: ");
    printLog("Da thuc dang chuan tac: ");
    int first = 1;
    for (int i = n; i >= 0; i--) {
        if (coeffs[i] != 0) {
            if (!first && coeffs[i] > 0) {
                printf(" + ");
                printLog(" + ");
            }
            if (coeffs[i] < 0) {
                printf(" - ");
                printLog(" - ");
            }
            printf("%.*lf", precision, fabs(coeffs[i]));
            printLog("%.*lf", precision, fabs(coeffs[i]));
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
    free(tmp);
    free(new_tmp);
}