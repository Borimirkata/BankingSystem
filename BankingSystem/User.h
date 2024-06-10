#pragma once
#include "MyString.h"

namespace Constants{
	const uint16_t MIN_AGE = 18;
	const uint16_t MAX_AGE = 100;
}

class User {
private:
	MyString name="Unknown";
	MyString egn="N/A";
	uint16_t age=0;
	MyString role="Unknown";
	MyString password="N/A";

protected:
	bool validateAge(uint16_t age) const;

public:
	User() = default;
	User(const MyString& name, const MyString& egn, uint16_t age, const MyString& role, const MyString& password);

	const MyString& getName() const;
	const MyString& getEgn() const;
	uint16_t getAge() const;
	const MyString& getRole() const;
	const MyString& getPassword() const;


	virtual void help() const = 0;
	virtual void whoami() const = 0;
	virtual void exit() = 0;

	virtual ~User() = default;
};
