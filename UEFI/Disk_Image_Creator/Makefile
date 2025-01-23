CC=gcc
TARGET=write_gpt
CFLAGS=-std=c17 -Wall -Werror -Wextra -Wpedantic -ggdb 
all:
	$(CC) -o $(TARGET) write_gpt.c $(CFLAGS)
clean:
	rm -f $(TARGET)
	rm -f test.img
