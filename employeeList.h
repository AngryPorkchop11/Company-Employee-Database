#ifndef _EMPLOYEELIST
#define _EMPLOYEELIST


#include "employee.h"

class EmployeeList
{
public:
	// Initalizes _head to NULL and _size to 0
	EmployeeList();

	// Calls DestroyList
	~EmployeeList();

	// Insert Employee* into correct spot in list (sort by ID), allocate a node to the Employee*. If list is empty, set Employee* to _head and point to its self in both directions
	bool Insert(Employee*);

	// Returns a pointer to the Employee object stored in the position given by the paramater. If the position in invalid method returns NULL 
	Employee* Get(unsigned int);

	// Searches for the node that stores an Employee that is = to the Employee passed into the method. Returs the position of the node found or -1
	int IndexOf(const Employee&);

	// Removes the node from the list at the position in the paramater. If the position is invalid returns false. If not, the node is un-hooked from the list, the node and Employee* are 
	// deallocated and _size is updated
	bool Remove(unsigned int);

	// Writes all Employees to ostream and returns a count
	int Write(ostream&);

	// Reads all Employee data from istream. As Employees are read they are inserted into the sorted list and returns a cont of Employees
	int Read(istream&);

	// Returs true if there are no nodes in the list, false otherwise 
	bool IsEmpty();

	// Returns the number of nodes in the list
	unsigned int Size();
private:
	// Structures the chain links in the list. Everytime a new Employee is created a new Node will also need to be created	
	struct Node
	{
		Employee *data;
		Node* next;
		Node* prev;
	};

	// Points to the first node in the list, NULL if list is empty
	Node* _head;

	// Number of nodes in the list
	unsigned int _size;

	// Uses delete to free up every node in the list, the Employee object it points to is also freed
	void DestroyList();
};
#endif