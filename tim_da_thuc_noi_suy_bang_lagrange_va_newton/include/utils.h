#ifndef UTILS_H
#define UTILS_H

#include <stdio.h>

int readInputFromFile(const char *filename, double **x, double **y, int *n);
void printLog(const char *format, ...);

#endif