#pragma once

#include "MyVector.hpp"
#include "Client.h"
#include "Bank.h"
#include "Employee.h"
#include "ThirdPartyEmployee.h"

namespace Roles {
	const MyString client = "Client";
	const MyString employee = "Employee";
	const MyString thirdParty = "Third-party-employee";
}

class Request;
class Bank;
class Client;
class Employee;
class ThirdPartyEmployee;

class BankingSystem {
private:
	MyVector<Bank> banks;
	MyVector<Client> clients;
	MyVector<Employee> employees;
	MyVector<ThirdPartyEmployee> thirdPartyEmployees;

	Client* currentClient = nullptr;
	Employee* currentEmployee = nullptr;
	ThirdPartyEmployee* currentThirdParty = nullptr;

	bool isUniquePerson(const MyString& firstName, const MyString& secondName, const MyString& egn) const;

	bool validateClient(const MyString& firstName, const MyString& secondName, const MyString& password, int& index) const;
	bool validateEmployee(const MyString& firstName, const MyString& secondName, const MyString& password, int& index) const;
	bool validateThirdPartyEmployee(const MyString& firstName, const MyString& secondName, const MyString& password, int& index) const;
	const MyString& getType(const MyString& firstName, const MyString& secondName, const MyString& password, int& index) const;

public:
	BankingSystem() = default;

	void signup(const MyString& firstName, const MyString& secondName, const MyString& egn, int age, const MyString& role, const MyString& password, const MyString& bankName, const MyString& address);
	void login(const MyString& firstName, const MyString& secondName, const MyString& password);
	void createBank(const MyString& bankName);

	Bank* getBankByName(const MyString& bankName);

	void clientCheckAvl(const MyString& bankName, size_t accountNumber) const;
	void clientOpen(const MyString& bankName);
	void clientClose(const MyString& bankName, size_t accountNumber);
	void clientRedeem(const MyString& bankName, size_t accountNumber, const MyString& verificationCode);
	void clientChange(const MyString& newBankName, const MyString& currentBankName, size_t accountNumber);
	void clientList(const MyString& bankName) const;
	void clientMessages() const;

	void employeePrintTasks() const;
	void employeeView(size_t idx) const;
	void employeeApprove(size_t idx);
	void employeeDisapprove(size_t idx, const MyString& message);
	void employeeValidate(size_t idx);

	void thirdPartySendCheck(double sum, const MyString& bankName, const MyString& code, const MyString& egn);

	void userHelp() const;
	void userWhoami() const;

	void quit();
	void exit();

	void writeToFile() const;
	void readFromFile();

	~BankingSystem();

};
