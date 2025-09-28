#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include "menu.h"
#include <utils.h>
#include "lagrange.h"
#include "newton.h"
#include "horner.h"
#define MAX_OPTIONS 7
#define COLOR_RESET   "\x1b[0m"
#define BG_WHITE   "\x1b[47m"
#define FG_BLACK   "\x1b[30m"

void showMenu(int selected) {
    const char *options[MAX_OPTIONS] = {
        "Doc File du lieu", 
        "Tao bang ty sai phan",
        "Tim da thuc noi suy theo cong thuc Lagrange", 
        "Tim da thuc noi suy theo cong thuc Newton tien",
        "Tim da thuc noi suy theo cong thuc Newton lui", 
        "Tinh gia tri da thuc tai 1 diem",  
        "Thoat"};
    system("cls"); 
    printf("=== MENU ===\n");
    for (int i = 0; i < MAX_OPTIONS; i++) {
        if (i == selected) {
            printf(BG_WHITE FG_BLACK "  %s  " COLOR_RESET "\n", options[i]);
        } else {
            printf("    %s\n", options[i]);
        }
    }
}

void processUserInput(int precision) {
    int selected = 0, check;
    char key;
    double *x = NULL, *y = NULL;
    int m = 0; // số nút nội suy
    int n = 0; // bậc đa thức
    int ready = 0;
    double x0;
    double *coeffs = NULL;
    double **table = NULL;
    while (1) {
        do {
            showMenu(selected);
            key = _getch();
            if (key == 72 && selected > 0) {
                selected--;
            } else if (key == 80 && selected < MAX_OPTIONS - 1) {
                selected++;
            } else if (key == 13) {
                break;
            }
        } while (key != 13);
        
        switch (selected) {
        case 0:
            printLog("Ban da chon chuc nang %d\n", selected + 1);
            system("cls");
            free(x);
            free(y);
            if (readInputFromFile("input.txt", &x, &y, &m) == 0) {
                printf("Doc file thanh cong. Du lieu gom:\n");
                printLog("Doc file thanh cong. Du lieu gom:\n");
                n = m - 1;
                printf("+----------------------+----------------------+\n");
                printf("|         x            |          y           |\n");    
                printf("+----------------------+----------------------+\n");

                printLog("+----------------------+----------------------+\n");
                printLog("|         x            |          y           |\n");
                printLog("+----------------------+----------------------+\n");
                for (int i = 0; i <= n; i++) {
                    printf("| %-20.*lf | %-20.*lf |\n", precision, x[i], precision, y[i]);
                    printLog("| %-20.*lf | %-20.*lf |\n", precision, x[i], precision, y[i]);
                }
                printf("+----------------------+----------------------+\n");
                printLog("+----------------------+----------------------+\n");
                ready = 1;
            } else {
                printf("Doc file that bai\n");
                printLog("Doc file that bai\n");
            }
            printf("Nhan phim enter de tiep tuc...\n");
            printLog("Nhan phim enter de tiep tuc...\n");
            _getch();
            break;
        case 1:
            printLog("Ban da chon chuc nang %d\n", selected + 1);
            system("cls");
            if (!ready) {
                printf("Hay chon chuc nang doc du lieu truoc");
                printLog("Hay chon chuc nang doc du lieu truoc");
            } else {
                if (table != NULL) {
                    for (int i = 0; i <= n; i++) {
                        free(table[i]);
                    }
                    free(table);
                }
                table = bangTySaiPhan(x, y, n, precision, "bangTySaiPhan.txt");
            }
            printf("\n");
            printLog("\n");
            printf("Nhan phim enter de tiep tuc...\n");
            printLog("Nhan phim enter de tiep tuc...\n");
            _getch();
            break;
        case 2:
            printLog("Ban da chon chuc nang %d\n", selected + 1);
            system("cls");
            if (!ready) {
                printf("Hay chon chuc nang doc du lieu truoc\n");
                printLog("Hay chon chuc nang doc du lieu truoc\n");
            } else {
                free(coeffs);
                coeffs = (double *)calloc(n + 1, sizeof(double));
                inDaThucLagrange(x, y, n, precision, coeffs);
            }
            printf("\n");
            printLog("\n");
            printf("Nhan phim enter de tiep tuc...\n");
            printLog("Nhan phim enter de tiep tuc...\n");
            _getch();
            break;
        case 3:
            printLog("Ban da chon chuc nang %d\n", selected + 1);
            system("cls");
            if (!ready) {
                printf("Hay chon chuc nang doc du lieu truoc");
                printLog("Hay chon chuc nang doc du lieu truoc\n");
            } else if (table == NULL) {
                printf("Hay chon chuc nang tao bang ty sai phan truoc");
                printLog("Hay chon chuc nang tao bang ty sai phan truoc");
            } else {
                free(coeffs);
                coeffs = NULL;
                coeffs = (double *)calloc(n + 1, sizeof(double));
                inDaThucNewtonTien(x, y, table, n, precision, coeffs);
            }
            printf("\n");
            printLog("\n");
            printf("Nhan phim enter de tiep tuc...\n");
            printLog("Nhan phim enter de tiep tuc...\n");
            _getch();
            break;
        case 4:
            printLog("Ban da chon chuc nang %d\n", selected + 1);
            system("cls");
            if (!ready) {
                printf("Hay chon chuc nang doc du lieu truoc");
                printLog("Hay chon chuc nang doc du lieu truoc\n");
            } else if (table == NULL) {
                printf("Hay chon chuc nang tao bang ty sai phan truoc");
                printLog("Hay chon chuc nang tao bang ty sai phan truoc");
            } else {
                free(coeffs);
                coeffs = NULL;
                coeffs = (double *)calloc(n + 1, sizeof(double));
                inDaThucNewtonLui(x, y, table, n, precision, coeffs);
            }
            printf("\n");
            printLog("\n");
            printf("Nhan phim enter de tiep tuc...\n");
            printLog("Nhan phim enter de tiep tuc...\n");
            _getch();
            break;
        case 5:
            printLog("Ban da chon chuc nang %d\n", selected + 1);
            system("cls");
            if (!ready) {
                printf("Hay chon chuc nang doc du lieu truoc");
                printLog("Hay chon chuc nang doc du lieu truoc\n");
            } else if (coeffs == NULL) {
                printf("Hay chon chuc nang tim da thuc bang lagrange hoac newton truoc");
                printLog("Hay chon chuc nang tim da thuc bang lagrange hoac newton truoc");
            } else {
                do
                {
                    printf("Nhap 1 so thuc x0: ");
                    printLog("Nhap 1 so thuc x0: ");
                    check = scanf("%lf", &x0);
                    if (check != 1) {
                        printf("Vui long nhap mot so thuc\n");
                        printLog("Vui long nhap mot so thuc!\n");
                        while (getchar() != '\n');
                        continue;
                    }
                } while (check != 1);

                printLog("%.*lf\n", precision, x0);

                tinhDaThucTaixBangHorner(coeffs, n, x0, precision);
            }
            printf("\n");
            printLog("\n");
            printf("Nhan phim enter de tiep tuc...\n");
            printLog("Nhan phim enter de tiep tuc...\n");
            _getch();
            break;
        case 6:
            printLog("Ban da chon chuc nang %d\n", selected + 1);
            system("cls");
            printf("Thoat chuong trinh\n");
            printLog("Thoat chuong trinh\n");
            if (table != NULL) {
                for (int i = 0; i <= n; i++) {
                    free(table[i]);
                }
                free(table);
            }
            if (coeffs != NULL) {
                free(coeffs);
            }
            if (x != NULL) {
                free(x);
            }
            if (y != NULL) {
                free(y);
            }
            return;
        default:
        }
    }
}