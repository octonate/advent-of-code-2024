CC = gcc
CFLAGS = -Wall -Wpedantic -Wextra -Wconversion -Wsign-conversion
LDLIBS = 

$(CC) $(CFLAGS) $(LDLIBS) main.c
