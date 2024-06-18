#pragma once
#include "Client.h"
#include "Bank.h"
#include "Check.h"
#include "HelperFunctions.h"

namespace ThirdPartyData {
	constexpr int SIZE = 3;
}

class Bank;
class Client;

class ThirdPartyEmployee :public User {
private:
	MyVector<Bank*> banks;

	int getBankIndex(const MyString& bankName) const;
	Client* getClient(const MyString& bankName,const MyString& egn) const;

	bool validateCode(const MyString& text) const;

public:
	ThirdPartyEmployee() = default;
	ThirdPartyEmployee(const MyString& firstName, const MyString& secondName, const MyString& egn, size_t age, const MyString& role, const MyString& password);

	void send_check(double sum, const MyString& bankName,const MyString& code, const MyString& egn);
	virtual void help() const override;
	virtual void whoami() const override;
	virtual void exit() const override;
	void addBank(Bank* bank);

	~ThirdPartyEmployee() = default;
};
