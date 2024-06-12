#pragma once
#include "Request.h"
#include "MyVector.hpp"
#include "Client.h"


class Employee :public User {
private:
	MyString bankAssociated="Unknown";
	MyVector<Request> task;

public:
	Employee() = default;
	Employee(const MyString& bankName);

	void tasks() const;
	void view(size_t idx) const;
	void approve(size_t idx);
	void disapprove(size_t idx, const MyString& message);
	void validate(size_t idx);

	virtual void help() const override;
	virtual void whoami() const override;
};
