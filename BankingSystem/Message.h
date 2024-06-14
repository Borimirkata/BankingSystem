#pragma once
#include "MyString.h"

class Message {
private:
	MyString from = "Unknown";
	MyString content = "Empty";
	MyString bankName = "Unknown";
public:
	Message() = default;
	Message(const MyString& from, const MyString& content, const MyString& bankName);

	const MyString& getFrom() const;
	const MyString& getContent() const;
	const MyString& getBankName() const;
	void setFrom(const MyString& from);
	void setContent(const MyString& content);

	void printMessage() const;

	~Message() = default;
};

