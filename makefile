all : myshop

Clients.o: Clients.c Clients.h
	gcc -c Clients.c -o Clients.o

Achat.o: Achat.c achat.h
	gcc -c Achat.c -o Achat.o

functions_gestion.o: functions_gestion.c gestion.h
	gcc -c functions_gestion.c -o functions_gestion.o

main.o: main.c main.h
	gcc -c main.c -o main.o

myshop : Clients.o Achat.o functions_gestion.o main.o
	gcc Clients.o Achat.o functions_gestion.o main.o -o myshop

clean:
	rm -f *.o 
	rm myshop