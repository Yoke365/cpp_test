
main: main.o c_pointer_fun.o 
	@gcc -o main main.o  c_pointer_fun.o

main.o: main.c 
	@gcc -c main.c  

c_pointer_fun.o: c_pointer_fun.c  c_pointer_fun.h
	@gcc -c c_pointer_fun.c


clean:
	rm -f main *.o
