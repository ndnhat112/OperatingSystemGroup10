#include <stdio.h>
#include <stdlib.h>
#include <sys/unistd.h>
#include <sys/shm.h>
#include <sys/wait.h>
#include <sys/ipc.h>

typedef struct shm 
{
    int x,y,z;
    int ready;
} shm;

int main() 
{
    char cwd[1000];
    getcwd(cwd, sizeof(cwd));

    // generate unique key
    key_t key = ftok(cwd, 1);

    // get a shared memory segment 
    // returns an identifier in shmid
    int shmid = shmget(key, sizeof(shm), IPC_CREAT|0666);
    if (shmid == -1) 
    {
        printf("Khong the tao ra id cho vung nho chung\n");
        return 1;
    }

    // attach to shared memory
    shm *shared_memory = (shm*)shmat(shmid, NULL, 0);
    if (shared_memory == (void *)-1) 
    {
        printf("Khong the ket noi toi vung nho chung\n");
        return 1;
    }

    shared_memory->ready = 0;
    // create child process
    pid_t pid = fork();
    
    if (pid < 0) 
    {
        printf("Khong the tao ra process con");
    } else if (pid > 0) {   
        printf("Nhap gia tri cua x: ");
        scanf("%d", &(shared_memory->x));
        printf("Nhap gia tri cua y: ");
        scanf("%d", &(shared_memory->y));

        shared_memory->ready = 1;

        while (shared_memory->ready == 1);

        printf("Gia tri cua z: %d\n", shared_memory->z);
    } else {
        while (shared_memory->ready == 0);
        shared_memory->z = shared_memory->x + shared_memory->y;
        shared_memory->ready = 0;

        shmdt(shared_memory);
        exit(1);
    }

    // detach to shared memory
    shmdt(shared_memory);
}