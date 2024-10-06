#include <stdio.h>

int main(int argc, const char** argv) {
    printf("Ban co muon xoa file nay khong:\n");
    for (int i = 1; i < argc; i++) {
        printf("%d. %s\n", i, argv[i]);
    }

    int choice;
    printf("Nhap lua chon cua ban: ");
    scanf("%d", &choice);

    while (choice != 1 && choice != 2)
    {
        printf("Nhap lai: ");
        scanf("%d", &choice);
    }

    return choice;
}