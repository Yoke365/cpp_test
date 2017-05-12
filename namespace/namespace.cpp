#include <iostream> 

using namespace std; 

class A 
{ 
public: 
    virtual void fun1(void) ;
    virtual void fun2(void) ;
private:
   int i;
   int j; 
}; 

void A::fun1(void)
{
	cout << "A's fun1()" << endl; 
        i = 5;
	cout << "i = " << i << endl; 

}

void A::fun2(void)
{
	cout << "A's fun2()" << endl; 	
	cout << "call internal function fun1" << endl; 
	this->fun1();
}

int main (int argc, char **argv)
{
	A *a;

        a = new A; // create intance
        a->fun1();

	return 0;

}
