#pragma once
#include "MyVector.hpp"
#include "Account.h"
#include "Request.h"
#include "Employee.h"
#include "Message.h"

class Account;
class Employee;

class Bank {
private:
	MyString bankName = "Unknown";
	MyVector<Account> accounts;
	MyVector<Request> requests;
	MyVector<Client*> clients;

	MyVector<Employee*> employees;
	int getEmployeeIdx(const MyString& egn) const;
	int getEmployeeWithLeastTasks() const;

	bool validateClient(Client* client) const;
	int getClientIdx(const MyString& egn) const;

	int getAccountIdx(size_t accountNumber) const;
	int getRequestIdx(const MyString& egn) const;

public:
	Bank() = default;
	Bank(const MyString& bankName);

	void addClient(Client* client);

	double getAccountBalance(size_t number);

	void sendRequestToEmployee(const Request& request);
	void sendAnswerToClient(const Message& message, Client* client);

	Account* getAccount(size_t accountNumber);

	void addAccount(size_t accountNumber, double balance, Client* client);
	void deleteAccount(size_t accountNumber, Client* client);
	void printAccounts() const;

	void setBankName(const MyString& bankName);

	MyVector<Employee*>& getEmployees();
	Client* getClient(const MyString& egn);
	bool checkClient(Client* client) const;

	Employee* getEmployeeByIndex(int idx);
	Request* getRequestByIndex(int task_id);

	const MyString& getBankName() const;

	~Bank() = default;
};
