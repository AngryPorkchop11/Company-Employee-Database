// Title: Company Employee Database
//
// Purpose: Create a database of employees and give the user the option to write the database to a file, display all employees, search by name / ID, find boss info, add employees,
//
// **Addition: Anytime the program runs into an error (bad input from user, or unable to find/add/delete something) that error message will appear in red. Anytime the program prints employee information that text will be in blue.**
// **Testing: Start program, option 1, enter garbage (error message should be in red). Start program, load company1.dat, choose option three (output of employee info should be in blue)**
// 2018
// Author: Mathew Lister

#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>
#include <cctype>
#include <assert.h>
#include <Windows.h> // **For color in console window**

using namespace std;

#include "employee.h"
#include "company.h"

//Function to validate user input for switch case
bool ValidOption(const int choice);
// Function to validate user input for ID search
bool ValidId(const int id);
// Function to validate a raise 
bool ValidRaise(const double raise);
// Function to validate user input for AddEmployee
bool ValidAdd(const unsigned int id, const double salary, const unsigned int bossId);
int main()
{
	// Variables needed for main
	Company *tempComp = NULL;
	ifstream fin;
	string fileNameR;
	string fileNameW;
	string menu = "1. Load a Company File\n2. Save Company Data to File\n3. List all Employees\n4. Search by Name\n5. Search by ID\n6. Find Employee Boss Information\n7. Add a New Employee\n8. Delete Employee\n9. Exit\n";
	int option = 100;

	// Loop menu options untill user chooses 9 for exit
	while (option != 0)
	{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15); // **Sets the color back to white**
		cout << menu;
		cin >> option;
		// Validate if the menu option was a number from 1-9
		while (ValidOption(option) == false)
		{
			cin.clear();
			cin.ignore(255, '\n');
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4); // **Creates red text in the console window**
			cerr << "Invalid input, please try again\n";
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
			cout << menu;
			cin >> option;
			cin.clear();
			cin.ignore(255, '\n');
		}

		switch (option) {
		case 1: // Load company file
		{
			tempComp = new Company;
			// Opening the file
			cout << "File name: ";
			cin >> fileNameR;

			fin.open(fileNameR);
			if (fin.fail())
			{
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
				cerr << "Can't open \"" << fileNameR << "\"" << endl;
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
				exit(1);
			}
			// Reading the file
			tempComp->Read(fin);
			cout << "File loaded, " << tempComp->GetEmployeeCount() << " records read\n";
			fin.close();
			break;
		}
		case 2: // Save company data to file
		{
			// Opening the file
			cout << "File Name: ";
			cin >> fileNameW;

			ofstream fout(fileNameW);
			if (fout.fail())
			{
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
				cerr << "Can't open \"" << fileNameW << "\"" << endl;
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
				exit(1);
			}
			// Writing to the file
			fout << tempComp->Write(fout);
			fout.close();
			break;
		}
		case 3: // List all employees
		{
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 9);
			tempComp->Write(cout);
			break;
		}
		case 4: // Search by name
		{
			string name;
			cout << "Searching all employees whit name: ";
			cin >> name;
			// If FindByName returns -1 then there is no employee on record by that name 
			if (tempComp->FindByName(name) == -1)
			{
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
				cerr << "Invalid input, please try again\n";
				break;
			}
			// Displaying all employees with the name specified in the search 
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 9); // **Creates blue text in the console window**
			cout << tempComp->Get(tempComp->FindByName(name))->ToString() << endl;
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
			for (int i = tempComp->FindByName(name) + 1; i < tempComp->GetEmployeeCount(); i++)
			{
				int x = tempComp->FindByName(name, i);
				if (x != -1)
				{
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 9);
					cout << tempComp->Get(tempComp->FindByName(name, x))->ToString() << endl;
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
					i = x;
				}
			}
			break;
		}
		case 5: // Search by ID
		{
			char choice;
			double raise;
			int ID;
			cout << "Search for employee ID: ";
			cin >> ID;
			// Validate that user entered a number for ID search
			if (ValidId(ID) == false)
			{
				cout << endl;
				cin.clear();
				cin.ignore(255, '\n');
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
				cerr << "Invalid input, please try again\n";
				break;
			}

			// If FindById returns -1, then there is no employee with that ID on record
			if (tempComp->FindById(ID) == -1)
			{
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
				cerr << "Invalid input, please try again\n";
				break;
			}

			// Displaying the employee with the matching ID 
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 9);
			cout << tempComp->Get(tempComp->FindById(ID))->ToString() << endl;
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
			cout << "Would you like to give " << tempComp->Get(tempComp->FindById(ID))->GetName() << " a raise? (Y/N): ";
			cin >> choice;
			if (choice == 'Y' || choice == 'y')
			{
				cout << "What is the raise: ";
				cin >> raise;
				if (ValidRaise(raise) == false)
				{
					cout << endl;
					cin.clear();
					cin.ignore(255, '\n');
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
					cerr << "Invalid input, please try again\n";
					break;
				}
				tempComp->Get(tempComp->FindById(ID))->Raise(raise);
				break;
			}
			else if (choice == 'N' || choice == 'n')
			{
				break;
			}
			else
			{
				cout << endl;
				cin.clear();
				cin.ignore(255, '\n');
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
				cerr << "Invalid input, please try again\n";
				break;
			}
		}
		case 6: // Find employee Boss info
		{
			int ID;
			int boss;
			cout << "Search for employee ID: ";
			cin >> ID;
			if (ValidId(ID) == false)
			{
				cout << endl;
				cin.clear();
				cin.ignore(255, '\n');
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
				cerr << "Invalid input, please try again\n";
				break;
			}

			if (tempComp->FindById(ID) == -1)
			{
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
				cerr << "Invalid input, please try again\n";
				break;
			}
			if (tempComp->Get(tempComp->FindById(ID))->GetManagerId() == 0)
			{
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
				cerr << "This employee is not a manager\n";
				break;
			}
			// Displaying the employee with the matching ID 
			cout << "Employee current information:\n";
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 9);
			cout << tempComp->Get(tempComp->FindById(ID))->ToString() << endl;
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
			boss = tempComp->Get(tempComp->FindById(ID))->GetManagerId();
			cout << "Boss Information:\n";
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 9);
			cout << tempComp->Get(tempComp->FindById(boss))->ToString() << endl;
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
			break;
		}
		case 7: // Add new Employee
		{
			unsigned int ID;
			string name;
			double salary;
			unsigned int bossId;
			
			cout << "Input Employee Information\n";
			cout << "Employee ID: ";
			cin >> ID;

			// ID numbers are unique to each employee
			while (tempComp->FindById(ID) != -1)
			{
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
				cout << "ID already on file, chose a different ID: ";
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
				cin >> ID;
			}
			cout << "Employee Name: ";
			cin >> name;
			cout << "Salary: ";
			cin >> salary;
			cout << "Boss ID (0 for non): ";
			cin >> bossId;

			// Validating all numerical data
			if (ValidAdd(ID, salary, bossId) == false)
			{
				cout << endl;
				cin.clear();
				cin.ignore(255, '\n');
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
				cerr << "Invalid input, please try again\n";
				break;
			}
			if (tempComp->AddEmployee(ID, name, salary, bossId) == false)
			{
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
				cout << name << " not added successfully";
				break;
			}
			cout << name << " added successfully";
			break;

		}
		case 8: // Delete Employee
		{
			unsigned int ID;
			char choice;
			cout << "----- Preparing to Delete an Employee from Database -----\n";
			cout << "Search for employee ID: ";
			cin >> ID;

			if (ValidId(ID) == false)
			{
				cout << endl;
				cin.clear();
				cin.ignore(255, '\n');
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
				cerr << "Invalid input, please try again\n";
				break;
			}

			// If FindById returns -1, then there is no employee with that ID on record
			if (tempComp->FindById(ID) == -1)
			{
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
				cerr << "Invalid input, please try again\n";
				break;
			}

			cout << "Employee current information\n";
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 9);
			cout << tempComp->Get(tempComp->FindById(ID))->ToString() << endl;
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
			cout << "Are you really sure you want to erase the employee from the databse (Y/N)\n";
			cin >> choice;
			if (choice == 'Y' || choice == 'y')
			{
				if (tempComp->DeleteEmployee(ID) != true)
				{
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
					cout << "It is not possible to delete an employee that has subordinates";
					break;
				}
				cout << "Employee with ID = " << ID << " successfully deleted from database";
				break;
			}
			else if (choice == 'N' || choice == 'n')
			{
				break;
			}
			else
			{
				cout << endl;
				cin.clear();
				cin.ignore(255, '\n');
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
				cerr << "Invalid input, please try again\n";
				break;
			}

		}
		case 9:  // Exit
		{
			return 0;
		}
		default:
			break;
		}
		cout << endl;
		cout << endl;
	}


	return 0;
}
// Takes in the option for the switch case, if the option is from 1-9 the function returns true, false otherwise
bool ValidOption(const int choice)
{
	if ((choice < 0) || (choice > 9))
	{
		return false;
	}
	return true;
}

