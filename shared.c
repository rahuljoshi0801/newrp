#include <stdio.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <unistd.h>

typedef struct {
  char data[100];
} shared_mem;
int main() {
  key_t key = ftok("/home/ubuntu/Desktop/semaphore", 65);
  printf("The value of  key is %d\n", key);
  int shmid = shmget(key, sizeof(shared_mem), 0666 | IPC_CREAT);
  printf("The value of  shmid is %d\n", shmid);
  shared_mem *shm_ptr = (shared_mem *)shmat(shmid, NULL, 0);
  printf("The value of shared memory pointer is %p\n", (void *)shm_ptr);
  // Keep writing messages continuously
  for (int i = 1; i <= 200; i++) {
    sprintf(shm_ptr->data, "Message-%d", i);
    printf("[Writer] Wrote: %s\n", shm_ptr->data);
    usleep(100000); // small delay (0.1 sec) so reader can interfere
  }
  shmdt(shm_ptr);
  return 0;
}
Reader.c
#include <stdio.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <unistd.h>
    typedef struct {
  char data[100];
} shared_mem;
int main() {
  key_t key = ftok("/home/ubuntu/Desktop/semaphore", 65);
  printf("The value of  key is %d\n", key);
  int shmid = shmget(key, sizeof(shared_mem), 0666);
  printf("The value of  shmid is %d\n", shmid);
  shared_mem *shm_ptr = (shared_mem *)shmat(shmid, NULL, 0);
  printf("The value of shared memory pointer is %p\n", (void *)shm_ptr);
  // Keep reading messages continuously
  for (int i = 1; i <= 200; i++) {
    printf("[Reader] Read : %s\n", shm_ptr->data);
    usleep(150000); // 0.15delay so we catch writer mid-update sometimes
  }
  shmdt(shm_ptr);
  shmctl(shmid, IPC_RMID, NULL); // remove shared memory
  return 0;
}
