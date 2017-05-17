#include <iostream>
#include <stdio.h>
//#include "common.h"
using namespace std;

class SENSOR
{
public:
	 SENSOR(int y, int z);
	 ~SENSOR();
private:
	static void setx(int x);
 	static int _x;
	int _y;
	int _z;
};

SENSOR::SENSOR(int y, int z)
{
	_y = y;
	_z = z;
}

SENSOR::~SENSOR()
{
}

void
SENSOR::setx(int x)
{
   _x = x;
   cout << "_x = " << _x << endl;
}
int SENSOR::_x = 2;

int main(int argc, char **argv)
{
	SENSOR *sensor_p;

	cout<< "test console " <<endl;
	sensor_p = new SENSOR(1,2);
    SENSOR::setx(2);
	return 0;

}
