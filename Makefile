CC = gcc
CFLAGS = -Wall -Wextra

vector_program.exe: main.o vector.o types.o tests.o
	$(CC) $(CFLAGS) -o vector_program.exe main.o vector.o types.o tests.o

main.o: main.c vector.h types.h
	$(CC) $(CFLAGS) -c main.c

vector.o: vector.c vector.h types.h
	$(CC) $(CFLAGS) -c vector.c

types.o: types.c types.h
	$(CC) $(CFLAGS) -c types.c

tests.o: tests.c vector.h
	$(CC) $(CFLAGS) -c tests.c

clean:
	del *.o vector_program.exe

run: vector_program.exe
	vector_program.exe

.PHONY: clean run