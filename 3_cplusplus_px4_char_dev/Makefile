main: main.o cdev.o serial.o fs.o
	@g++ -o main main.o cdev.o  serial.o fs.o

main.o: main.cpp serial.hpp
	@g++ -c cdev.hpp  main.cpp

cdev.o: cdev.cpp  cdev.hpp  fs.h
	@g++ -c cdev.cpp  fs.h

serial.o: serial.cpp  serial.hpp 
	@g++ -c serial.cpp  

fs.o: fs.c  fs.h 
	@g++ -c fs.c  

clean:
	rm -f main *.o
