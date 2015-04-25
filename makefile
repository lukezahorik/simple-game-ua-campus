game100: bronco.o locations.o scanner.o
	gcc bronco.o locations.o scanner.o -o game100

bronco.o: bronco.c
	gcc -Wall -g -c bronco.c

locations.o: locations.c locations.h
	gcc -Wall -g -c locations.c

scanner.o: scanner.c scanner.h
	gcc -Wall -g -c scanner.c

clean:
	rm bronco.o locations.o scanner.o

puzzle: game100
	cat PUZZLE | game100

run: game100
	game100

	
