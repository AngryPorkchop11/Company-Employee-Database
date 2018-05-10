#include "employee.h"
#include "employeeList.h"

class Company
{
public:
	// Constructor for Company, creates dynamic array of *Employee, and has an many elements as specified then sets count to 0
	Company();

	// Adds employee to the list
	bool AddEmployee(unsigned int id, const string& name, double salary, unsigned int managerId = 0);

	// Adds specified employee to the list if it can fit
	bool AddEmployee(const Employee&);

	// Delete an employee via ID
	bool DeleteEmployee(unsigned int);

	// Uses binary search to find employee by ID, returns the position of the employee if found or -1 if not
	int FindById(unsigned int);

	// Uses linear search to find the first occurance of a name, returns the position if found or -1 if not
	int FindByName(const string&, unsigned int = 0);

	// Extracts data from istream and adds employees to the current list of employees, returns the number of employees addeds
	int Read(istream&);

	// Writes all the avialable employees to ostream and returns to number of employees written
	int Write(ostream&);

	// Returns a pointer to the employee in the position specified by the paramater, if position is invalid returns NULL
	Employee* Get(unsigned int);

	// Returns the number of employees in the Company
	unsigned int GetEmployeeCount();

	// Frees the memory by releasing all dynamically created employees in the array
	~Company();
private:
	EmployeeList _list; // Object in charge of storing and managing the list of employees
	int BinarySearch(int); // Executes a binary search on the array with the paramater as the key. Returns the position in the array if foud, or -1 if not found
};