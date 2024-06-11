#pragma once
#include "MyString.h"

namespace {
	constexpr size_t NULL_VALUE = 0;
}

class Account {
private:
	size_t accountNumber=0;
	double balance = 0;

public:
	Account() = default;
	Account(size_t accountNumber, double balance);
	size_t getAccountNumber() const;
	double getBalance() const;

	void setAccountNumber(size_t accountNumber);
	void setBalance(double balance);

	~Account() = default;
};
