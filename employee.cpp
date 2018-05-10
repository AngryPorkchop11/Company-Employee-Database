#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <cctype>
#include <cstring>

using namespace std;

#include "employee.h"


// Creates an employee using the values given by paramaters. 
Employee::Employee(unsigned int id, const string& name, double salary, unsigned int managerId)
{
	string temp;
	_id = id;
	if (name.length() == 0)
	{
		temp = "***";
		_name = new char[temp.length() + 1];
		strcpy(_name, temp.c_str());
	}
	else {
		_name = new char[name.length() + 1];
		strcpy(_name, name.c_str());
	}
	_salary = salary;
	_managerId = managerId;
}

// Copy constructor for Employee
Employee::Employee(const Employee& employee)
{
	_id = employee._id;

	_name = new char[strlen(employee._name) + 1];
	strcpy(_name, employee._name);

	_salary = employee._salary;
	_managerId = employee._managerId;
}

//Getters
unsigned int Employee::GetId() const
{
	return _id;
}
string Employee::GetName() const
{
	return _name;
}
double Employee::GetSalary() const
{
	return _salary;
}
unsigned int Employee::GetManagerId() const
{
	return _managerId;
}

// Return the string representation of the employee
string Employee::ToString()
{
	stringstream format;

	string name = _name;

	string id = to_string(_id);

	string salary = to_string(_salary);

	string managerId = to_string(_managerId);

	format << "Name: " << setw(10) << setfill(' ') << left << name << "ID: " << setw(5) << setfill(' ') << right << id << left << " " << "Salary: " << setw(10) << setfill(' ') << right << salary << left << " " << "Manager ID: " << setw(5) << setfill(' ') << right << managerId << left;

	return format.str();
}

// Give an rais to an employees current salary
void Employee::Raise(double raise)
{
	_salary += raise;
}

// Returns true if the employee specified by the paramater has the same ID as the current object
bool Employee::Equals(const Employee& employee)
{
	if (employee.GetId() == _id)
	{
		return true;
	}
	return false;
}

// Reads the employee from the istream, return true if successfull and false if not
bool Employee::Read(istream& in)
{
	string name;
	in >> _id >> name >> _salary >> _managerId;
	if (in.fail())
	{
		return false;
	}

	delete[] _name;
	_name = new char[name.length() + 1];
	strcpy(_name, name.c_str());

	return true;
}

// Writes information about an employee, sperated by spaces to the ostream. A final end of line is written
void Employee::Write(ostream& fout)
{
	fout << _id << " " << _name << " " << _salary << " " << _managerId << endl;
}

// Destructor for Employee, releases the memory allocated for the name
Employee::~Employee()
{
	delete[] _name;
}