#include<iostream>
#include<stdlib.h>
#include"obj.h"



int main()
{
	Space space(7, 7);		  // space height - width
	space.fiilRandomBox(15, 5, 1);    // box quantity, maximum box sizes, density
	space.putBox();
	space.printmatrix();
	space.printBoxCoordinates();
	space.printCenterOfMass();

	system("pause");
	return 0;
}
