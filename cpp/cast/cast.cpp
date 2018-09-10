/**
	LOG INFORMATION:
	a 
	int set(void)  const 
	~a
*/

#include <iostream>
#include <stdio.h>

using namespace std;
class a{
public:
	a():i(2)
	{
		cout<< "a " <<endl;
	}
	~a()
	{
		cout<< "~a" <<endl;
	}
             int set(void)  const 
             {       
             	/**
	 	const attribute:
				仅仅可以修改类内的const类型的成员变量:  const int i;
				不能修改非const类型的变量: int j;	
             	*/
             		cout<< "int set(void)  const " <<endl;
			/*  error */
			// j = 1;  
             		return this->i;
             }

private:
	const int i;
	int j;	
};

extern "C"{ extern int cast_main(int argc, char **argv);}

int cast_main(int argc, char **argv)
{
	int i;

	float f = 166.71;
	i = static_cast<int>(f);

	cout<< "i =" <<  i  <<endl;

	return 0;
}

