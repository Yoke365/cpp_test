# main: main.o work_queue.o time.o
# 	gcc -o main main.o work_queue.o time.o

main: main.o stepmotor.o
	gcc -o main main.o stepmotor.o

main.o: main.c 
	gcc -c main.c  

stepmotor.o: stepmotor.c  stepmotor.h
	gcc -c stepmotor.c

# time.o: time.c time.h
# 	gcc -c time.c  

clean:
	rm -f main *.o
