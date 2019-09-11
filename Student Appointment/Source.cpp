#include <iostream>
#include <fstream>
#include <string.h>
#include <stdlib.h>
#include <vector>

#define STUDENTFILE     "Student.txt"
#define ACADEMICIANFILE "Academician.txt"
#define APPOINTMENTFILE "Appointment.txt"

using namespace std;
class appointment
{
public:
	// setAppoinment Overloaded

	void setAppointment(long int, long int, string, string, string);	// parameters are placed

	void setAppointment(long int, long int, string, string);			// corrections for endTime = startTime +  10

	long int getNumber();
	long int getregistrationNumber();
	string getDate();
	string getstartTime();
	string getfinishTime();
private:
	long int number;
	long int registrationNumber;
	string date;                        // appointment date
	string startTime;                   // appointment start time
	string endTime;                     // appointment end time
	char endTimeArry[5];
};
class person
{
public:
	void setPerson(string, string, string, string);       // name, surname, e-Mail, phoneNum

	string getname();
	string getSurname();
	string getePost();
	string getPhoneNum();
protected:
	string name;                        // person name
	string surname;                     // person surname
	string eMail;                       // personel e-Mail Adress
	string phoneNum;                    // personel phone number
};
class academician : public person
{
public:
	void setAcademician(long int, string, string);     // registrationNumber, department, title

	long int getRegistrationNumber();
	string getDepartment();
	string getTitle();

protected:
	long int registrationNumber;   // Academician Registration Number
	string department;             // Academician Department
	string title;                  // Academician Title
};
class student : public person
{
public:
	void setStudent(long int, string, string);     // number, branch, registration

	long int getNumber();
	string getChapter();
	string getRegistration();
protected:
	long int number;            // Student Number
	string branch;				// Student branch
	string registration;        // date of registration
};
class Derived : public student, academician, appointment
{
protected:
	academician aca[100];
	student stu[100];
	appointment app[100];
	int academicianTotal;
	int studentTotal;
	int appointmentTotal;
	string name;					  // buffer variables
	string surname;
	string eMail;
	string phoneNum;
	long int registrationNumber;
	string department;
	string title;
	long int number;
	string branch;
	string registration;
	string date;
	string startTime;
	string endTime;
public:
	Derived();

	void Control(int);
	int readFile(string);              // called in constructor and reads data from text file
	void printFile(string);            // called in destructor and write data to text file

	int addStudent();
	int addAcademician();
	int addAppointment();
	int AppointmentControl();           // checks when adding an appointment

	long int* sorter(long int*, int);   // insertion sort
	void listStudent();
	void listAcademician();
	void listAppointment();

	int stuUpdate();
	int acaUpdate();
	int appUpdate();

	int delStudent();
	int delAcademician();
	int delAppointment();

	~Derived();
};

void appointment::setAppointment(long int number, long int registrationNumber, string date, string startTime, string endTime)
{
	this->number = number;
	this->registrationNumber = registrationNumber;
	this->date = date;
	this->startTime = startTime;
	this->endTime = endTime;

}
void appointment::setAppointment(long int number, long int registrationNumber, string date, string startTime)
{
	this->number = number;
	this->registrationNumber = registrationNumber;
	this->date = date;
	this->startTime = startTime;

	strcpy_s(endTimeArry, startTime.c_str());

	if (endTimeArry[3] == '5')
	{
		switch (endTimeArry[1])
		{
		case '8':
			this->endTimeArry[1] = '9';
			this->endTimeArry[3] = '0';
			break;
		case '9':
			this->endTimeArry[1] = '0';
			this->endTimeArry[0] = '1';
			this->endTimeArry[3] = '0';
			break;
		case '0':
			this->endTimeArry[1] = '1';
			this->endTimeArry[3] = '0';
			break;
		case '1':
			this->endTimeArry[1] = '2';
			this->endTimeArry[3] = '0';
			break;
		case '2':
			this->endTimeArry[1] = '3';
			this->endTimeArry[3] = '0';
			break;
		case '3':
			this->endTimeArry[1] = '4';
			this->endTimeArry[3] = '0';
			break;
		case '4':
			this->endTimeArry[1] = '5';
			this->endTimeArry[3] = '0';
			break;
		case '5':
			this->endTimeArry[1] = '6';
			this->endTimeArry[3] = '0';
			break;
		case '6':
			this->endTimeArry[1] = '7';       // 17:0* end time
			this->endTimeArry[3] = '0';
			break;
		default:
			break;
		}
	}
	else
	{
		switch (endTimeArry[3])
		{
		case '0':
			this->endTimeArry[3] = '1';
			break;
		case '1':
			this->endTimeArry[3] = '2';
			break;
		case '2':
			this->endTimeArry[3] = '3';
			break;
		case '3':
			this->endTimeArry[3] = '4';
			break;
		case '4':
			this->endTimeArry[3] = '5';
			break;
		default:
			break;
		}
	}
	string newfinishTime;
	for (int i = 0; i < 5; i++)
		newfinishTime += endTimeArry[i];

	this->endTime = newfinishTime;
}
long int appointment::getNumber()
{
	return number;
}
long int appointment::getregistrationNumber()
{
	return registrationNumber;
}
string appointment::getDate()
{
	return date;
}
string appointment::getstartTime()
{
	return startTime;
}
string appointment::getfinishTime()
{
	return endTime;
}


