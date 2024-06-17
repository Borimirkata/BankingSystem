#pragma once

#include "MyVector.hpp"
#include "Client.h"
#include "Bank.h"
#include "Employee.h"
#include "ThirdPartyEmployee.h"

namespace Roles {
	const MyString client = "Client";
	const MyString employee = "Employee";
	const MyString thirdParty = "Third-party employee";
}

class Bank;
class Client;
class Employee;
class ThirdPartyEmployee;

class BankingSystem {
private:
	static MyVector<Bank> banks;
	MyVector<Client> clients;
	MyVector<Employee> employees;
	MyVector<ThirdPartyEmployee> thirdPartyEmployees;

	Client* currentClient = nullptr;
	Employee* currentEmployee = nullptr;
	ThirdPartyEmployee* currentThirdParty = nullptr;
	Bank* currentBank = nullptr;

	int getClientIndex(const MyString& egn) const;
	int getEmployeeIndex(const MyString& egn) const;
	int getThirdEmployeeIndex(const MyString& egn) const;
	int getBankIndex(const MyString& bankName) const;

	bool validateClient(const MyString& firstName, const MyString& secondName, const MyString& password,int& index) const;			
	bool validateEmployee(const MyString& firstName, const MyString& secondName, const MyString& password,int& index) const;				
	bool validateThirdPartyEmployee(const MyString& firstName, const MyString& secondName, const MyString& password,int& index) const;
	const MyString& getType(const MyString& firstName,const MyString& secondName,const MyString& password,int& index) const;

public:
	BankingSystem() = default;

	void signup(const MyString& firstName, const MyString& secondName, const MyString& egn, int age, const MyString& role, const MyString& password, const MyString& bankName,const MyString& address);
	void login(const MyString& firstName, const MyString& secondName, const MyString& password);
	void createBank(const MyString& bankName);

	static Bank* getBankByName(const MyString& bankName);

	void quit();
	void exit();


	~BankingSystem() = default;

};
