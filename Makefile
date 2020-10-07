CC = gcc
CFLAGS = -Wall -std=gnu99 -g -c
INCLUDES = 
all: bin/habitUnzip

bin/habitUnzip:	src/main.o
	$(CC) src/main.o -lz -o $@

src/main.o:	src/main.c
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm src/*.o
	rm bin/habitUnzip