string person::getname()
{
	return name;
}
string person::getSurname()
{
	return surname;
}
string person::getePost()
{
	return eMail;
}
string person::getPhoneNum()
{
	return phoneNum;
}
void person::setPerson(string name, string surname, string eMail, string phoneNum)
{
	this->name = name;
	this->surname = surname;
	this->eMail = eMail;
	this->phoneNum = phoneNum;
}


long int academician::getRegistrationNumber()
{
	return registrationNumber;
}
string academician::getDepartment()
{
	return department;
}
string academician::getTitle()
{
	return title;
}
void academician::setAcademician(long int registrationNumber, string department, string title)
{
	this->registrationNumber = registrationNumber;
	this->department = department;
	this->title = title;
}


void student::setStudent(long int number, string branch, string registration)
{
	this->number = number;
	this->branch = branch;
	this->registration = registration;
}
long int student::getNumber()
{
	return number;
}
string student::getChapter()
{
	return branch;
}
string student::getRegistration()
{
	return registration;
}


Derived::Derived()
{
	studentTotal = readFile(STUDENTFILE);
	academicianTotal = readFile(ACADEMICIANFILE);
	appointmentTotal = readFile(APPOINTMENTFILE);

	cout << "[1]  Add Students " << endl
		<< "[2]  List Students " << endl
		<< "[3]  Delete Students " << endl
		<< "[4]  Update Students " << endl
		<< "[5]  Add Academician  " << endl
		<< "[6]  List Academician  " << endl
		<< "[7]  Delete Academician  " << endl
		<< "[8]  Update Academician  " << endl
		<< "[9]  Add Appointment " << endl
		<< "[10] List Appointment " << endl
		<< "[11] Delete Appointment " << endl
		<< "[12] Update Appointment " << endl
		<< "[0]  Exit and Save !" << endl;
}

Derived::~Derived()
{
	printFile(ACADEMICIANFILE);
	printFile(STUDENTFILE);
	printFile(APPOINTMENTFILE);
}

void Derived::printFile(string fileName)
{
	// write to file

	ofstream outfile;

	outfile.open(fileName.c_str(), ios::out);

	if (fileName == STUDENTFILE)
	{
		for (int index = 0; index < studentTotal; index++)
		{
			outfile << stu[index].getNumber() << " " << stu[index].getname() << " "
				<< stu[index].getSurname() << " " << stu[index].getChapter() << " "
				<< stu[index].getRegistration() << " " << stu[index].getePost() << " "
				<< stu[index].getPhoneNum() << endl;
		}
	}
	else if (fileName == ACADEMICIANFILE)
	{
		for (int index = 0; index < academicianTotal; index++)
		{
			outfile << aca[index].getRegistrationNumber() << " " << aca[index].getname() << " "
				<< aca[index].getSurname() << " " << aca[index].getDepartment() << " "
				<< aca[index].getePost() << " " << aca[index].getPhoneNum() << " "
				<< aca[index].getTitle() << endl;
		}
	}
	else
		for (int index = 0; index < appointmentTotal; index++)
		{
			outfile << app[index].getNumber() << " " << app[index].getregistrationNumber() << " "
				<< app[index].getDate() << " " << app[index].getstartTime() << " "
				<< app[index].getfinishTime() << endl;
		}

	outfile.close();
}

