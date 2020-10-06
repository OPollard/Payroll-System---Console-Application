// Copyright Codebird Ltd ©, Inc. All Rights Reserved.
#pragma once

#include "Employee.h"
#include <fstream>
#include <sstream>
#include <vector>
#include <string>

#define LOWER_TAX_RATE  0.20f
#define MIDDLE_TAX_RATE 0.40f
#define HIGHER_TAX_RATE 0.45f

class Database
{
public:

	////	Tools		/////////////////////////////////////////////////////////////////

	//Read data from text file
	bool ReadFromFile(const std::string& filename)
	{
		std::ifstream infile(filename,  std::ios::in);
		if (infile.good())
		{
			while (!infile.eof())
			{
				uint32_t ID, Pension, BasicSalary, Deductions;
				std::string Name, Address, Phone, Designation;
				Date date;
				char Grade;
				for (int i{ 1 }; i < 13; ++i)
				{
					std::string line;
					std::getline(infile, line);
					switch (i)
					{
					case 1: ID = (std::stoi(line)); break;
					case 2: Name = (line); break;
					case 3: Address = (line); break;
					case 4: Phone = (line); break;
					case 5: date.Day = std::stoi(line); break;
					case 6: date.Month = std::stoi(line); break;
					case 7: date.Year = std::stoi(line); break;
					case 8: Designation = (line); break;
					case 9: Grade = (line[0]); break;
					case 10: Pension = (std::stoi(line)); break;
					case 11: BasicSalary = (std::stoi(line)); break;
					case 12: Deductions = (std::stoi(line)); break;
					}
				}
				Employee person(ID, Name, Address, Phone, date, Designation, Grade, Pension, BasicSalary, Deductions);
				EmployeeList.push_back(person);
			}
			infile.close();
			return true;
		}
		return false;
	}

	//Check user input is correct
	template <class T>
	T FlushInput(const std::string& title, T datatype, bool isAfterString)
	{
		do
		{
			std::cin.clear();
			if (!isAfterString) std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			std::cout << title; 
			if constexpr (std::is_same_v<T, std::string>) std::getline(std::cin, datatype);
			else std::cin >> datatype;
		} while (std::cin.fail());
		return datatype;
	}

	// Creates new employee from user data
	Employee CreateEmployee()
	{
		uint32_t ID{ 0 }, Pension{ 0 }, BasicSalary{ 0 }, Deductions{ 0 };
		std::string Name, Address, Phone, Designation;
		Date JoiningDate;
		char Grade = 0;
		do
		{
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			std::cout << "ID:\t\t\t "; std::cin >> ID;
		} while (!IsIdFree(ID) || std::cin.fail());

		Name = FlushInput("Name:\t\t\t ", Name, false);
		Address = FlushInput("Address:\t\t ", Address, true);
		Phone = FlushInput("Phone Number:\t\t ", Phone, true);
		JoiningDate.Day = FlushInput("Joining Date Day:\t ", JoiningDate.Day, true);
		JoiningDate.Month = FlushInput("Joining Date Month:\t ", JoiningDate.Month, false);
		JoiningDate.Year = FlushInput("Joining Date Year:\t ", JoiningDate.Year, false);
		Designation = FlushInput("Designation:\t\t ", Designation, false);
		Grade = FlushInput("Grade:\t\t\t ", Grade, true);
		Pension = FlushInput("Pension:\t\t ", Pension, false);
		BasicSalary = FlushInput("Basic Salary:\t\t ", BasicSalary, false);
		Deductions = FlushInput("Deductions:\t\t ", Deductions, false);

		return Employee(ID, Name, Address, Phone, JoiningDate, Designation, Grade, Pension, BasicSalary, Deductions);
	}

	//Print a list of all current ID's
	void PrintIDs()
	{
		std::cout << "\nID List:\n\n";
		for (size_t index{ 0 }; index < EmployeeList.size(); ++index)
		{
			std::cout << "\t " << EmployeeList[index].GetID() << std::endl;
		}
	}

	// Find employee by ID
	std::vector<Employee>::iterator FindEmployee(uint32_t id)
	{
		for (std::vector<Employee>::iterator i = EmployeeList.begin(); i != EmployeeList.end(); i++)
		{
			if (i->GetID() == id)
			{
				return i;
			}
		}
		std::cout << "\nError Code: ChocolateButtons. No employee with that ID" << std::endl;
		return EmployeeList.end();
	}

