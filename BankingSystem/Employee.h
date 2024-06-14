#pragma once

#include "MyVector.hpp"
#include "BankingSystem.h"
#include "User.h";
#include "Bank.h"

class Bank;
class Request;

class Employee :public User {
private:
	MyString bankAssociated = "Unknown";
	MyVector<Request*> tasks;
	Bank* bank;

public:
	Employee() = default;
	Employee(const MyString& firstName, const MyString& secondName, const MyString& egn, size_t age, const MyString& role, const MyString& password, const MyString& bankName);

	void addTask(Request* request);
	void printTasks() const;
	void view(size_t idx) const;
	void approve(size_t idx);
	void disapprove(size_t idx, const MyString& message);
	void validate(size_t idx);

	MyVector<Request*> getTasks();

	virtual void help() const override;
	virtual void whoami() const override;
};
