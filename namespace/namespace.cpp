#include <iostream>
#include <stdio.h>

using namespace std;

class A
{
public:
    virtual void seti(int i) ;
    virtual void setj(int j) ;
    static int task_main(void);
    void print_info(void);
private:
   int _i;
   int _j;
};

void A::seti(int i)
{
    _i = i;
    cout << "A's seti()" << endl;
    cout << "_i = " << _i << endl;
}

void A::setj(int j)
{
    _j = j;
	cout << "A's setj()"  << endl;
	cout << "_j = " << _j << endl;
}

namespace test {
    A *g_dev;
}

using namespace test;

/* static function */
int
A::task_main(void)
{
    if (g_dev != NULL) {
        printf("g_dev->_j = %d\r\n", g_dev->_j);
    } else {
        cout << "g_dev is null" << endl;
        return -1;
    }
}

void
A::print_info(void)
{
	cout << "_i = " << _i << endl;
    cout << "_j = " << _j << endl;
}



using namespace test;

int main (int argc, char **argv)
{

    g_dev = new A; // create intance
    g_dev->seti(5);
    g_dev->seti(9);

    A::task_main();
    g_dev->print_info();

    return 0;
}
