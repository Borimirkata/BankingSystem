#pragma once
#include "MyString.h"
#include "Client.h"


class Client;

namespace {
	constexpr size_t MIN_AGE_ = 18;
	constexpr size_t MAX_AGE_ = 100;
}

class Request {
private:
	MyString type = "Unknown";
	Client* client;

public:
	Request() = default;
	Request(const MyString& type, Client* client);

	const MyString& getType() const;
	const MyString& getFirstName() const;
	const MyString& getSecondName() const;
	const MyString& getEgn() const;
	size_t getAge() const;

	void printRequest() const;

	Client* getClient() const;

	~Request() = default;
};
