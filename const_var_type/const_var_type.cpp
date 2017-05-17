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

	//  int set(void)  const
	//  {
	//  	/**
	// const attribute:
	// 	仅仅可以修改类内的const类型的成员变量:  const int i;
	// 	不能修改非const类型的变量: int j;
	//  	*/
	//  		cout<< "int set(void)  const " <<endl;
	// /*  error */
	// // j = 1;
	//  		return this->i;
	//  }

	 int set(const int＊p);

private:
	const int i;
	int j;
};

int
a::set(const int＊p)
{
	  cout<< "a::set(const int＊p) " <<endl;
	  return 0;
}

const int test[2] = {1,1};

int main(int argc, char **argv)
{
    a *a1 = new a;
	const  int *p_test = test;

	// a1-> set();
	a1-> set(p_test);

	delete a1;

	return 0;
}
