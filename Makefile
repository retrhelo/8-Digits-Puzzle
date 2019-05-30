SRC=struct.c display.c main.c
OBJ=struct.o display.o main.o

main: $(OBJ)
	cc $(OBJ) -o main

*.o: $(SRC)
	cc -c *.o

clean: 
	rm $(OBJ) main
