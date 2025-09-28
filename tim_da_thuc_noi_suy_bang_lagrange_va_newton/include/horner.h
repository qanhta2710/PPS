#ifndef HORNER_H
#define HORNER_H
#include <stdio.h>

void nhanDaThucBangHorner(double *res, double *poly, int deg, double c);
void tinhDaThucTaixBangHorner(double *poly, int deg, double x0, int precision);

#endif