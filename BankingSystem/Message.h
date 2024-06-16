#pragma once
#include "MyString.h"
#include "HelperFunctions.h"

namespace MessageData {
	constexpr int VALUE = -1;
}

class Message {
private:
	MyString from = "Unknown";
	MyString content = "Empty";
	MyString bankName = "Unknown";
	MyString code = "*";
	int accNumber = MessageData::VALUE;
public:
	Message() = default;
	Message(const MyString& from, const MyString& content, const MyString& bankName);
	Message(const MyString& from, const MyString& content, const MyString& bankName,const MyString& code);
	Message(const MyString& from, const MyString& content, const MyString& bankName, int number);

	const MyString& getFrom() const;
	const MyString& getContent() const;
	const MyString& getBankName() const;
	const MyString& getCode() const;

	int getAccNumber() const;
	void setFrom(const MyString& from);
	void setContent(const MyString& content);

	void printMessage() const;

	~Message() = default;
};

