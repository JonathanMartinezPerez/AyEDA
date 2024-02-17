#Compilar con: make
#Ejecutar con: make run
#Limpiar con: make clean

CC = g++
CFLAGS = -Wall -g -std=c++17

p2_execute: p3_main.cc  number.o
	$(CC) $(CFLAGS) -o p3_execute p3_main.cc number.o
	
number.o: number.cc number.h
	$(CC) $(CFLAGS) -c number.cc

clean:
	rm -f *.o p3_execute