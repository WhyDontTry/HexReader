






myprog: main.o
	gcc -o myprog main.o

main.o: main.c
	gcc -std=c99 -c main.c
