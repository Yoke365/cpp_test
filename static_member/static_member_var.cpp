#include <iostream>
#include <stdio.h>

using namespace std;

class STATIC_CLASS
{
public:
    virtual void seti(int i) ;
    static int task_main(void);
    void print_info(void);

private:
   static int _i;
   int _j;
};

int STATIC_CLASS::_i = 1;


void
STATIC_CLASS::print_info(void)
{
    cout << "STATIC_CLASS::_i = " << STATIC_CLASS::_i << endl;
}


int main (int argc, char **argv)
{
    //STATIC_CLASS *g_dev;

    //g_dev = new STATIC_CLASS; // create intance
    //STATIC_CLASS::print_info();
    cout << "test "<< endl;
    return 0;
}
