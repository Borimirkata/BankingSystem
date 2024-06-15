#pragma once
#include "MyString.h"

namespace CheckData {
	constexpr int NULL_VALUE = 0;
}

class Check {
private:
	MyString code="*";
	double sum = 0;

public:
	Check() = default;
	Check(const MyString& code, double sum);

	double getSum() const;
	const MyString& getCode() const;

	void setSum(double sum);

};
