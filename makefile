CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -g -D_POSIX_C_SOURCE=200809L
TARGET = cas_system

SRCS = main.c context.c natural_menu.c integer_menu.c rational_menu.c polynomial_menu.c \
       N.c Z.c Q.c P.c \
       readDigitN.c readDigZ.c readDigitQ.c readPoly.c

OBJS = $(SRCS:.c=.o)

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(TARGET) -lm

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f *.o $(TARGET)

.PHONY: all clean