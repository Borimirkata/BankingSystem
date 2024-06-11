#pragma once
#include "MyVector.hpp"
#include "Account.h"
#include "Request.h"


class Bank {
private:
	MyString bankName = "Unknown";
	MyVector<Account> accounts;
	MyVector<Request> requests;

	int getAccountIdx(size_t accountNumber) const;
	int getRequestIdx(const MyString& firstName, const MyString& secondName,const MyString& egn,size_t age);

public:
	Bank() = default;
	Bank(const MyString& bankName);

	double getAccountBalance(size_t number);
	void addAccount(size_t accountNumber,double balance);
	void addRequests(const MyString& role,const MyString& firstName,const MyString& secondName,const MyString& egn,size_t age);

	void getCurrentAccount(size_t accountNumber, Account*& currentAcc);
	void getCurrentRequest(const MyString& firstName, const MyString& secondName, const MyString& egn, size_t age, Request*& currentReq);

	void printAccounts() const;
	
	void setBankName(const MyString& bankName);
	const MyString& getBankName() const;
};
