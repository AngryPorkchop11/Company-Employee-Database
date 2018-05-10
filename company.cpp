#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>
#include <cctype>


using namespace std;

#include "company.h"

// Constructor for Company
Company::Company()
{
}

// Adds employee to the list
bool Company::AddEmployee(unsigned int id, const string& name, double salary, unsigned int managerId)
{
	Employee *tempEmp;
	tempEmp = new Employee(id, name, salary, managerId);
	if(_list.Insert(tempEmp) == true)
	{
			return true;
	}
	return false;
}

// Adds specified employee to the list if it can fit
bool Company::AddEmployee(const Employee& employee)
{
	Employee *tempEmp;
	tempEmp = new Employee(employee);
	if (_list.Insert(tempEmp) == true)
		return true;
	return false;
}

// Delete an employee via ID
bool Company::DeleteEmployee(unsigned int id)
{
	// Check if ID exits
	if (BinarySearch(id) == -1)
	{
		return false;
	}
	// Check if employee is a manager
	int pos = FindById(id);
	int i = 0;
	while(i < _list.Size())
	{
		if (id == _list.Get(i)->GetManagerId())
		{
			return false;
		}
		i++;
	}
	
	// Delete the employee specified by ID
	_list.Remove(pos);
	return true;
}

// Uses binary search to find employee by ID, returns the position of the employee if found or -1 if not
int Company::FindById(unsigned int id)
{
	return BinarySearch(id);
}

// Uses linear search to find the first occurance of a name, returns the position if found or -1 if not
int Company::FindByName(const string& name, unsigned int pos)
{
	for (pos; pos < _list.Size(); pos++)
	{
		if (name == _list.Get(pos)->GetName())
		{
			return pos;
		}
	}
	return -1;
}

// Extracts data from istream and adds employees to the current list of employees, returns the number of employees added
int Company::Read(istream& in)
{
	return _list.Read(in);
}

// Writes all the avialable employees to ostream and returns to number of employees written
int Company::Write(ostream& fout)
{
	return _list.Write(fout);
}


// Returns a pointer to the employee in the position specified by the paramater, if position is invalid returns NULL
Employee* Company::Get(unsigned int pos)
{
	return _list.Get(pos);
}

// Returns the number of employees in the Company
unsigned int Company::GetEmployeeCount()
{
	return _list.Size();
}

// Executes a binary search on the array with the paramater as the key. Returns the position in the array if foud, or -1 if not found
int Company::BinarySearch(int key)
{
	int first = 0;
	int one = 1;
	int last = _list.Size() - one;

	while (first <= last)
	{
		int mid = (first + last) / 2;

		if (key < _list.Get(mid)->GetId())
		{
			last = mid - 1;
		}
		else if (key > _list.Get(mid)->GetId())
		{
			first = mid + 1;
		}
		else
		{
			return mid;
		}
	}
	return -1;
}

// Destructor for Company
Company::~Company()
{
}
