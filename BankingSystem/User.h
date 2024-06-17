#pragma once
#include "MyString.h"

namespace UserData{
	const size_t MIN_AGE = 18;
	const size_t MAX_AGE = 100;
}

namespace {
	const MyString type1 = "Open";
	const MyString type2 = "Close";
	const MyString type3 = "Change";
	const MyString approvedChange = "(approved)";

}
//this namespace is like a global one because everyone uses them

class User {
protected:
	MyString firstName = "Unknown";
	MyString secondName = "Unknown";
	MyString egn = "N/A";
	size_t age = 0;
	MyString role = "Unknown";
	MyString password = "N/A";

public:
	User() = default;
	User(const MyString& firstName, const MyString& secondName, const MyString& egn, size_t age, const MyString& role, const MyString& password);

	const MyString& getFirstName() const;
	const MyString& getSecondName() const;
	const MyString& getEgn() const;
	size_t getAge() const;
	const MyString& getRole() const;
	const MyString& getPassword() const;


	virtual void help() const = 0;
	virtual void whoami() const = 0;
	virtual void exit() const = 0;

	virtual ~User() = default;
};
