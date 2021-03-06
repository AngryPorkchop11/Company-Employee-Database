// Title: Lab 8 Company Employee Database Unit Test - Lab8UnitTest.cpp
//
// Purpose: Runs validation tests on the Company's Database classes for Lab 8
//
// Class: CSC 2430 Winter 2018
//
// Author: Carlos Arias

#define _CRTDBG_MAP_ALLOC  
#include <stdlib.h>  
#include <crtdbg.h>  

#ifdef _DEBUG
#define DBG_NEW new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )
#define new DBG_NEW
#endif

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <cassert>

using std::cout;
using std::cerr;
using std::cin;
using std::endl;

using std::ostream;
using std::istream;
using std::ofstream;
using std::ifstream;
using std::string;
using std::stringstream;

#include "employee.h"
#include "employeeList.h"
#include "company.h"

int main()
{
	const int TEST_MAX = 10;
	stringstream inbuffer0, inbuffer1, inbuffer2, inbuffer3, outbuffer;

	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF | _CRTDBG_CHECK_ALWAYS_DF);

	Employee employee(0, "", 0);
	// Check Employee initial state
	assert(employee.GetId() == 0);
	assert(employee.GetName() == "***");
	assert(employee.GetManagerId() == 0);
	assert(employee.GetSalary() == 0.0);
	cerr << "Employee operations --------------------- Passed!" << endl << endl;

	Company * company = new Company();

	// Check Company initial state
	assert(company->GetEmployeeCount() == 0);
	assert(company->Get(0) == NULL);
	assert(company->FindById(1) == -1);
	assert(company->FindByName("Name") == -1);
	cerr << "Company operations (Initial State) ------ Passed!" << endl << endl;


	// Empty file
	inbuffer0.str("");
	assert(company->Read(inbuffer0) == 0);
	assert(company->GetEmployeeCount() == 0);
	assert(company->Get(0) == NULL);
	assert(company->FindById(1) == -1);
	assert(company->FindByName("Name") == -1);
	cerr << "Company operations (Empty File) --------- Passed!" << endl << endl;

	// Load Employees
	inbuffer1.str(
		"10 Anna 2250 2\n"
		"1 Peter 250 0\n"
		"11 Melissa 1450 1\n"
		"4 Leonel 1801 0\n"
		"3 Silvia 150 1\n"
		"16 Nicole 50 0\n"
		"5 Jon 3500 1\n"
		"2 Dio 100 0\n"
		"9 Jon 4100 2\n"
	);
	Employee* ptrEmployee;

	int employeeIndex;

	assert(company->Read(inbuffer1) == 9);
	assert(company->Get(0)->Equals(Employee(1, "Peter", 250))); // Testing sort
	assert((employeeIndex = company->FindById(1)) != -1);
	assert((ptrEmployee = company->Get(employeeIndex)) != NULL);
	assert(ptrEmployee->GetId() == 1);
	assert(ptrEmployee->GetName() == "Peter");
	assert(ptrEmployee->GetSalary() == 250);
	assert(ptrEmployee->GetManagerId() == 0);
	assert((employeeIndex = company->FindByName("Jon")) != -1);
	assert((ptrEmployee = company->Get(employeeIndex)) != NULL);
	assert(ptrEmployee->GetId() == 5);
	assert(ptrEmployee->GetName() == "Jon");
	assert(ptrEmployee->GetSalary() == 3500);
	assert(ptrEmployee->GetManagerId() == 1);
	assert((employeeIndex = company->FindByName("Jon", employeeIndex + 1)) != -1);
	assert((ptrEmployee = company->Get(employeeIndex)) != NULL);
	assert(ptrEmployee->GetId() == 9);
	assert(ptrEmployee->GetName() == "Jon");
	assert(ptrEmployee->GetSalary() == 4100);
	assert(ptrEmployee->GetManagerId() == 2);
	assert(company->GetEmployeeCount() == 9);
	assert(company->Write(outbuffer) == 9);
	cerr << "Company operations (9 records test) ----- Passed!" << endl << endl;

	delete company;
	company = new Company();

	inbuffer2.str(
		"10 Anna 2250 2\n"
		"1 Peter 250 0\n"
		"11 Melissa 1450 1\n"
		"4 Leonel 1801 0\n"
		"3 Silvia 150 1\n"
		"16 Nicole 50 0\n"
		"5 Jon 3500 1\n"
		"2 Dio 100 0\n"
		"9 Jon 4100 2\n"
		"8 Chris 800 0\n"
		"100 Kat 4875 2\n"
	);
	assert(company->Read(inbuffer2) == 11);
	assert(company->Get(0)->Equals(Employee(1, "Peter", 250))); // Testing sort
	assert((employeeIndex = company->FindById(8)) != -1);
	assert((ptrEmployee = company->Get(employeeIndex)) != NULL);
	assert(ptrEmployee->GetId() == 8);
	assert(ptrEmployee->GetName() == "Chris");
	assert(ptrEmployee->GetSalary() == 800);
	assert(ptrEmployee->GetManagerId() == 0);
	assert((employeeIndex = company->FindByName("Jon")) != -1);
	assert((ptrEmployee = company->Get(employeeIndex)) != NULL);
	assert(ptrEmployee->GetId() == 5);
	assert(ptrEmployee->GetName() == "Jon");
	assert(ptrEmployee->GetSalary() == 3500);
	assert(ptrEmployee->GetManagerId() == 1);
	assert((employeeIndex = company->FindByName("Jon", employeeIndex + 1)) != -1);
	assert((ptrEmployee = company->Get(employeeIndex)) != NULL);
	assert(ptrEmployee->GetId() == 9);
	assert(ptrEmployee->GetName() == "Jon");
	assert(ptrEmployee->GetSalary() == 4100);
	assert(ptrEmployee->GetManagerId() == 2);
	ptrEmployee->Raise(1000);
	assert(ptrEmployee->GetSalary() == 5100);
	assert(company->GetEmployeeCount() == 11);
	assert(!company->DeleteEmployee(2));
	assert(company->DeleteEmployee(8));
	assert(company->GetEmployeeCount() == 10);
	assert(company->FindById(8) == -1);
	assert(company->Write(outbuffer) == 10);
	cerr << "Company operations (11 records test) ---- Passed!" << endl << endl;

	delete company;

	EmployeeList *plist = new EmployeeList();
	Employee employeeTest(1, "Test", 99.9);

	// Empty list
	assert(plist->IsEmpty());
	assert(plist->Size()==0);
	assert(!plist->Get(0));
	assert(plist->IndexOf(employeeTest) == -1);
	assert(!plist->Remove(5));

	// One element
	assert(plist->Insert(new Employee(employeeTest)));
	assert(!plist->IsEmpty());
	assert(plist->Size() == 1);
	{
		Employee *pemployee;

		assert(pemployee = plist->Get(0));
		assert(pemployee->GetId() == 1);
		assert(pemployee->GetName() == "Test");
		assert(pemployee->GetSalary() == 99.9);
		assert(pemployee->GetManagerId() == 0);
	}
	assert(!plist->Get(1));
	assert(plist->IndexOf(employeeTest) == 0);
	assert(!plist->Remove(5));
	assert(plist->Remove(0));
	assert(plist->IsEmpty());
	assert(plist->Size() == 0);
	assert(!plist->Get(0));
	assert(plist->IndexOf(employeeTest) == -1);
	assert(!plist->Remove(0));

	inbuffer3.str(
		"19 Anna 2250 2\n"
		"3 Peter 250 0\n"
		"21 Melissa 1450 1\n"
		"9 Leonel 1801 0\n"
		"7 Silvia 150 1\n"
		"23 Nicole 50 0\n"
		"11 Jon 3500 1\n"
		"5 Dio 100 0\n"
		"17 Jon 4100 2\n"
		"15 Chris 800 0\n"
		"13 Kat 4875 2\n"
	);
	struct EmployeeData
	{
		int id;
		string name;
		double salary;
		int managerId;
	};
	EmployeeData E1[] = {
			{3, "Peter", 250, 0 },
			{5, "Dio",   100, 0 },
			{7, "Silvia",150, 1 },
			{9, "Leonel",1801,0 },
			{11, "Jon",   3500,1 },
			{13, "Kat",   4875,2 },
			{15, "Chris", 800, 0 },
			{17, "Jon",   4100,2 },
			{19,"Anna",  2250,2 },
			{21,"Melissa",1450, 1},
			{23,"Nicole", 50, 0 } };

	assert(plist->Read(inbuffer3) == 11);
	assert(!plist->IsEmpty());
	assert(plist->Size() == 11);
	for (int i = 0; i < sizeof(E1) / sizeof(E1[0]); i++)
	{
		Employee *pemployee;

		assert(pemployee = plist->Get(i));
		assert(pemployee->GetId() == E1[i].id);
		assert(pemployee->GetName() == E1[i].name);
		assert(pemployee->GetSalary() == E1[i].salary);
		assert(pemployee->GetManagerId() == E1[i].managerId);
		assert(plist->IndexOf(*pemployee) == i);
	}
	assert(plist->Insert(new Employee(2, "Gith", 1340, 3)));
	assert(plist->Insert(new Employee(6, "Enid", 5706, 1)));
	assert(plist->Insert(new Employee(30, "Oleg", 2400, 2)));
	EmployeeData E2[] = {
		{ 2, "Gith", 1340, 3 },//
		{ 3, "Peter", 250, 0 },
		{ 5, "Dio",   100, 0 },
		{ 6, "Enid",  5706,1 },
		{ 7, "Silvia",150, 1 },
		{ 9, "Leonel",1801,0 },//
		{ 11, "Jon",   3500,1 },
		{ 13, "Kat",   4875,2 },//
		{ 15, "Chris", 800, 0 },
		{ 17, "Jon",   4100,2 },
		{ 19,"Anna",  2250,2 },
		{ 21,"Melissa",1450, 1 },
		{ 23,"Nicole", 50, 0 },
		{ 30, "Oleg", 2400, 2}};
	assert(plist->Size() == 14);
	for (int i = 0; i < sizeof(E2) / sizeof(E2[0]); i++)
	{
		Employee *pemployee;

		assert(pemployee = plist->Get(i));
		assert(pemployee->GetId() == E2[i].id);
		assert(pemployee->GetName() == E2[i].name);
		assert(pemployee->GetSalary() == E2[i].salary);
		assert(pemployee->GetManagerId() == E2[i].managerId);
		assert(plist->IndexOf(*pemployee) == i);
	}
	assert(plist->Remove(0));
	assert(plist->Remove(5));
	assert(plist->Remove(7));
	assert(plist->Remove(10));
	assert(plist->Size() == 10);
	EmployeeData E3[] = {
		{ 3, "Peter", 250, 0 },
		{ 5, "Dio",   100, 0 },
		{ 6, "Enid",  5706,1 },
		{ 7, "Silvia",150, 1 },
		{ 9, "Leonel",1801,0 },
		{ 13, "Kat",   4875,2 },
		{ 15, "Chris", 800, 0 },
		{ 19,"Anna",  2250,2 },
		{ 21,"Melissa",1450, 1 },
		{ 23,"Nicole", 50, 0 } };
	for (int i = 0; i < sizeof(E3) / sizeof(E3[0]); i++)
	{
		Employee *pemployee;

		assert(pemployee = plist->Get(i));
		assert(pemployee->GetId() == E3[i].id);
		assert(pemployee->GetName() == E3[i].name);
		assert(pemployee->GetSalary() == E3[i].salary);
		assert(pemployee->GetManagerId() == E3[i].managerId);
		assert(plist->IndexOf(*pemployee) == i);
	}

	delete plist;
	
	cerr << "EmployeeList Test ---- Passed!" << endl << endl;

	cerr << "Congratulations you passed all the tests!" << endl;
    return 0;
}

