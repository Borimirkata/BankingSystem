#pragma once
#include "Client.h"
#include "Bank.h"
#include "Check.h"
#include "HelperFunctions.h"

namespace ThirdPartyData {
	constexpr int SIZE = 0;
}

class Bank;
class Client;

class ThirdPartyEmployee :public User {
private:
	MyVector<Bank*> banks;
	MyVector<Client*> clients;

	int getBankIndex(const MyString& bankName) const;
	int getClientIndex(const MyString& egn) const;

	bool validateCode(const MyString& text) const;

public:
	ThirdPartyEmployee() = default;
	ThirdPartyEmployee(const MyString& firstName, const MyString& secondName, const MyString& egn, size_t age, const MyString& role, const MyString& password);

	void send_check(double sum, const MyString& bankName,const MyString& code, const MyString& egn);
	void help() const override;
	void whoami() const override;
	void addBank(const MyString& bankName);

	~ThirdPartyEmployee() = default;
};