	// Check if ID is free
	bool IsIdFree(uint32_t id)
	{
		for (size_t i{ 0 }; i < EmployeeList.size(); i++)
		{
			if (EmployeeList[i].GetID() == id)
			{
				std::cout << "\nError Code: VanillaBullet. ID taken.\n" << std::endl;
				return false;
			}
		}
		
		return true;
	}

	// Get reference to employee by ID
	std::vector<Employee>::iterator IdentifyByID()
	{
		uint32_t id{};
		std::cout << "Enter employee ID:\t "; std::cin >> id;
		
		return FindEmployee(id);
	}

	//Calculate tax, as of UK 2020/2021
	double CalculatePostTaxPay(double income)
	{
		if (income <= 12500) return income;
		else if (income <= 50000) return ((income - 12500) * LOWER_TAX_RATE) + 12500;
		else if (income <= 150000) return ((income - 50000) * MIDDLE_TAX_RATE) + 42500;
		else return ((income - 150000) * HIGHER_TAX_RATE) + 102500;
	}

	////	Features	///////////////////////////////////////////////////////////////

	//Add new employee
	void Add()
	{
		EmployeeList.push_back(CreateEmployee());
	}

	//Modify employee information
	void Modify()
	{
		auto Person = IdentifyByID();
		if (Person != EmployeeList.end())
		{
			Person->Record(Person->GetID());
			std::cout << "\n\nWhich data would you like to edit?\n\n";
			std::cout << "(0) ID\n";
			std::cout << "(1) Name\n";
			std::cout << "(2) Address\n";
			std::cout << "(3) Phone\n";
			std::cout << "(4) Joining Date\n";
			std::cout << "(5) Designation\n";
			std::cout << "(6) Grade\n";
			std::cout << "(7) Pension\n";
			std::cout << "(8) Basic Salary\n";
			std::cout << "(9) Deductions" << std::endl;

			int UserRequest;
			do
			{
				std::cin.clear();
				std::cout << "\nChoice:\t\t\t ";
				std::cin >> UserRequest;
			} while (std::cin.fail());

			uint32_t ID, Pension{ 0 }, BasicSalary{ 0 }, Deductions{0};
			std::string Name, Address, Phone, Designation;
			Date JoiningDate;
			char Grade = 0;

			switch (UserRequest)
			{
				case 0:
					do
					{
						std::cin.clear();
						std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
						std::cout << "\nID:\t\t\t "; std::cin >> ID;
					} while (!IsIdFree(ID) || std::cin.fail());
					Person->SetID(ID);
					std::cout << "\n Success!\n"; break;
				case 1:
					Name = FlushInput("Name:\t\t\t ", Name, false);
					Person->SetName(Name);
					std::cout << "\n Success!\n"; break;
				case 2:
					Address = FlushInput("Address:\t\t ", Address, true);
					Person->SetAddress(Address);
					std::cout << "\n Success!\n"; break;
				case 3: 
					Phone = FlushInput("Phone Number:\t\t ", Phone, true);
					Person->SetPhone(Phone);
					std::cout << "\n Success!\n"; break;
				case 4: 
					JoiningDate.Day = FlushInput("Joining Date Day:\t ", JoiningDate.Day, true);
					JoiningDate.Month = FlushInput("Joining Date Month:\t ", JoiningDate.Month, false);
					JoiningDate.Year = FlushInput("Joining Date Year:\t ", JoiningDate.Year, false);
					Person->SetJoiningDate(JoiningDate);
					std::cout << "\n Success!\n"; break;
				case 5:
					Designation = FlushInput("Designation:\t\t ", Designation, false);
					Person->SetDesignation(Designation);
					std::cout << "\n Success!\n"; break;
				case 6:
					Grade = FlushInput("Grade:\t\t\t ", Grade, true);
					Person->SetGrade(Grade);
					std::cout << "\n Success!\n"; break;
				case 7: 
					Pension = FlushInput("Pension:\t\t ", Pension, false);
					Person->SetPension(Pension);
					std::cout << "\n Success!\n"; break;
				case 8: 
					BasicSalary = FlushInput("Basic Salary:\t\t ", BasicSalary, false);
					Person->SetBasicSalary(BasicSalary);
					std::cout << "\n Success!\n"; break;
				case 9:
					Deductions = FlushInput("Deductions:\t\t ", Deductions, false);
					Person->SetDeductions(Deductions);
					std::cout << "\n Success!\n"; break;
				default: std::cout << "\nError code: GoldFlake. Incorrect Selection" << std::endl;
			}
		}
	}

