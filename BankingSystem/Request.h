#pragma once
#include "MyString.h"
#include "Client.h"


class Client;

namespace RequestData {
	constexpr int DEF_VALUE = 0;

	const MyString type1 = "Open";
	const MyString type2 = "Close";
	const MyString type3 = "Change";
	const MyString approvedChange = "(approved)";
}

class Request {
private:
	MyString type = "Unknown";
	Client* client=nullptr;
	int accountNum = RequestData::DEF_VALUE;
	MyString nameBank = "Unknown";
	double money = RequestData::DEF_VALUE;

public:

	Request() = default;
	Request(const MyString& type, Client* client);
	Request(const MyString& type, Client* client, int accountNumber);
	Request(const MyString& type, Client* client, int accountNumber, const MyString& nameBank);
	Request(const MyString& type, Client* client, int accountNumber, const MyString& nameBank,double money);

	const MyString& getType() const;
	void setType(const MyString& type);

	const MyString& getNameOfBank() const;

	int getAccountNum() const;
	double getMoney() const;

	void setMoney(double money);

	void printRequest() const;

	Client* getClient() const;

	void writeToFile(std::ofstream& ofs) const;
	void readFromFile(std::ifstream& ifs);

	~Request();
};
