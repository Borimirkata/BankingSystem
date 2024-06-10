#include "Message.h"

void Message::setFrom(const MyString& from) {
	this->from = from;
}

void Message::setContent(const MyString& content) {
	this->content = content;
}

const MyString& Message::getFrom() const {
	return from;
}

const MyString& Message::getContent() const {
	return content;
}