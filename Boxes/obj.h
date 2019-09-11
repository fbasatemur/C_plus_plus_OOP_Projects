class Coord
{
public:
	Coord();
	void setCoord(int, int, int, int);
	int getCoordxstart();
	int getCoordystart();
	int getCoordxend();
	int getCoordyend();

protected:
	int xstart;
	int ystart;
	int xend;
	int yend;
};

class Box :public Coord
{
public:
	Box();
	void setBox(int, int, int, int);	
	int getBoxdensity();
	int getBoxwidth();
	int getBoxheight();
	int getBoxmass();
	bool getRotFlag();
	Box* swap(Box *);
	
protected:
	Coord* coord;
	int density, width, height, mass;	
	bool rotationFlag = false;
};

class Space: public Box
{
public:
	Space(int, int);
	~Space();
	void printmatrix();
	void clearmatrix();
	int randSize(int);
	void fiilRandomBox(int, int, int);
	void putBox();
	int spaceControl(Box *);
	void printBoxCoordinates();
	void printCenterOfMass();
protected:
	int spaceHeight = 0;
	int spaceWidth = 0;
	int spaceTotalBox = 0;
	float spaceXCenter = 0.0;
	float spaceYCenter = 0.0;
	int** matrix;
	Box* boxes;
};