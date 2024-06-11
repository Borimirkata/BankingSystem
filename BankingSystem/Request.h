#pragma once
#include "MyString.h"

namespace {
	constexpr size_t MIN_AGE_ = 18;
	constexpr size_t MAX_AGE_ = 100;
}

class Request{
private:
	MyString type = "Unknown";
	MyString firstName = "Unknown";
	MyString secondName = "Unknown";
	MyString egn = "Unknown";
	size_t age=0;

public:
	Request() = default;
	Request(const MyString& type, const MyString& firstName, const MyString& secondName, const MyString& egn, size_t age);

	const MyString& getType() const;
	const MyString& getFirstName() const;
	const MyString& getSecondName() const;
	const MyString& getEgn() const;
	size_t getAge() const;

	~Request() = default;
};
