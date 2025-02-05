#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>

int main()
{
    // Ключ разделяемой памяти
    int mem_id;

    // Cоздаем идентефикатор разделяемой памяти на основе IPC_PRIVATE
    mem_id = shmget(IPC_PRIVATE, 1000, IPC_CREAT | 0666);

    // Проверяем возникновение ошибки
    if (mem_id == -1) {
        perror("shmget failed");
        return 1;
    }

    // Выводим полученный ключ в стандарнтый поток
    printf("%d\n", mem_id);

    // указатель на сегмент разделяемой памяти
    char* shm_ptr;

    // Примоединяес сегмент к адресному пространству процесса
    shm_ptr = (char*)shmat(mem_id, NULL, 0);

    // Проверяем возникновение ошибки
    if (shm_ptr == (char *)-1) {
        perror("shmat failed");
        return 1;
    }

    // Печатаем строку из условия в участок разделяемой памяти
    sprintf(shm_ptr, "Hello world!");

    // Отсоединяем сегмент
    shmdt(shm_ptr);

    return 0;
}
