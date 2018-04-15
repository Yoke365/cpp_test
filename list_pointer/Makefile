# main: main.o work_queue.o time.o
# 	gcc -o main main.o work_queue.o time.o

OBJ_DIR = ./obj  

INC_DIR = -I./  

main: main.o 
	@gcc -o main main.o  
	
main.o: main.c 
	@gcc -c main.c  

# nuttx_i2c.o: nuttx_i2c.c  nuttx_i2c.h
# 	@gcc -c nuttx_i2c.c

clean:
	rm -f main *.o
