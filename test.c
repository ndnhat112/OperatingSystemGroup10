#include <stdio.h>

int main(int argc, const char** argv) {
    // Ki?m tra ði?u ki?n c?a menu
    if (argc < 2) {
        printf("Khong co lua chon trong menu !\n");
        return 1;
    }

    // In menu
    printf("Ban co muon xoa file nay khong:\n");
    for (int i = 1; i < argc; i++) {
        printf("%d. %s\n", i, argv[i]);
    }

    // Nh?p l?a ch?n
    int choice;
    printf("Nhap lua chon cua ban: ");
    scanf("%d", &choice);

    // Ki?m tra l?a ch?n h?p l?
    if (choice < 1 || choice >= argc) {
        printf("Lua chon khong hop le!\n");
        return 1;  // Tr? v? m? l?i
    }

    // Tr? v? giá tr? c?a l?a ch?n
    return choice;
}