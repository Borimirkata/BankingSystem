#include "HelperFunctions.h"

bool isSubstring(const MyString& string, const MyString& substring) {
	int stringLength = string.length();
	int subStringLength = substring.length();

	int difference = stringLength - subStringLength;

	for (int i = 0; i <= difference; i++) {
		int j=0;
		
		while (j < subStringLength && string[i + j] == substring[j]) {
			j++;
		}
		if (j == subStringLength) {
			return true;
		}
	}
	return false;
}

bool isLowerCase(char ch) {
	if (ch >= 'a' && ch <= 'z') {
		return true;
	}
	return false;
}

bool isUpperCase(char ch) {
	if (ch >= 'A' && ch <= 'Z') {
		return true;
	}
	return false;
}

bool isDigit(char ch) {
	if (ch >= '0' && ch <= '9') {
		return true;
	}
	return false;
}

unsigned getDigitFromChar(char ch)
{
	if (!isDigit(ch)) {
		throw std::exception("Invalid code");
	}
	return ch - '0';
}
unsigned getNumFromStr(const MyString& str)
{
	size_t len = str.length();
	unsigned mult = 1;
	unsigned res = 0;
	for (int i = len - 1; i >= 0; i--)
	{
		res += mult * getDigitFromChar(str[i]);
		mult *= 10;
	}
	return res;
}