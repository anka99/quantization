CC = gcc
CFLAGS = -Wall -Wextra -std=c11 -O2
LDFLAGS =

.PHONY: all clean

all: quantization

quantization: main.o structures.o execute.o engine.o input.o
	$(CC) $(LDFLAGS) -o $@ $^

engine.o: engine.c engine.h structures.h
	$(CC) $(CFLAGS) -c $<

execute.o: execute.c execute.h input.h engine.h defines.h
	$(CC) $(CFLAGS) -c $<

input.o: input.c input.h defines.h
	$(CC) $(CFLAGS) -c $<

structures.o: structures.c structures.h
	$(CC) $(CFLAGS) -c $<

main.o: main.c structures.h execute.h defines.h
	$(CC) $(CFLAGS) -c $<

clean:
	rm -f *.o quantization
