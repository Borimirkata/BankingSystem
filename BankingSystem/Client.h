#pragma once
#include "User.h"
//#include "MyVector.hpp"
#include "Message.h"
//#include "Account.h"
#include "Bank.h"

class Client:public User{
private:
//Need to add a MyVector for the checks!!!!
	MyString address = "Unknown";
	MyVector<Message> message;
	MyVector<Bank> banks;
	int getBankIndex(const MyString& bankName) const;

public:
	Client() = default;
	Client(const MyString& firstName, const MyString& secondName, const MyString& egn, size_t age, const MyString& role, const MyString& password, const MyString& address);
	

	void pushBank(const Bank& bank);
	void pushMessage(const Message& message);

	void check_avl(const MyString& bankName, size_t accountNumber) const;
	void open(const MyString& bankName);
	void close(const MyString& bankName, size_t accountNumber);
	void redeem(const MyString& bankName, size_t accountNumber, MyString& verificationCode);
	void change(const MyString& newBankName, const MyString& currentBankName, size_t accountNumber);
	void list(const MyString& bankName) const;
	void messages() const;

	virtual void help() const override;
	virtual void whoami() const override;
	//virtual void exit() override;

	~Client() = default;
};
