/**
	log information:
 
	a(int v1_t) 
	b(int v2_t) 
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
	a(int v1_t)
	{  
		
		cout<< "a(int v1_t) " <<endl;
		v1 = v1_t; 
	}
	~a()
	{
		cout<< "~a" <<endl;
	}

private: 
	int v1;
};

class b {
public:
	b()
	{
		cout<< "b " <<endl;
	}
	b(int v2_t)
	{
		cout<< "b(int v2_t) " <<endl;
		v2 = v2_t; 
	}
	~b()
	{
		cout<< "~b" <<endl;
	}	

private: 
	int v2;
};

class c : public a, public b {
public:
	c():a(1),b(1)
	{
		cout<< "c " <<endl;
	}
	~c()
	{
		cout<< "~c" << endl;
	}
	
private: 
	int v3;
};

c c1;

int main(int argc, char **argv)
{
     
	 
	return 0;	
}


