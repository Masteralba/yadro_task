#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>

int main() {

    // Ключ разделяемой памяти
    int mem_id;

    // Читаем ключ из потока
    if (scanf("%d", &mem_id) != 1) {
        fprintf(stderr, "Failed to read shmid from stdin\n");
        return 1;
    }
    
    // Идентификатор существующего сегмента разделяемой памяти
    char *shm_ptr;

    // Присоединяем сегмент к адресному пространству процесса
    shm_ptr = (char *)shmat(mem_id, NULL, 0);
    if (shm_ptr == (char *)-1) {
        perror("shmat failed");
        return 1;
    }

    // Читаем данные из разделяемой памяти
    printf("Data read from shared memory: %s\n", shm_ptr);

    // Удаляем сегмент
    shmctl(mem_id, IPC_RMID, NULL);

    return 0;
}