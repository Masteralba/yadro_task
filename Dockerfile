# Используем базовый образ с GCC для сборки программ на C
FROM gcc:11.3.0

# Устанавливаем рабочую директорию внутри контейнера
WORKDIR /app

# Копируем исходные файлы в контейнер
COPY first.c .
COPY second.c .

# Компилируем программы
RUN gcc first.c -o first.exe
RUN gcc second.c -o second.exe

# Указываем команду для запуска контейнера
CMD ["sh", "-c", "./first.exe | ./second.exe"]