/**
	int &c = int  &b = int &a
*/

#include <iostream>
#include <stdio.h>

using namespace std;

int& fun(int &a)
{
	a++;
	return a;
}
extern "C"{ extern int refence_main(int argc, char **argv);}
int refence_main(int argc, char **argv)
{
	cout<< "test console " <<endl;
    int b = 0;
	
	fun(b);
	cout<< "b= " <<b<<endl;
    
	int& c= fun(b);
	c++;
	cout<< "c= " << c <<endl;
	cout<< "b= " << b <<endl;
	
	return 0;
	
}
