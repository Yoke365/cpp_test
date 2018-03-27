# main: main.o work_queue.o time.o
# 	gcc -o main main.o work_queue.o time.o

OBJ_DIR = ./obj  

INC_DIR = -I./  


main: main.o stepmotor.o protocol.o pwm_stepmotor.o
	@gcc -o main main.o stepmotor.o protocol.o pwm_stepmotor.o

main.o: main.c 
	@gcc -c main.c  

pwm_stepmotor.o: pwm_stepmotor.c  stepmotor.h protocol.h
	@gcc -c pwm_stepmotor.c

stepmotor.o: stepmotor.c  stepmotor.h
	@gcc -c stepmotor.c

protocol.o: protocol.c  protocol.h
	@gcc -c protocol.c

# time.o: time.c time.h
# 	gcc -c time.c  

clean:
	rm -f main *.o
