#ifndef _EMPLOYEE
#define _EMPLOYEE

class Employee
{
	//	friend class Company;
public:
	// Creates an employee using the values given by paramaters. 
	Employee(unsigned int id, const string& name, double salary, unsigned int managerId = 0);

	// Copy constructor for Employee
	Employee(const Employee& employee);

	//Getters
	unsigned int GetId() const;
	string GetName() const;
	double GetSalary() const;
	unsigned int GetManagerId() const;

	// Return the string representation of the employee
	string ToString();

	// Give an rais to an employees current salary
	void Raise(double);

	// Returns true if the employee specified by the paramater has the same ID as the current object
	bool Equals(const Employee&);

	// Reads the employee from the istream, return true if successfull and false if not
	bool Read(istream&);

	// Writes information about an employee, sperated by spaces to the ostream. A final end of line is written
	void Write(ostream&);

	// Destructor
	~Employee();
private:
	unsigned int _id; // ID
	char *_name; // Name
	double _salary; // Salary
	unsigned int _managerId; // ID of manager, if the employee does not have one the value will be 0
};
#endif