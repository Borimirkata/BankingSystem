#pragma once
#include "MyString.h"

namespace {
	constexpr size_t NULL_VALUE = 0;
}

class Account {
private:
	MyString bankName="Unknown";
	size_t accountNumber=0;
	double balance = 0;

public:
	Account() = default;
	Account(const MyString& bankName, size_t accountNumber, double balance);

	const MyString& getBankName() const;
	size_t getAccountNumber() const;
	double getBalance() const;

	void setBankName(const MyString& bankName);
	void setAccountNumber(size_t accountNumber);
	void setBalance(double balance);

	~Account() = default;
};
