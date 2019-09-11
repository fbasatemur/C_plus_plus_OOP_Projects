#include <iostream>
#include <fstream>
#include <math.h>

using namespace std;

// necessary functions for matrix and sobel matrix are created in this class
class Matrix
{
public:

	void setMatrixHeight(int matrixHeight)
	{
		this->matrixHeight = matrixHeight;
	}
	void setMatrixWidth(int matrixWidth)
	{
		this->matrixWidth = matrixWidth;
	}

	int getMatrixHeight()
	{
		return matrixHeight;
	}
	int getMatrixWidth()
	{
		return matrixWidth;
	}

	void setMatrix(int i, int j, int v)
	{
		matrix[i][j] = v;
	}
	void createMatrix();                                 // creates a dynamic matrix

	void setSobelMatrix(int i, int j, int v)
	{
		sobelMatrix[i][j] = v;
	}
	int getSobelMatrix(int i, int j)
	{
		return sobelMatrix[i][j];
	}
	void createSobel();									 // creates a dynamic sobelMatrix

protected:

	int** matrix;                                   // stores data read from binary file
	int** sobelMatrix;                              // the sobel process is stored here
	int matrixHeight;                               // matrix height
	int matrixWidth;                                // matrix width
};

// overload of functions defined in this class
class Image :public Matrix
{
public:
	friend ifstream& operator>> (ifstream& infile, Image& I)
	{
		// read from binary file to object

		if (infile.is_open())
		{
			// read image sizes
			char* buffer = new char[2];
			infile.read(buffer, 2);

			// first read image height
			int height = int((buffer[0] + 256) % 256);
			// second read image width
			int width = int((buffer[1] + 256) % 256);

			I.setMatrixHeight(height);
			I.setMatrixWidth(width);
			I.createMatrix();

			int imageSize = height * width;

			delete buffer;

			char* buff = new char[imageSize];
			infile.read(buff, imageSize);

			// now image data is placed
			int index = 2;

			for (int i = 0; i < width; i++)
				for (int j = 0; j < height; j++)
					I.setMatrix(j, i, int(buff[index++]));

			delete buff;
		}
		else
			cout << "File is not found !" << endl;

		infile.close();
		return infile;
	}

	friend ofstream& operator<< (ofstream& outfile, Image& I)
	{
		// writing to text file

		for (int i = 0; i < I.getMatrixHeight() - 2; i++)
		{
			for (int j = 0; j < I.getMatrixWidth() - 2; j++)
				I.getSobelMatrix(i, j) ? outfile << "*" : outfile << " ";

			outfile << endl;
		}
		outfile.close();

		return outfile;
	}

	Image operator+ (Image& I)
	{
		// + operator overloads for image class objects

		Image img;
		img.setMatrixHeight(I.getMatrixHeight());
		img.setMatrixWidth(I.getMatrixWidth());
		img.createSobel();

		for (int i = 0; i < I.getMatrixHeight() - 2; i++)
		{
			for (int j = 0; j < I.getMatrixWidth() - 2; j++)
			{
				if (this->getSobelMatrix(i, j) || I.getSobelMatrix(i, j))
					img.setSobelMatrix(i, j, 1);

				else
					img.setSobelMatrix(i, j, 0);
			}
		}
		return img;
	}

	Image operator* (Image& I)
	{
		// AND the operation is done on two objects

		Image img;
		img.setMatrixHeight(I.getMatrixHeight());
		img.setMatrixWidth(I.getMatrixWidth());
		img.createSobel();

		for (int i = 0; i < I.getMatrixHeight() - 2; i++)
		{
			for (int j = 0; j < I.getMatrixWidth() - 2; j++)
			{
				if (this->getSobelMatrix(i, j) && I.getSobelMatrix(i, j))
					img.setSobelMatrix(i, j, 1);

				else
					img.setSobelMatrix(i, j, 0);
			}
		}

		return img;
	}

	Image operator! ()
	{
		// NOT operator overloaded  

		Image img;
		img.setMatrixHeight(this->getMatrixHeight());
		img.setMatrixWidth(this->getMatrixWidth());
		img.createSobel();
		bool value = 0;

		for (int i = 0; i < this->getMatrixHeight() - 2; i++)
		{
			for (int j = 0; j < this->getMatrixWidth() - 2; j++)
			{
				value = (this->getSobelMatrix(i, j) == 0) ? 1 : 0;
				img.setSobelMatrix(i, j, value);
			}
		}
		return img;
	}

	void threshold(int);
	void sobel();
};

void Matrix::createMatrix()
{
	matrix = new int* [matrixHeight];

	for (int i = 0; i < matrixHeight; i++)
		matrix[i] = new int[matrixWidth];
}
void Matrix::createSobel()
{
	sobelMatrix = new int* [matrixHeight - 2];

	for (int i = 0; i < matrixHeight - 2; i++)
		sobelMatrix[i] = new int[matrixWidth - 2];
}

void Image::threshold(int thdValue)
{
	// places 1 or 0 according to the threshold

	for (int i = 0; i < matrixHeight - 2; i++)
		for (int j = 0; j < matrixWidth - 2; j++)
			sobelMatrix[i][j] > thdValue ? (sobelMatrix[i][j] = 1) : (sobelMatrix[i][j] = 0);

}

void Image::sobel()
{
	// first image created
	createSobel();

	int hX[3][3] = { {-1,-2,-1}, {0,0,0 }, {1,2,1 } };    // horizontal sobel
	int hY[3][3] = { { -1,0,1 }, {-2,0,2}, {-1,0,1} };    // vertical sobel

	// hX and hY hover over image

	int totalX = 0, totalY = 0;
	int value = 0;
	for (int i = 0; i < matrixHeight - 2; i++)
	{
		for (int j = 0; j < matrixWidth - 2; j++)
		{
			for (int a = 0; a < 3; a++)
			{
				for (int b = 0; b < 3; b++)
				{
					totalY += (matrix[i + a][j + b] * hY[a][b]);
					totalX += (matrix[i + a][j + b] * hX[a][b]);
				}
			}
			value = sqrt(pow(totalX, 2) + pow(totalY, 2));
			setSobelMatrix(i, j, value);

			totalX = 0, totalY = 0;
		}
	}
}

int main()
{
	Image I1, I2;
	ifstream File1, File2;

	File1.open("image1.bin", ios::binary);
	File1 >> I1;

	File2.open("image2.bin", ios::binary);
	File2 >> I2;

	I1.sobel();
	I2.sobel();

	I1.threshold(300);
	I2.threshold(200);

	Image I3;
	ofstream File3;
	File3.open("fileout.txt", ios::out);

	// I3 = I1 + I2;
	// I3 = I1 * I2;
	// I3 = !I1;
	I3 = I1;

	File3 << I3;

	return 0;
}
