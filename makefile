CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -g -D_POSIX_C_SOURCE=200809L -Iinclude
TARGET = cas_system

# Файлы интерфейса
INTERFACE = src/main.c src/context.c src/natural_menu.c src/integer_menu.c \
            src/rational_menu.c src/polynomial_menu.c

# Математические модули
MATH = src/math/N.c src/math/Z.c src/math/Q.c src/math/P.c

# Функции ввода-вывода
IO = src/io/readDigitN.c src/io/readDigZ.c src/io/readDigitQ.c src/io/readPoly.c

# Все исходники
SRCS = $(INTERFACE) $(MATH) $(IO)

# Объектные файлы будут в корне
OBJS = $(notdir $(SRCS:.c=.o))

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(TARGET) -lm

# Правило компиляции для файлов из разных папок
%.o: src/%.c
	$(CC) $(CFLAGS) -c $< -o $@

%.o: src/math/%.c
	$(CC) $(CFLAGS) -c $< -o $@

%.o: src/io/%.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f *.o $(TARGET)

.PHONY: all clean
