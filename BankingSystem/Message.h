#pragma once
#include "MyString.h"

class Message {
private:
	MyString from = "Unknown";
	MyString content = "Empty";

public:
	Message() = default;
	Message(const MyString& from, const MyString& content);

	const MyString& getFrom() const;
	const MyString& getContent() const;
	void setFrom(const MyString& from);
	void setContent(const MyString& content);

	~Message() = default;
};