bool ValidId(const int id)
{
	string idString = to_string(id);
	// Validate ID
	int posId = idString.find_first_not_of("0123456789");
	if (posId != -1)
	{
		return false;
	}
	return true;
}

// Takes in the raise given by the user and makes sure its a number and greater than 0
bool ValidRaise(const double raise)
{
	string raiseString = to_string(raise);
	int posRaise = raiseString.find_first_not_of("0123456789.");
	if (posRaise != -1)
	{
		return false;
	}
	if (raise < 0)
	{
		return false;
	}
	return true;
}

// Takes in all the digit values to build an employee and validates the data, if the data is good the function returns true, false otherwise
bool ValidAdd(const unsigned int id, const double salary, const unsigned int bossId)
{
	// Converting data into strings and making sure they only contain numbers
	string idString = to_string(id);
	string salaryString = to_string(salary);
	string bossString = to_string(bossId);
	// Validate ID
	int posId = idString.find_first_not_of("0123456789");
	if (posId != -1)
	{
		return false;
	}
	// Validate Salary
	int posSalary = salaryString.find_first_not_of("0123456789.");
	if (posSalary != -1)
	{
		return false;
	}
	// Validate Boss ID
	int posBoss = bossString.find_first_not_of("0123456789");
	if (posBoss != -1)
	{
		return false;
	}
	return true;
}