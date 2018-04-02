# main: main.o work_queue.o time.o
# 	gcc -o main main.o work_queue.o time.o

OBJ_DIR = ./obj  

INC_DIR = -I./  

main: main.o file_autochange_char.o 
	@gcc -o main main.o  file_autochange_char.o

main.o: main.c 
	@gcc -c main.c  

file_autochange_char.o: file_autochange_char.c  file_autochange_char.h
	@gcc -c file_autochange_char.c

clean:
	rm -f main *.o