int Derived::readFile(string fileName)
{
	// read data from file

	ifstream infile(fileName.c_str(), ios::app | ios::in);
	if (infile.is_open())
	{
		int i = 0;
		for (; !infile.eof() && fileName == STUDENTFILE; i++)
		{
			infile >> number;
			infile >> name;
			infile >> surname;
			infile >> branch;
			infile >> registration;
			infile >> eMail;
			infile >> phoneNum;
			stu[i].setPerson(name, surname, eMail, phoneNum);
			stu[i].setStudent(number, branch, registration);
		}

		for (; !infile.eof() && fileName == ACADEMICIANFILE; i++)
		{
			infile >> registrationNumber;
			infile >> name;
			infile >> surname;
			infile >> department;
			infile >> eMail;
			infile >> phoneNum;
			infile >> title;
			aca[i].setPerson(name, surname, eMail, phoneNum);
			aca[i].setAcademician(registrationNumber, department, title);
		}

		for (; !infile.eof() && fileName == APPOINTMENTFILE; i++)
		{
			infile >> number;
			infile >> registrationNumber;
			infile >> date;
			infile >> startTime;
			infile >> endTime;

			app[i].setAppointment(number, registrationNumber, date, startTime, endTime);
		}

		infile.close();
		return i - 1;
	}
	else
	{
		cout << "Unable to open file !" << endl;
		return 0;
	}
}

long int* Derived::sorter(long int* p, int i)
{
	long int temp;
	long int min;

	for (int index = 0; index < i; index++)
	{
		min = index;
		for (int j = index; j < i; j++)
		{
			if (p[j] < p[min])
				min = j;
		}
		temp = p[index];
		p[index] = p[min];
		p[min] = temp;
	}
	return p;
}

void Derived::listAcademician()
{
	long int* sortArray = new long int[academicianTotal];

	for (int index = 0; index < academicianTotal; index++)
	{
		sortArray[index] = aca[index].getRegistrationNumber();
	}

	long int* p = sorter(sortArray, academicianTotal);  // sorted array is transferred

	for (int a = 0; a < academicianTotal; a++)
	{
		for (int j = 0; j < academicianTotal; j++)
		{
			if (p[a] == aca[j].getRegistrationNumber())
			{
				cout << aca[j].getRegistrationNumber() << " " << aca[j].getname() << " "
					<< aca[j].getSurname() << " " << aca[j].getDepartment() << " "
					<< aca[j].getePost() << " " << aca[j].getPhoneNum() << " "
					<< aca[j].getTitle() << endl;
			}
		}
	}

};

