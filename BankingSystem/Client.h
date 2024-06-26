#pragma once
#include "User.h"
#include "Message.h"
#include "Bank.h"
#include "Check.h"

class Bank;


namespace ClientData {
	const MyString type1 = "Open";
	const MyString type2 = "Close";
	const MyString type3 = "Change";
}

class Client :public User {
private:
	MyString address = "Unknown";
	MyVector<Message> message;
	MyVector<Bank*> banks;
	MyVector<Check> checks;

	int getBankIndex(const MyString& bankName) const;
	int getCheckIndex(const MyString& code) const;

	void addCheck(const Check& check);

public:
	Client() = default;
	Client(const MyString& firstName, const MyString& secondName, const MyString& egn, size_t age, const MyString& role, const MyString& password, const MyString& address);
	Bank* getBank(const MyString& bankName);

	void addMessage(const Message& message);

	Message* getMessageAtIndex(size_t index);
	void receiveCheck(const Check& check);
	void addBank(Bank* bank);

	void check_avl(const MyString& bankName, size_t accountNumber) const;
	void open(const MyString& bankName);
	void close(const MyString& bankName, size_t accountNumber);
	void redeem(const MyString& bankName, size_t accountNumber, const MyString& verificationCode);
	void change(const MyString& newBankName, const MyString& currentBankName, size_t accountNumber);
	void list(const MyString& bankName) const;
	void messages() const;

	virtual void help() const override;
	virtual void whoami() const override;
	virtual void exit() const override;

	void writeToFile(std::ofstream& ofs) const;
	void readFromFile(std::ifstream& ifs);

	~Client();
};
