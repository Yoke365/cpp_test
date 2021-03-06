//Test.cpp
#include<iostream>

using std::cout;
using std::endl;
//声明一个函数模版,用来比较输入的两个相同数据类型的参数的大小，class也可以被typename代替，
//T可以被任何字母或者数字代替。

template <class T>   // 定义1个模板类

T min(T x,T y)       // 传入类的参数
{
	return(x<y)?x:y;
}

extern "C"{ extern int template_main(int argc, char **argv);}
int template_main(int argc, char **argv)
{  
    int n1=2,n2=10;

    double d1=1.5,d2=5.6;

    cout<< "较小整数:"<<min(n1,n2)<<endl;
    cout<< "较小实数:"<<min(d1,d2)<<endl;

    return 0;
}
