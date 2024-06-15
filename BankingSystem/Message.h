#pragma once
#include "MyString.h"

namespace MessageData {
	constexpr int VALUE = -1;
}

class Message {
private:
	MyString from = "Unknown";
	MyString content = "Empty";
	MyString bankName = "Unknown";
	int accNumber = MessageData::VALUE;
public:
	Message() = default;
	Message(const MyString& from, const MyString& content, const MyString& bankName);
	Message(const MyString& from, const MyString& content, const MyString& bankName, int number);

	const MyString& getFrom() const;
	const MyString& getContent() const;
	const MyString& getBankName() const;
	void setFrom(const MyString& from);
	void setContent(const MyString& content);

	void printMessage() const;

	~Message() = default;
};