	//Delete employee
	void Delete()
	{
		auto Person = IdentifyByID();
		if (Person != EmployeeList.end())
		{
			std::cout << "Are you sure you want to delete " << Person->GetName() << "? (y/n) : ";
			std::cin.clear(); std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			char answer; std::cin >> answer;
			if (answer == 'y')
			{
				EmployeeList.erase(Person);
				std::cout << "\nErased." << std::endl;
			}
			else if (answer == 'n')
			{
				std::cout << "\nAborted." << std::endl;
			}
			else
			{
				std::cout << "\nError: WolfBlood. Invalid Input" << std::endl;
			}
		}
	}

	//Enter employee hours
	void EmployeeHours()
	{
		std::vector<Employee>::iterator Person = IdentifyByID();

		if (Person != EmployeeList.end())
		{
			int Month;
			double HoursWorked;

			do
			{
				std::cin.clear();
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
				std::cout << "Which month to input (1-12):\t "; std::cin >> Month;
			} while (std::cin.fail() || ((Month < 0) || (Month > 13)));
			do
			{
				std::cin.clear();
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
				std::cout << "Hours worked:\t\t\t "; std::cin >> HoursWorked;
			} while (std::cin.fail() || ((HoursWorked <= 0) || (HoursWorked >= 480)));

			double MonthlySalary = (Person->GetBasicSalary() / 12) * (HoursWorked / 160); // 160 is 9am-5pm for Mon-Fri
			Person->SetPayslip(Month, MonthlySalary);

			std::cout << "\nSuccess! Data added to employee " << Person->GetID() << std::endl;
		}
	}

	//Print Employee Salary Slip
	void PrintSalary()
	{
		std::vector<Employee>::iterator Person = IdentifyByID();

		if (Person != EmployeeList.end())
		{
			std::cout << "\n______________________________\n";
			std::cout << "\n\tAnnual Statement:";
			std::cout << "\nJAN:\t " << Person->GetPayslip(1);
			std::cout << "\nFEB:\t " << Person->GetPayslip(2);
			std::cout << "\nMAR:\t " << Person->GetPayslip(3);
			std::cout << "\nAPR:\t " << Person->GetPayslip(4);
			std::cout << "\nMAY:\t " << Person->GetPayslip(5);
			std::cout << "\nJUN:\t " << Person->GetPayslip(6);
			std::cout << "\nJUL:\t " << Person->GetPayslip(7);
			std::cout << "\nAUG:\t " << Person->GetPayslip(8);
			std::cout << "\nSEP:\t " << Person->GetPayslip(9);
			std::cout << "\nOCT:\t " << Person->GetPayslip(10);
			std::cout << "\nNOV:\t " << Person->GetPayslip(11);
			std::cout << "\nDEC:\t " << Person->GetPayslip(12);

			double BasicTotal{ 0 };
			for (int i{ 1 }; i < 13; ++i)
			{
				BasicTotal += Person->GetPayslip(i);
			}
			std::cout << "\n______________________________\n";
			std::cout << "\nBASIC:\t " << BasicTotal;
			std::cout << "\nDEDUCT:\t " << Person->GetDeductions();
			std::cout << "\nPENSION: " << Person->GetPension();
			double PostDeductTotal{ BasicTotal - Person->GetDeductions() };
			double PostPensionTotal{ PostDeductTotal - Person->GetPension() };
			std::cout << "\nPRE-TAX: " << PostPensionTotal;
			double TaxToPay{ (PostPensionTotal - CalculatePostTaxPay(PostPensionTotal)) };
			std::cout << "\nTAX:\t " << TaxToPay;
			double FinalTotal{ PostPensionTotal - TaxToPay };
			std::cout << "\nTOTAL:\t " << FinalTotal;

			std::cout << "\n______________________________\n";
		}
	}

	//Get record of employee
	void DisplayRecord()
	{
		auto Person = IdentifyByID();

		if(Person != EmployeeList.end())
		{
			Person->Record(Person->GetID());
		}
	}

	//Display record of all employees
	void DisplayAllRecords()
	{
		for (auto e : EmployeeList)
		{
			e.Record(e.GetID());
		}
	}

private:

	std::vector<Employee> EmployeeList;
};