void Derived::listStudent()
{
	long int* sortArray = new long int[studentTotal];

	for (int a = 0; a < studentTotal; a++)
	{
		sortArray[a] = stu[a].getNumber();
	}

	long int* p = sorter(sortArray, studentTotal);      // sorted array is transferred

	for (int a = 0; a < studentTotal; a++)
	{
		for (int j = 0; j < studentTotal; j++)
		{
			if (p[a] == stu[j].getNumber())
			{
				cout << stu[j].getNumber() << " " << stu[j].getname() << " " << stu[j].getSurname() << " "
					<< stu[j].getChapter() << " " << stu[j].getRegistration() << " "
					<< stu[j].getePost() << " " << stu[j].getPhoneNum() << endl;
			}
		}
	}
}
int Derived::stuUpdate()
{
	cout << "Student Number :";
	cin >> number;
	int a = 0;
	for (; a < studentTotal; a++)
	{
		if (stu[a].getNumber() == number)
			break;
		else if (a + 1 == studentTotal)
			return 0;
	}
	cout << "Name:";
	cin >> name;
	cout << "Surname:";
	cin >> surname;
	cout << "E-Mail Adress:";
	cin >> eMail;
	cout << "Phone number:";
	cin >> phoneNum;
	cout << "Branch:";
	cin >> branch;
	cout << "Date of Registration:";
	cin >> registration;

	stu[a].setPerson(name, surname, eMail, phoneNum);
	stu[a].setStudent(number, branch, registration);

	return 1;
}
int Derived::acaUpdate()
{
	cout << "Academician registration number:";
	cin >> registrationNumber;
	int index = 0;
	for (; index < academicianTotal; index++)        // Academician control
	{
		if (aca[index].getRegistrationNumber() == registrationNumber)
			break;
		else if (index + 1 == academicianTotal)
			return 0;
	}
	cout << "Name:";
	cin >> name;
	cout << "Surname:";
	cin >> surname;
	cout << "E-Mail:";
	cin >> eMail;
	cout << "Phone Number:";
	cin >> phoneNum;
	cout << "Department:";
	cin >> department;
	cout << "Title:";
	cin >> title;

	aca[index].setPerson(name, surname, eMail, phoneNum);
	aca[index].setAcademician(registrationNumber, department, title);

	return 1;
}
int Derived::appUpdate()
{
	cout << "Student Number:";
	cin >> number;
	cout << "Academician Registration Number:";
	cin >> registrationNumber;
	cout << "Date:";
	cin >> date;
	cout << "Start time:";
	cin >> startTime;
	int a = 0;
	for (; a < appointmentTotal; a++)
	{
		if (registrationNumber == app[a].getregistrationNumber() && number == app[a].getNumber())
			break;
	}

	if (AppointmentControl())
	{
	}
	else
		return 0;

	app[a].setAppointment(number, registrationNumber, date, startTime);

	return 1;
}
int Derived::addAcademician()
{
	cout << "Academician Registration Number:";
	cin >> registrationNumber;

	for (int a = 0; a < academicianTotal; a++)
	{
		if (registrationNumber == aca[a].getRegistrationNumber())
		{
			cout << "The academician is on the list !" << endl;
			return 0;
		}
	}
	cout << "Name:";
	cin >> name;
	cout << "Surname:";
	cin >> surname;
	cout << "E-Mail:";
	cin >> eMail;
	cout << "Phone Number:";
	cin >> phoneNum;
	cout << "Department:";
	cin >> department;
	cout << "Title:";
	cin >> title;

	aca[academicianTotal].setPerson(name, surname, eMail, phoneNum);
	aca[academicianTotal].setAcademician(registrationNumber, department, title);

	academicianTotal++;
	return 1;

}
int Derived::addStudent()
{
	cout << "Student Number:";
	cin >> number;
	for (int a = 0; a < studentTotal; a++)
	{
		if (number == stu[a].getNumber())
		{
			cout << "The student is on the list !" << endl;
			return 0;
		}
	}
	cout << "Name:";
	cin >> name;
	cout << "Surname:";
	cin >> surname;
	cout << "E-Mail:";
	cin >> eMail;
	cout << "Phone Number:";
	cin >> phoneNum;
	cout << "Branch:";
	cin >> branch;
	cout << "Registration Date:";
	cin >> registration;

	stu[studentTotal].setPerson(name, surname, eMail, phoneNum);
	stu[studentTotal].setStudent(number, branch, registration);

	studentTotal++;

	return 1;

}
int Derived::delAcademician()
{
	cout << "Academician Registration Number:";
	cin >> registrationNumber;
	int a = 0;
	for (; a < academicianTotal; a++)
	{
		if (aca[a].getRegistrationNumber() == registrationNumber)
			break;
		else if (a + 1 == academicianTotal)
			return 0;
	}
	academicianTotal--;
	for (; a < academicianTotal; a++)
	{
		aca[a] = aca[a + 1];
	}
	return 1;
}
int Derived::delStudent()
{
	cout << "Student Number:";
	cin >> number;
	int a = 0;
	for (; a < studentTotal; a++)
	{
		if (stu[a].getNumber() == number)
			break;
		else if (a + 1 == studentTotal)
			return 0;
	}
	studentTotal--;
	for (; a < studentTotal; a++)
	{
		stu[a] = stu[a + 1];
	}
	return 1;
}
int Derived::delAppointment()
{
	cout << "Student Number";
	cin >> number;
	cout << "Academician Registration Number:";
	cin >> registrationNumber;
	int a = 0;
	for (; a < appointmentTotal; a++)          // student number and registration number control
	{
		if (app[a].getNumber() == number && app[a].getregistrationNumber() == registrationNumber)
			break;
		else if (a + 1 == appointmentTotal)
			return 0;
	}
	appointmentTotal--;
	for (; a < appointmentTotal; a++)
	{
		app[a] = app[a + 1];
	}
	return 1;
}
int Derived::addAppointment()
{
	cout << "Student number:";
	cin >> number;
	cout << "Academician Registration Number:";
	cin >> registrationNumber;

	for (int index = 0; index < appointmentTotal; index++)                  // appointment control
	{
		if (number == app[index].getNumber() && registrationNumber == app[index].getregistrationNumber())
		{
			cout << "This appointment is listed !" << endl;
			return 0;
		}
	}

	cout << "Date:";
	cin >> date;
	cout << "Start Time:";
	cin >> startTime;

	if (AppointmentControl())
	{
		app[appointmentTotal].setAppointment(number, registrationNumber, date, startTime);

		appointmentTotal++;
		return 1;
	}
	else
		return 0;
}
void Derived::listAppointment()
{

	for (int index = 0; index < appointmentTotal; index++)
	{
		cout << app[index].getNumber() << " " << app[index].getregistrationNumber() << " " << app[index].getDate() << " "
			<< app[index].getstartTime() << " " << app[index].getfinishTime() << endl;
	}
}
int Derived::AppointmentControl()
{
	bool flag1 = false, flag2 = false;

	for (int index = 0; index < studentTotal; index++)                  // student control
	{
		if (number == stu[index].getNumber())
		{
			flag1 = true;
		}
	}
	for (int index = 0; index < academicianTotal; index++)              // academician control
	{
		if (registrationNumber == aca[index].getRegistrationNumber())
		{
			flag2 = true;
		}
	}
	if (flag1 == false || flag2 == false)
	{
		cout << "This student or academician was not listed !" << endl;
		return 0;
	}


	for (int i = 0; i < appointmentTotal; i++)                // Are academics available ?
	{
		if (app[i].getDate() == date && app[i].getregistrationNumber() == registrationNumber && app[i].getstartTime() == startTime)
		{
			cout << "Academician is not available !" << endl;
			return 0;
		}
	}
	char newstartTime[5];
	strcpy_s(newstartTime, startTime.c_str());

	if (newstartTime[0] == '0' && newstartTime[1] >= '8')        // is the time available ? (08:00-16:59)
	{
	}
	else if (newstartTime[0] == '1' && newstartTime[1] <= '6' && newstartTime[3] <= '5' && newstartTime[4] <= '9')
	{
	}
	else
	{
		cout << "Academician is not working hours !" << endl;
		return 0;
	}
	return 1;
}
void Derived::Control(int choice)
{

	switch (choice)
	{
	case 0:
		// exit and save !
		break;
	case 1:

		if (addStudent())
			cout << "Student successfully added. " << endl;
		else
			cout << "Failed to add student !" << endl;
		break;
	case 2:

		listStudent();
		break;
	case 3:

		if (delStudent())
			cout << "Student successfully delete." << endl;
		else
			cout << "Student not found in list !" << endl;
		break;
	case 4:

		if (stuUpdate())
			cout << "Student successfully updated. " << endl;
		else
			cout << "Student not found in list !" << endl;
		break;
	case 5:

		if (addAcademician())
			cout << "Academician successfully added." << endl;
		else
			cout << "Failed to add academician !" << endl;
		break;
	case 6:

		listAcademician();
		break;
	case 7:

		if (delAcademician())
			cout << "Academician is deleted." << endl;
		else
			cout << "Academician not found in list !" << endl;
		break;
	case 8:

		if (acaUpdate())
			cout << "Academician successfully updated. " << endl;
		else
			cout << "Academician not found in list !" << endl;
		break;
	case 9:

		if (addAppointment())
			cout << "Appointment successfully added." << endl;
		else
			cout << "Failed to add appointment !" << endl;
		break;
	case 10:

		listAppointment();
		break;
	case 11:

		if (delAppointment())
			cout << "Appointment successfully deleted." << endl;
		else
			cout << "Appointment not found in list !" << endl;
		break;

	case 12:

		if (appUpdate())
			cout << "Appointment successfully Updeted." << endl;
		else
			cout << "Appointment update failed !" << endl;
		break;
	default:

		cout << "Enter appropriate value !" << endl;
		break;

	}

}
int main()
{
	Derived d;
	int input;

	do
	{
		cout << "Choice:";
		cin >> input;
		d.Control(input);
	} while (input != 0);

	return 0;
}


