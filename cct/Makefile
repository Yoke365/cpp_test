main: main.o cct.o manual_ctrl.o
	@gcc -o main main.o  cct.o manual_ctrl.o

main.o: main.c 
	@gcc -c main.c  

manual_ctrl.o: manual_ctrl.c  manual_ctrl.h
	@gcc -c manual_ctrl.c

cct.o: cct.c  cct.h
	@gcc -c cct.c

clean:
	rm -f main *.o
