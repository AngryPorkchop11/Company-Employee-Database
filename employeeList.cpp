#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>
#include <cctype>


using namespace std;

#include "employeeList.h"


// Initalizes _head to NULL and _size to 0
EmployeeList::EmployeeList()
{
	_head = NULL;
	_size = 0;
}

// Calls DestroyList
EmployeeList::~EmployeeList()
{
	DestroyList();
}

// Insert Employee* into correct spot in list (sort by ID), allocate a node to the Employee*. If list is empty, set Employee* to _head and point to its self in both directions
bool EmployeeList::Insert(Employee* other)
{
	// Allocate a new node and fill data with current object 
	Node *ptrNew = new Node;
	ptrNew->data = other;
	// If the list is empty
	if (IsEmpty() == true)
	{
		_head = ptrNew;
		_head->next = NULL;
		_head->prev = NULL;
		_size++;
		return true;
	}	
	// Insert at beginning of list
	if (_head->data->GetId() > ptrNew->data->GetId())
	{
		ptrNew->next = _head;
		ptrNew->prev = NULL;
		_head->prev = ptrNew;
		_head = ptrNew;
		_size++;
		return true;
	}
	Node *ptr = _head;
	Node *run = _head;
	while(ptr)
	{
		// Insert between
		if (ptr->data->GetId() > ptrNew->data->GetId())
		{
			ptrNew->next = ptr;
			ptrNew->prev = ptr->prev;
			ptr->prev = ptrNew;
			ptrNew->prev->next = ptrNew;

			_size++;
			return true;
 		}
		run = ptr;
		ptr = ptr->next;
	}
	// Insert at end
	ptrNew->prev = run;
	ptrNew->next = NULL;
	run->next = ptrNew;
	_size++;
	return true;
}

// Returns a pointer to the Employee object stored in the position given by the paramater. If the position in invalid method returns NULL 
Employee* EmployeeList::Get(unsigned int pos)
{
	int count = 0;
	Node *ptr = _head;

	// loop through list to find pos
	if (pos <= _size)
	{
		while (ptr)
		{
			if (count == pos)
			{
				return ptr->data;
			}
			ptr = ptr->next;
			count++;
		}
	}
	return NULL;
}

// Searches for the node that stores an Employee that is = to the Employee passed into the method. Returs the position of the node found or -1
int EmployeeList::IndexOf(const Employee& other)
{
	int count = 0;
	Node *ptr = _head;
	while (ptr)
	{
		if (ptr->data->GetId() == other.GetId(  ))
		{
			return count;
		}
		ptr = ptr->next;
		count++;
	}
	return -1;
}

// Removes the node from the list at the position in the paramater. If the position is invalid returns false. If not, the node is un-hooked from the list, the node and Employee* are 
// deallocated and _size is updated
bool EmployeeList::Remove(unsigned int pos)
{
	int count = 0;
	Node *ptr = _head;
	Node *run = _head;
	// Check for empty list
	if (_size == 0)
	{
		return false;
	}
	// Validate the pos
	if (pos > _size)
	{
		return false;
	}
	// If only one element
	if (_size == 1)
	{
		delete ptr;
		_head = NULL;
		_size--;
		return true;
	}
	// Remove from front
	if (pos == 0)
	{
		ptr->next->prev = NULL; 
		_head = ptr->next;
		delete ptr;
		_size--;
		return true;
	}
	// Remove in between
	while (ptr)
	{
		if (count == pos && count != _size -1)
		{
			ptr->prev->next = ptr->next;
			ptr->next->prev = ptr->prev;
			delete ptr;
			_size--;
			return true;
		}
		run = ptr;
		ptr = ptr->next;
		count++;
	}
	// Remove at end
		run->next = NULL;
		delete ptr;
		_size--;
		return true;
}

// Writes all Employees to ostream and returns a count
int EmployeeList::Write(ostream& out)
{
	int count = 0;
	Node *ptr =_head;
	while (ptr)
	{
		ptr->data->Write(out);
		ptr = ptr->next;
		count++;
	}
	return count;
}

// Reads all Employee data from istream. As Employees are read they are inserted into the sorted list and returns a cont of Employees
int EmployeeList::Read(istream& in)
{
	while (!in.eof())
	{
		Employee *temp;
		temp = new Employee(0, "", 0.0, 0);

		if (temp->Read(in) == true)
		{
			Insert(temp);
		}
	}
	return _size;
}

// Returs true if there are no nodes in the list, false otherwise 
bool EmployeeList::IsEmpty()
{
	if (Size() == 0)
		return true;
	return false;
}

// Returns the number of nodes in the list
unsigned int EmployeeList::Size()
{
	return _size;
}

// Uses delete to free up every node in the list, the Employee object it points to is also freed
void EmployeeList::DestroyList()
{
	Node *ptr = _head;
	Node *run = _head;
	while (ptr)
	{
		run = ptr->next;
		delete ptr;
		ptr = run;
	}
	delete run;
}