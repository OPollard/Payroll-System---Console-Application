// Copyright Codebird Ltd ©, Inc. All Rights Reserved.

/*
1. Addition of New Employee: You can find this feature under the public category of class employee. 
	The information contained in this feature are employee code number, name, address, phone number, joining date 
	(day, month and year), designation, grade and Pension. Besides these, this function also stores record related to 
	employee’s basic salary, deductions, and many more.
*/
/*
2. Modify Employee Record: Payroll management system project in C++ asks for employee code from the user for
	this function to work. Modifications that can be made are the employee code number itself, joining date 
	(day, month and year), name, address, phone number, designation, grade, deductions and Pension given to the employee.
	Employee’s grade are categorized as A, B, C, D and E.
*/
/*
3. Delete Employee Record: You can simply delete an employee record from Payroll management system project by entering
	the employee code. A confirmation message is asked stating whether the user really wants to delete the record from the 
	file.
*/
/*
4. Print Employee Salary Slip: This feature too asks for the employee code; the employee code has been used to unlock 
	or perform operations in many features of this payroll management system project in C++. This function lists all the 
	months of the year, and asks for date, employee name, designation and grade from the user. To print the salary slip, 
	the user further needs to provide information such as number of days worked in the month by the employee and the number 
	of hours worked over time. The slip enlists basic salary, allowance, deductions and net salary of the employee.
*/
/*
5. Display a Employee Record: Providing the employee code number, users can access all the provided information 
	related to a particular employee via this function. The employee record information displayed are the ones provided 
	while adding a new employee record.
*/
/*
6. Display List of Employees: Unlike the above function, this feature displays the record of all employees added in file.
	The records are displayed in a tabular pattern containing information such as code name of the employee, phone number,
	date of joining, designation, grade and salary.
*/
// Add option to quit when things go wrong

#include <iostream>
#include "Database.h"

#define FILENAME "Staff.txt"

int main()
{
	Database db;

	if (db.ReadFromFile(FILENAME))
	{
		std::cout << "Success importing " << FILENAME << std::endl;
	}
	else
	{
		std::cout << "Failure to import " << FILENAME << std::endl;
	}
	
	while (true)
	{
		std::cout << "\n\nPayroll System:\n\n\t 1 - Add new employee\n\t 2 - Modify existing employee\n\t 3 - Delete employee record\n\t 4 - Enter employee hours"
		<< "\n\t 5 - Print employee annual statement\n\t 6 - Display employee record\n\t 7 - Display list of employees\n\t 8 - Display list of ID's\n\t 9 - Exit\n\n";

		int UserRequest;
		std::cin >> UserRequest;
		if (!std::cin.fail())
		{
			switch (UserRequest)
			{
				case 1: db.Add();				break;
				case 2:	db.Modify();			break;
				case 3: db.Delete();			break;
				case 4:	db.EmployeeHours();		break;
				case 5:	db.PrintSalary();		break;
				case 6:	db.DisplayRecord();		break;
				case 7:	db.DisplayAllRecords();	break;
				case 8:	db.PrintIDs();			break;
				case 9: 						return 0;
					default: std::cout << "\nError code: GoldFlake. Incorrect Selection" << std::endl;
			}
		}
		else
		{
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			std::cout << "\nError: WolfBlood. Invalid Input" << std::endl;
		}
	}

}
