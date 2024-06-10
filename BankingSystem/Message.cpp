#include "Message.h"

Message::Message(const MyString& from, const MyString& content) {
	setFrom(from);
	setContent(content);
}

void Message::setFrom(const MyString& from) {
	if (from == nullptr) {
		throw std::exception("Nullptr given");
	}
	this->from = from;
}

void Message::setContent(const MyString& content) {
	if (content == nullptr) {
		throw std::exception("Nullptr given");
	}
	this->content = content;
}

const MyString& Message::getFrom() const {
	return from;
}

const MyString& Message::getContent() const {
	return content;
}