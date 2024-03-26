CC = g++
CFLAGS = -Wall -g

build: main

main: obj
	$(CC) $(CFLAGS) -o main main.o lexer.o lambda.o

obj:
	$(CC) $(CFLAGS) -c main.cpp lexer.cpp lambda.cpp

clean:
	rm -f *.o main
