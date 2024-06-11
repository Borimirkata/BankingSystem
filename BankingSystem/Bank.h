#pragma once
#include "MyString.h"
#include "MyVector.hpp"
#include "Account.h"


class Bank {
private:
	MyString bankName = "Unknown";
	MyVector<Account> accounts;
	MyVector<MyString> tasks;

public:
	Bank() = default;
	Bank(const MyString& bankName);
	double getAccountBalance(size_t number);
	void pushTask(const MyString& task);
	const MyString& getTaskAtIndex(size_t index) const;
	void printAccounts() const;
	void setBankName(const MyString& bankName);
	const MyString& getBankName() const;
};
