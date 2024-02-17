#Compilar con: make
#Ejecutar con: make run
#Limpiar con: make clean

CC = g++
CFLAGS = -Wall -g -std=c++17

p1_execute: p1_main_rp.cc 
	$(CC) $(CFLAGS) -o p1_execute p1_main_rp.cc
	
clean:
	rm -f *.o p1_execute

run: p1_execute
	./p1_execute