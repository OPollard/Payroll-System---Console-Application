// Copyright Codebird Ltd ©, Inc. All Rights Reserved.
#pragma once

#include <array>

struct Date
{
	uint16_t Day{};
	uint16_t Month{};
	uint16_t Year{};
};


class Employee
{
private:
	uint32_t ID;
	std::string Name;
	std::string Address;
	std::string Phone;
	Date JoiningDate;
	std::string Designation;
	char Grade;
	uint32_t Pension;
	uint32_t BasicSalary;
	uint32_t Deductions;
	std::array<double, 12> Payslips;

public:

	Employee(uint32_t id = 0, std::string name = 0, std::string address = "", std::string phone = 0, Date joiningdate = { 0,0,0 },
		std::string designation = "", char grade = 0, uint32_t pension = 0, uint32_t basicsalary = 0, uint32_t deductions = 0)
		: ID{ id }, Name{ name }, Address{ address }, Phone{ phone }, JoiningDate{ joiningdate }, Designation{ designation }, Grade{ grade },
		Pension{ pension }, BasicSalary{ basicsalary }, Deductions{ deductions }
	{
		Payslips.fill(BasicSalary/12.00);
	}

	void Record(uint32_t id)
	{
		if (id != ID) std::cout << "Access denied. Wrong ID.";
		else
		{
			std::cout << "\n____________________________________\n";
			std::cout << "\nID:\t\t\t " << ID;
			std::cout << "\nName:\t\t\t " << Name;
			std::cout << "\nAddress:\t\t " << Address;
			std::cout << "\nPhone number:\t\t " << Phone;
			std::cout << "\nJoining date:\t\t " << JoiningDate.Day << '/' << JoiningDate.Month << '/' << JoiningDate.Year;
			std::cout << "\nDesignation:\t\t " << Designation;
			std::cout << "\nGrade:\t\t\t " << Grade;
			std::cout << "\nPension:\t\t " << Pension;
			std::cout << "\nBasic salary:\t\t " << BasicSalary;
			std::cout << "\nDeductions:\t\t " << Deductions;
			std::cout << "\n____________________________________";
		}
	}

	//Getters and Setters
	void SetID(const uint32_t id) { ID = id; }
	uint32_t GetID() const { return ID; }
	void SetName(const std::string name) { Name = name; }
	std::string GetName() const { return Name; }
	void SetAddress(const std::string address) { Address = address; }
	std::string GetAddress() const { return Address; }
	void SetPhone(const std::string phone) { Phone = phone; }
	std::string GetPhone() const { return Phone; }
	void SetJoiningDate(const Date joiningdate) { JoiningDate = joiningdate;  }
	Date GetJoiningDate() const { return JoiningDate; }
	void SetDesignation(const std::string designation) { Designation = designation; }
	std::string GetDesignation() const { return Designation; }
	void SetGrade(const char grade) { Grade = grade; }
	char GetGrade() const { return Grade; }
	void SetPension(uint32_t pension) { Pension = pension; }
	uint32_t GetPension() const { return Pension; }
	void SetBasicSalary(uint32_t basicsalary) { BasicSalary = basicsalary; }
	uint32_t GetBasicSalary() const { return BasicSalary; }
	void SetDeductions(uint32_t deductions) { Deductions = deductions; }
	uint32_t GetDeductions() const { return Deductions; }
	void SetPayslip(int month, const double amount) { Payslips[month-1] = amount; }
	double GetPayslip(int month) const { return Payslips[month-1]; }
};


