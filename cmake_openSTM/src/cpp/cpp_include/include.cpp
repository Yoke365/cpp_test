#include <iostream>
#include <stdio.h>
//#include "common.h"

using namespace std;

#define NAME "xiaozhang"
#define NAME "xiaoming"
#define NAME "xiaoli"

class STATIC_CLASS
{
public:
    STATIC_CLASS();
    ~STATIC_CLASS();
    void print_info(void);

private:
   int _j;
};

STATIC_CLASS::STATIC_CLASS()
{
}
STATIC_CLASS::~STATIC_CLASS()
{

}
void
STATIC_CLASS::print_info(void)
{
}

int main (int argc, char **argv)
{
    STATIC_CLASS *g_dev;

    g_dev = new STATIC_CLASS(); // create intance
    g_dev->print_info();

    return 0;
}
