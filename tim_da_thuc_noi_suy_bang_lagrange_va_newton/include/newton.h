#ifndef NEWTON_H
#define NEWTON_H

double **bangTySaiPhan(double *x, double *y, int n, int precision, const char *output);
void inDaThucNewtonTien(double *x, double *y, double **table, int n, int precision, double *coeffs);
void inDaThucNewtonLui(double *x, double *y, double **table, int n, int precision, double *coeffs);

#endif