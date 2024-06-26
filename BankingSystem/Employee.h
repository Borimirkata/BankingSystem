#pragma once

#include "MyVector.hpp"
#include "User.h"
#include "Bank.h"
#include "SerializeFunctions.h"

class Bank;
class Request;

namespace EmployeeData {
	constexpr size_t START_BALANCE = 0;
	
	const MyString type1 = "Open";
	const MyString type2 = "Close";
	const MyString type3 = "Change";
	const MyString approvedChange = "(approved)";
}

class Employee :public User {
private:
	MyString bankAssociated = "Unknown";
	MyVector<Request*> tasks;
	Bank* bank=nullptr;

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

	const MyString& getBankAssociated() const;
	void setBank(Bank* bank);

	virtual void help() const override;
	virtual void whoami() const override;
	virtual void exit() const override;

	void writeToFile(std::ofstream& ofs) const;
	virtual void readFromFile(std::ifstream& ifs);

	~Employee();
};
