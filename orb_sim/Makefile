main: main.o wheel_mesg.o 
	@gcc -o main main.o  wheel_mesg.o

main.o: main.c 
	@gcc -c main.c  

wheel_mesg.o: wheel_mesg.c  wheel_mesg.h
	@gcc -c wheel_mesg.c

clean:
	rm -f main *.o
