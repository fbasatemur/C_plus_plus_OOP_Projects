#include<iostream>
#include<time.h>
#include<fstream>
#include<iomanip>
#include"obj.h"

using namespace std;

// Class Space

Space::Space(int height, int width)				// constructer of space class
{
	while (height < 0 || width < 0)				// the size of space is controlled
	{
		cout << "Matrix size must be greater than zero !" << endl;
		cout << "Height :";
		cin >> height;
		cout << "Width  :";
		cin >> width;
	}
	spaceHeight = height;
	spaceWidth = width;

	matrix = new int* [spaceHeight];			//

	for (int i = 0; i < spaceHeight; i++)		// dynamic array defined
	{
		matrix[i] = new int[spaceWidth];		//
	}
	clearmatrix();								// matrix is filled with zero				
}
Space::~Space()									// matrix is destroyed
{
	for (int i = 0; i < spaceHeight; i++)
		delete matrix[i];

	delete matrix;
}
void Space::printmatrix()						// matrix is drawn to the screen
{
	int i = 0, j = 0;

	for (j = 0; j < spaceWidth; j++)
		cout << " -";

	cout << endl;
	for (i = 0; i < spaceHeight; i++)
	{
		cout << '|';

		for (j = 0; j < spaceWidth; j++)
			cout << char(matrix[i][j]) << " ";

		cout << '|' << endl;
	}

	for (j = 0; j < spaceWidth; j++)
		cout << " -";

	cout << endl;
}
void Space::clearmatrix()						// matrix is filled with zero
{
	int i = 0, j = 0;
	for (i = 0; i < spaceHeight; i++)
		for (j = 0; j < spaceWidth; j++)
			matrix[i][j] = 0;
}

int Space::randSize(int maxBoxSize)				// random size is determined
{
	int random = rand() % maxBoxSize;
	return random > 0 ? random : randSize(maxBoxSize);
}

// Parameters -> total of boxes, maximum box lenght and density

