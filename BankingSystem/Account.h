#pragma once
#include "MyString.h"
#include "Client.h"

class Client;

namespace {
	constexpr size_t NULL_VALUE = 0;
}

class Account {
private:
	size_t accountNumber = 0;
	double balance = 0;
	Client* client;

public:
	Account() = default;
	Account(size_t accountNumber, double balance, Client* client);
	size_t getAccountNumber() const;
	double getBalance() const;

	void printAccount() const;

	void setAccountNumber(size_t accountNumber);
	void setBalance(double balance);

	~Account();
};
