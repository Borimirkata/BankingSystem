#pragma once
#include "MyString.h"

bool isSubstring(const MyString& string, const MyString& substring);

bool isLowerCase(char ch);
bool isUpperCase(char ch);
bool isDigit(char ch);

unsigned getDigitFromChar(char ch);
unsigned getNumFromStr(const MyString& str);

