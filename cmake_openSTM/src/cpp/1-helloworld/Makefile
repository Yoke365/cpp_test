main: main.o helloworld.o
	@g++ -o main main.o helloworld.o 

main.o: main.cpp
	@g++ -c helloworld.hpp  main.cpp

helloworld.o: helloworld.cpp  helloworld.hpp 
	@g++ -c helloworld.cpp  

clean:
	rm -f main *.o
