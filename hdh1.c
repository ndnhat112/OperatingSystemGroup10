#include <stdio.h>
#include <stdlib.h>

int main(int argc, const char** argv) {
    // kiem tra dieu kien
    if (argc < 2) {
        printf("No menu options provided!\n");
        return 1; 
    }

    // in menu
    printf("Menu options:\n");
    for (int i = 1; i < argc; i++) {
        printf("%d. %s\n", i, argv[i]); 
    }

    //nhap lua chon
    int choice;
    printf("Please select an option (1-%d): ", argc - 1);
    scanf("%d", &choice);

    //kiem tra dieu kien cua lua chon
    if (choice < 1 || choice >= argc) {
        printf("Invalid choice!\n");
        return 1; 
    }

   
    printf("You selected: %s\n", argv[choice]);

    return 0;
}