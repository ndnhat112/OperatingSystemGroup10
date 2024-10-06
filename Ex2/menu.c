#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char** argv)
{
	int choice;
    printf("(1): Y\n");
    printf("(0): n\n");
    printf("Nhap lua chon: ");
    scanf("%d", &choice);
    
    while (choice!=0 && choice!=1) 
    {
        printf("Nhap lai: ");
        scanf("%d", &choice);
    }

    return choice;
}
