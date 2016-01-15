CC=gcc
CFLAGS=-W -pedantic -Wall -g

main: clean color_table.o main.o
	$(CC) color_table.o main.o lib/libimage64.a -o main
	
color_table.o: 
	$(CC) -g -c color_table.c

main.o: 
	$(CC) $(CFLAGS) -c main.c
	
clean: 
	rm -f *.o 
