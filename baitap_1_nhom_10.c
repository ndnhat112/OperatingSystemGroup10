#include <stdio.h>


int main(int argc, const char** argv) {
    // kiem tra dieu kien cua menu
    if (argc < 2) {
        printf("Khong co lua chon trong menu !\n");
        return 1; 
    }

    // in menu
    printf("Menu :\n");
    for (int i = 1; i < argc; i++) {
        printf("%d. %s\n", i, argv[i]); 
    }

    //nhap lua chon
    int choice;
    while (1) {
        printf("Ban hay chon so (1-%d): ", argc - 1);
        scanf("%d", &choice);

        //kiem tra dieu kien cua lua chon
        if ( choice <1 ||choice >= argc ) {
            printf("Lua chon khong hop le !\n");
            return 1;
        }
        printf("Ban da chon : %s\n", argv[choice]);
    }

    
    return 0;
}