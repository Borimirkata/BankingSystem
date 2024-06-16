#pragma once
#include "MyString.h"
#include "Client.h"


class Client;

namespace {
	constexpr size_t MIN_AGE_ = 18;
	constexpr size_t MAX_AGE_ = 100;
	constexpr int DEF_VALUE = 0;
}

class Request {
private:
	MyString type = "Unknown";
	Client* client;
	int accountNum = DEF_VALUE;
	MyString nameBank = "Unknown";

public:

	Request() = default;
	Request(const MyString& type, Client* client);
	Request(const MyString& type, Client* client, int accountNumber);
	Request(const MyString& type, Client* client, int accountNumber, const MyString& nameBank);

	const MyString& getType() const;
	const MyString& getFirstName() const;
	const MyString& getSecondName() const;
	const MyString& getEgn() const;
	size_t getAge() const;

	int getAccountNum() const;

	void printRequest() const;

	Client* getClient() const;

	~Request();
};
