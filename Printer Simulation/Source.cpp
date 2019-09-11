#include<iostream>
#include<fstream>
#include<string>
#include<time.h>
#include<iomanip>
#include<windows.h>							// color line 
#define FILENAME "Readfile.txt"					// sample source text
#define CAPACITY 7							// sample Queue size -> 7 = 1 cursor + 6 header 

using namespace std;

struct person
{
	string name;
	string surname;
	string nickname;
	string e_mail;
	string birthday;
};
struct date
{
	string year;
	string month;
	string day;
	string hour;
	string minute;
	string second;
};
struct document
{
	string filePath;
	string size;
	unsigned int num_Pages;
	person Person;
	date Date;

};

struct CircularlyNode
{
	document Document;
	CircularlyNode* next;					// next node in the Queue
};


struct CircularlyLinkedList
{
	CircularlyNode* cursor;					// printer's pointer
	CircularlyNode* header;					// to add to the queue

	CircularlyLinkedList();					// constructor
	bool empty() const;						// is Queue empty?

	void add(ifstream& readfile);				// header will add
	void remove();							// cursor to be removed
	void dequeuePrint();					// cursor print
	void enqueuePrint();					// header print

};

void pause(float seconds)
{
	clock_t endtime;
	endtime = clock() + seconds * CLOCKS_PER_SEC;
	while (clock() < endtime)
	{}
}

unsigned int control(ifstream& readfile)				// text lines may be missing
{
	char getchar;							// character of line the end 
	getchar = readfile.peek();
	if (getchar == '\n') { return 0; }
}

unsigned int lineNum(string& Filename)					// how much is text in line ?
{
	ifstream readfile;
	readfile.open(Filename.c_str());

	if (readfile.is_open() == false)
	{
		cout << "File not found !" << endl;
		return 0;
	}
	string getLine;
	unsigned int counter = 1;;
	while (!readfile.eof())
	{
		readfile >> getLine;
		if (!control(readfile))
			counter++;
	}
	readfile.close();
	return counter;										// returns the number of lines in the text
}

bool CircularlyLinkedList::empty() const							// is list empty?
{
	return cursor == NULL;
}


void CircularlyLinkedList::remove()
{																	// remove node cursor
	if (empty())
	{
		cout << "List is empty ! " << endl;
		return;
	};


	CircularlyNode* temp = cursor;									// the node being removed
	cursor = cursor->next;

	if (temp == cursor)
	{
		cursor = NULL;												// Queue is now empty
		header = NULL;
	}

	delete temp;													// delete the old cursor
}

CircularlyLinkedList::CircularlyLinkedList()						// constructor
{
	cursor = NULL;
	header = NULL;
}


CircularlyNode* Fileread(ifstream& readfile, CircularlyNode* v)
{

	readfile >> v->Document.filePath;
	if (control(readfile)) readfile >> v->Document.size;
	if (control(readfile)) readfile >> v->Document.num_Pages;
	if (control(readfile)) readfile >> v->Document.Person.name;
	if (control(readfile)) readfile >> v->Document.Person.surname;
	if (control(readfile)) readfile >> v->Document.Person.nickname;
	if (control(readfile)) readfile >> v->Document.Person.e_mail;
	if (control(readfile)) readfile >> v->Document.Person.birthday;
	if (control(readfile)) readfile >> v->Document.Date.year;
	if (control(readfile)) readfile >> v->Document.Date.month;
	if (control(readfile)) readfile >> v->Document.Date.day;
	if (control(readfile)) readfile >> v->Document.Date.hour;
	if (control(readfile)) readfile >> v->Document.Date.minute;
	if (control(readfile)) readfile >> v->Document.Date.second;

	return v;
}

void CircularlyLinkedList::add(ifstream& readfile)
{														// add after header
	CircularlyNode* v = new CircularlyNode;				// create a new node
	v = Fileread(readfile, v);

	if (cursor == NULL)
	{													// Queue is empty?
		v->next = v;									// v points to itself
		cursor = v;										// cursor points to v
		header = v;
	}
	else
	{													// Queue is nonempty?
		v->next = header->next;							// link in v after header
		header->next = v;
		header = header->next;
	}

}

