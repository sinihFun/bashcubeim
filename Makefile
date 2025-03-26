bashcubeim.out : main.o menu.o
	gcc main.o menu.o -o bashcubeim.out -lncurses

main.o : main.c
	gcc -c main.c

menu.o : menu.c
	gcc -c menu.c
