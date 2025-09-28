#include <stdio.h>
#include <stdlib.h>
#include "menu.h"
#include "utils.h"
int main() {
    int precision, check;
    char choice;    
    do {
        printf("Nhap so chu so hien thi phan thap phan (Nhap so nguyen duong): ");
        printLog("Nhap so chu so hien thi phan thap phan (Nhap so nguyen duong): ");
        check = scanf("%d", &precision);
        if (check != 1) {
            printf("Vui long nhap mot so nguyen duong\n");
            printLog("Vui long nhap mot so nguyen duong\n");
            while (getchar() != '\n');
            precision = -1;
            continue;
        }
        printLog("%d\n", precision);
        if (precision < 0) {
            printf("So chu so hien thi phan thap phan khong the am\n");
            printLog("So chu so hien thi phan thap phan khong the am\n");
            printf("Xin moi nhap lai.\n");
            printLog("Xin moi nhap lai.\n");
        }
        if (precision > 15) {
            printf("So ban vua nhap lon hon so chu so co the hien thi chinh xac phan thap phan cua chuong trinh\n");
            printLog("\nSo ban vua nhap lon hon so chu so co the hien thi chinh xac phan thap phan cua chuong trinh\n");
            printf("Chuong trinh se tu dong hien thi chinh xac 15 chu so phan thap phan\n");
            printLog("Chuong trinh se tu dong hien thi chinh xac 15 chu so phan thap phan\n");
            do {
                printf("Ban co dong y khong (y/N, q de thoat chuong trinh): ");
                printLog("Ban co dong y khong (y/N, q de thoat chuong trinh): ");
                scanf(" %c", &choice);
                printLog("%c\n", choice);
                if (choice == 'y' || choice == 'Y') {
                    precision = 15;
                    break;
                } else if (choice == 'n' || choice == 'N') {
                    printf("Xin moi nhap lai.\n");
                    printLog("Xin moi nhap lai.\n");
                    precision = -1;
                    break;
                } else if (choice == 'q' || choice == 'Q') {
                    printf("Thoat chuong trinh");
                    printLog("Thoat chuong trinh");
                    exit(0);
                } else {
                    printf("Lua chon khong hop le. Vui long nhap lai\n");
                    printLog("Lua chon khong hop le. Vui long nhap lai\n");
                }
            } while (1);
        }
    } while (precision < 0 || precision > 15);
    processUserInput(precision);
    printLog("------------------------------------------------\n");
}
