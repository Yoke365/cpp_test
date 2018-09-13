#include<iostream>
#include"template_class.h"

using std::cout;
using std::endl;
extern "C"{ extern int template_class_main(int argc, char **argv);}
int template_class_main(int argc, char **argv)
{
    myClass<int,int> class1(3,5);
    class1.show();
    myClass<int,char> class2(3,'a');
    class2.show();
    myClass<double,int> class3(2.9,10);
    class3.show();

    return 0;
}


