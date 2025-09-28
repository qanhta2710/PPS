#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <math.h>
#include "utils.h"
#define eps 1e-10

int readInputFromFile(const char *filename, double **x, double **y, int *m) {
    *x = NULL, *y = NULL;
    FILE *f = fopen(filename, "r");
    if (f == NULL) {
        printf("Khong the mo file %s\n", filename);
        printLog("Khong the mo file %s\n", filename);
        return -1;
    }
    if (fscanf(f, "%d", m) != 1 || *m <= 0) {
        printf("So diem noi suy khong hop le\n");
        printLog("So diem noi suy khong hop le\n");
        fclose(f);
        return -1;
    }
    int count = 0;
    double *tmp_x = (double *)malloc((*m) * sizeof(double));
    double *tmp_y = (double *)malloc((*m) * sizeof(double));
    for (int i = 0; i < *m; i++) {
        int res = fscanf(f, "%lf%lf", &tmp_x[i], &tmp_y[i]);
        if (res != 2) {
            printf("So diem noi suy khai bao khong khop hoac ton tai nut noi suy co du lieu khong hop le. Vui long kiem tra lai input \n");
            printLog("So diem noi suy khai bao khong khop hoac ton tai nut noi suy co du lieu khong hop le. Vui long kiem tra lai input \n");
            free(tmp_x);
            free(tmp_y);
            *m = 0;
            fclose(f);
            return -1;
        }
        count++;
    }
    double dummy_x, dummy_y;
    if (fscanf(f, "%lf%lf", &dummy_x, &dummy_y) == 2) {
        printf("So diem noi suy khai bao khong khop, file co nhieu hon %d diem\n", *m);
        printLog("So diem noi suy khai bao khong khop, file co nhieu hon %d diem\n", *m);
        free(tmp_x);
        free(tmp_y);
        fclose(f);
        return -1;
    }
    fclose(f);
    int *seen = (int *)calloc(*m, sizeof(int));
    int uq_count = 0;
    for (int i = 0; i < *m; i++) {
        if (!seen[i]) {
            seen[i] = 1;
            uq_count++;
            for (int j = i + 1; j < *m; j++) {
                if (!seen[j] && fabs(tmp_x[i] - tmp_x[j]) < eps) {
                    seen[j] = -1;
                }
            }
        }
    }
    int dup_count = *m - uq_count;
    if (dup_count > 0) {
        printf("Phat hien co diem x trung nhau\n");
        printLog("Phat hien co diem x trung nhau\n");
        printf("Chuong trinh se tu dong lay diem dau tien va loai bo cac diem trung nhau con lai\n");
        printLog("Chuong trinh se tu dong lay diem dau tien va loai bo cac diem trung nhau con lai\n");
    }
    *x = (double *)malloc(uq_count * sizeof(double));
    *y = (double *)malloc(uq_count * sizeof(double));
    int idx = 0;
    for (int i = 0; i < *m; i++) {
        if (seen[i] != -1) {
            (*x)[idx] = tmp_x[i];
            (*y)[idx] = tmp_y[i];
            idx++;
        }
    }
    *m = uq_count;
    free(tmp_x);
    free(tmp_y);
    free(seen);
    return 0;
}

void printLog(const char *format, ...) {
    FILE *log = fopen("log.txt", "a");
    if (!log) {
        printf("Khong the mo file log");
        return;
    }

    va_list args;
    va_start(args, format);
    vfprintf(log, format, args);
    va_end(args);

    fclose(log);
}