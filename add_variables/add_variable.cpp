#include <iostream> 

using namespace std; 

class A 
{ 
public: 
    virtual void fun1(void) ;

    virtual void fun2(void) ;
    void set(int z_input); 

    int  z; 

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

void A::set(int z_input)
{	
	z = z_input;
	cout << "z  = " <<  z << endl; 
}



int main (int argc, char **argv)
{
	A *a;

	char b = 2;

    unsigned char c = 5;

	cout << "c = " <<  c << endl;

     
    cout << "create class" << endl; 
	a = new A; 
  
    a->set(5);

	return 0;
}