void Space::fiilRandomBox(int totalBox, int maxBoxSize, int density = 1)	// 
{
	while (totalBox <= 0 || maxBoxSize <= 0 || density < 1)			// Control of parameters
	{
		cout << "Box quantity, size or density are incorrect !" << endl;
		cout << "Box quantity : ";
		cin >> totalBox;
		cout << "Box size (Max) : ";
		cin >> maxBoxSize;
		cout << "Density : ";
		cin >> density;
	}
	boxes = new Box[totalBox];									// dynamic array
	spaceTotalBox = totalBox;
	int randomSizeHe = 0;
	int randomSizeWi = 0;
	cout << "  Height  Width  Density  Mass" << endl;

	srand(time(NULL));
	for (int i = 0; i < totalBox; i++)							// required size assignments
	{
		randomSizeHe = randSize(maxBoxSize);
		randomSizeWi = randSize(maxBoxSize);
		cout << setw(5) << left << i + 1 << right << randomSizeHe << setw(8) << randomSizeWi << setw(8) << density << setw(8) << randomSizeHe * randomSizeWi * density << endl;
		boxes[i].setBox(randomSizeHe, randomSizeWi, density, randomSizeHe * randomSizeWi * density);
	}
}
void Space::putBox()														// boxes are positioned
{
	int boxNo = 49;															// ASCII Table -> 49 => 1
	for (int i = 0; i < spaceTotalBox; i++)
	{
		if (boxes[i].getBoxheight() > spaceHeight || boxes[i].getBoxwidth() > spaceWidth)
		{
			cout << setw(3) << left << i + 1 << right << "failed to box loaded" << endl;
			boxes[i].setBox(0, 0, 0, 0);										// failed to box loaded -> 0,0,0,0
			continue;
		}
		else
		{
			if (spaceControl(boxes + i) || spaceControl(swap(boxes + i)))		// Height x Width OR Width x Height 
			{
				for (int a = 0; a < boxes[i].getBoxheight(); a++)
				{
					for (int b = 0; b < boxes[i].getBoxwidth(); b++)
						matrix[boxes[i].getCoordystart() + a][boxes[i].getCoordxstart() + b] = boxNo;
				}

				cout << setw(3) << left << i + 1 << right << "box loaded" << endl;
				boxNo++;
			}
			else
			{
				cout << setw(3) << left << i + 1 << right << "failed to box loaded" << endl;
				boxes[i].setBox(0, 0, 0, 0);								//  failed to box loaded -> 0,0,0,0
				boxNo++;
			}
		}
		if (boxNo == 123 || boxNo == 91 || boxNo == 58)
			boxNo = (boxNo == 58 ? boxNo = 65 : (boxNo == 91 ? boxNo = 97 : boxNo = 49));		// ASCII Table -> 1-9 , A-Z , a-z
	}
}
int Space::spaceControl(Box* boxes)											// gap contol
{
	int counterX = 0, counterY = 0;

	for (int i = 0; i < spaceHeight; i++)
	{
		for (int j = 0; j < spaceWidth; j++)
		{
			if (matrix[i][j] == 0 && spaceHeight - i >= boxes->getBoxheight() && spaceWidth - j >= boxes->getBoxwidth())		// prevent overflow
			{
				if (matrix[i][j + boxes->getBoxwidth() - 1] == 0 && matrix[i + boxes->getBoxheight() - 1][j] == 0 && matrix[i + boxes->getBoxheight() - 1][j + boxes->getBoxwidth() - 1] == 0)		// is it appropriate ?
				{
					for (int a = 0; a < boxes->getBoxwidth(); a++)
					{
						if (matrix[i][j + a] == 0)
							counterX++;
					}
					for (int b = 0; b < boxes->getBoxheight(); b++)
					{
						if (matrix[i + b][j] == 0)
							counterY++;
					}
					if (counterX == boxes->getBoxwidth() && counterY == boxes->getBoxheight())		// Does the box size fit ?
					{
						boxes->setCoord(j, i, j + boxes->getBoxwidth() - 1, i + boxes->getBoxheight() - 1);
						return 1;
					}
					else
					{
						counterX = 0;
						counterY = 0;
						boxes->setCoord(0, 0, 0, 0);	// failed to box loaded -> 0,0,0,0
					}
				}
			}
			else
				boxes->setCoord(0, 0, 0, 0);		// failed to box loaded -> 0,0,0,0
		}
	}

	return 0;
}
void Space::printBoxCoordinates()					// write box coordinates to screen and file
{
	ofstream outfile;
	outfile.open("tutorial.txt");
	outfile << "    Coordinates   Rotation (0/1)" << endl;
	cout << "    Coordinates   Rotation (0/1)" << endl;
	for (int i = 0; i < spaceTotalBox; i++)
	{
		cout << setw(5) << left << i + 1 << right << boxes[i].getCoordxstart() << ' ' << boxes[i].getCoordystart() << "  "
			<< boxes[i].getCoordxend() << ' ' << boxes[i].getCoordyend() << setw(8) << boxes[i].getRotFlag() << endl;
		outfile << setw(5) << left << i + 1 << right << boxes[i].getCoordxstart() << ' ' << boxes[i].getCoordystart() << "  "
			<< boxes[i].getCoordxend() << ' ' << boxes[i].getCoordyend() << setw(8) << boxes[i].getRotFlag() << endl;
	}
	int i = 0, j = 0;

	for (j = 0; j < spaceWidth; j++)
		outfile << " -";

	outfile << endl;
	for (i = 0; i < spaceHeight; i++)
	{
		outfile << '|';

		for (j = 0; j < spaceWidth; j++)
			outfile << char(matrix[i][j]) << " ";

		outfile << '|' << endl;
	}
	for (j = 0; j < spaceWidth; j++)
		outfile << " -";

	outfile.close();
}
void Space::printCenterOfMass()		// find mass centers
{
	/*
	What is center of mass ?
	source: https://www.khanacademy.org/science/physics/linear-momentum/center-of-mass/a/what-is-center-of-mass

	COMx = m1*x1 + m2*x2 + ... / m1 + m2 + ...
	COMy = m1*y1 + m2*y2 + ... / m1 + m2 + ...
	*/
	float sumNUMx = 0;				// COMx Numerator
	float sumNUMy = 0;				// COMy Numerator
	float sumDENO = 0;				// denominator

	for (int i = 0; i < spaceTotalBox; i++)
	{
		if (boxes[i].getBoxmass() == 0)
			continue;
		else
		{
			sumNUMy += ((boxes[i].getCoordyend() + boxes[i].getCoordystart()) / 2) * boxes[i].getBoxmass();	   // y1*m1 + y2*m2 +...		y1 -> ( starty + endy ) /2    -> y middle point
			sumNUMx += ((boxes[i].getCoordxend() + boxes[i].getCoordxstart()) / 2) * boxes[i].getBoxmass();   // x1*m1 + x2*m2 +...		x1 -> ( startx + endx ) /2	  -> x middle point
			sumDENO += boxes[i].getBoxmass();                                                                  // m1 + m2 +...			       -> sum of box masses
		}
	}
	spaceXCenter = sumNUMx / sumDENO;
	spaceYCenter = sumNUMy / sumDENO;
	cout << "Space Center Coordinate:" << endl << "x: " << spaceXCenter << " " << "y: " << spaceYCenter << endl;

}


// Class Box

Box::Box()
{
	;
}
void Box::setBox(int height, int width, int density, int mass)
{
	this->width = width;
	this->height = height;
	this->density = density;
	this->mass = mass;
}

int Box::getBoxdensity()
{
	return density;
}
int Box::getBoxwidth()
{
	return width;
}
int Box::getBoxheight()
{
	return height;
}
int Box::getBoxmass()
{
	return mass;
}
bool Box::getRotFlag()
{
	return rotationFlag;
}
Box* Box::swap(Box* boxes)			// change height and width
{
	boxes->setBox(boxes->getBoxwidth(), boxes->getBoxheight(), boxes->getBoxdensity(), boxes->getBoxmass());
	boxes->rotationFlag = true;		// box rotation
	return boxes;
}


// Class Coord

Coord::Coord()
{
	;
}
void Coord::setCoord(int x, int y, int x1, int y1)
{
	xstart = x;
	ystart = y;
	xend = x1;
	yend = y1;
}

int Coord::getCoordxstart()
{
	return xstart;
}
int Coord::getCoordystart()
{
	return ystart;
}
int Coord::getCoordxend()
{
	return xend;
}
int Coord::getCoordyend()
{
	return yend;
}

