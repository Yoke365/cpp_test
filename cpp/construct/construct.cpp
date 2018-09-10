/**
	log information:
	a 
	b 
	c 
	~c
	~b
	~a

*/

#include <iostream>
#include <stdio.h>

using namespace std;
class a{
public:
	a()
	{
		cout<< "a " <<endl;
	}
	~a()
	{
		cout<< "~a" <<endl;
	}
};

class b {
public:
	b()
	{
		cout<< "b " <<endl;
	}
	~b()
	{
		cout<< "~b" <<endl;
	}	
};

class c : public a, public b {
public:
	c()
	{
		cout<< "c " <<endl;
	}
	~c()
	{
		cout<< "~c" << endl;
	}	
};

c c1;
extern "C"{ extern int construct_main(int argc, char **argv);}
int construct_main(int argc, char **argv)
{
     
	 
	return 0;	
}