void CircularlyLinkedList::dequeuePrint()
{
	if (empty())										//is Queue empty ?
	{
		cout << " Queue is empty ! " << endl;
		return;
	};
	HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);				// for color line 
	SetConsoleTextAttribute(hStdout, FOREGROUND_GREEN);				// red line
	cout << clock() / 1000 << "th seconds printer wrote this file - " << setw(36) << cursor->Document.filePath << '(' << cursor->Document.num_Pages << ')' << endl;
	SetConsoleTextAttribute(hStdout, FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_RED);		// try white line
}

struct CircularlyLinkedQueue
{
	CircularlyLinkedList C;
	unsigned int n;									// number of nodes

	CircularlyLinkedQueue();
	int size() const;
	bool empty() const;
	void enqueue(ifstream& readfile);
	void dequeue();
};

CircularlyLinkedQueue::CircularlyLinkedQueue()		// constructor
{
	n = 0;
}

int CircularlyLinkedQueue::size() const				// number of items in the queue
{
	return n;
}

bool CircularlyLinkedQueue::empty() const			// is the queue empty?
{
	return n == 0;
}

void CircularlyLinkedQueue::enqueue(ifstream& readfile)
{
	C.add(readfile);										// insert after header
	n++;													// number of nodes increases
}
void CircularlyLinkedList::enqueuePrint()
{
	HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);		// for color line
	SetConsoleTextAttribute(hStdout, FOREGROUND_BLUE);		// blue line
	cout << clock() / 1000 << "th seconds added to the queue, next file ->" << setw(30) << header->Document.filePath << '(' << header->Document.num_Pages << ')' << endl;
	SetConsoleTextAttribute(hStdout, FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_RED);		// try white line
}

void CircularlyLinkedQueue::dequeue()
{
	if (empty())
	{
		cout << "dequeuing of empty queue !" << endl;
		return;
	}

	C.remove();										// remove node
	n--;											// number of nodes decreases
}

int main()
{
	string Filename = FILENAME;
	unsigned int addfast, printfast;

	do {
		cout << "Queue insertion time:";
		cin >> addfast;
		cout << "The printer takes one page to write:";
		cin >> printfast;
	} while (addfast <= 0 || printfast <= 0);

	unsigned int documentSize = lineNum(Filename);		// file amount

	HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);	// for color line

	ifstream readfile;
	readfile.open(Filename.c_str());

	CircularlyLinkedQueue Queue;

	float QueueTime = 0.0;			//time of Queue add
	float PrintTime = 0.0;			//time of print

	unsigned int nodeSum = 0;		//number of nodes add
	unsigned int counter = 0;		//number of loop
	do
	{

		if (counter == 0)
		{
			Queue.enqueue(readfile);
			nodeSum++;
			QueueTime = Queue.C.header->Document.num_Pages * addfast;
			cout << "Time:" << clock() / 1000 << " Adding to queue -> " << setw(48) << Queue.C.header->Document.filePath << '(' << Queue.C.header->Document.num_Pages << ')' << endl;
		}

		else
		{
			if (counter == int(QueueTime) && Queue.size() < CAPACITY && nodeSum < documentSize)
			{
				Queue.enqueue(readfile);
				nodeSum++;
				QueueTime = float(Queue.C.header->Document.num_Pages * addfast) + QueueTime;
				Queue.C.enqueuePrint();
			}
		}

		if (counter == int(QueueTime) && Queue.size() == CAPACITY && nodeSum < documentSize)
		{
			SetConsoleTextAttribute(hStdout, FOREGROUND_RED);
			cout << clock() / 1000 << "th seconds Queue full, " << "could not be added -> " << setw(28) << Queue.C.header->Document.filePath << '(' << Queue.C.header->Document.num_Pages << ')' << endl;
			SetConsoleTextAttribute(hStdout, FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED);
			QueueTime = float(Queue.C.header->Document.num_Pages * addfast) + QueueTime;
		}

		if (counter == 0)
		{
			PrintTime = (Queue.C.cursor->Document.num_Pages * printfast);
		}

		else
		{
			if (counter == int(PrintTime))
			{
				Queue.C.dequeuePrint();
				Queue.dequeue();
				PrintTime = (Queue.C.cursor->Document.num_Pages * printfast) + PrintTime;
			}
		}
		counter++;
		pause(1);

	} while (Queue.size() > 0);

	cout << "Queue empty, all files printed." << endl;

	system("pause");

	return 0;
}