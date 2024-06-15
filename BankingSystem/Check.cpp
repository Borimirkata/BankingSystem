#include "Check.h"

Check::Check(const MyString& code,double sum) {
	this->code = code;
	setSum(sum);
}

void Check::setSum(double sum) {
	if (sum <= CheckData::NULL_VALUE) {
		throw std::exception("Sum should be higher than zero");
	}

	this->sum = sum;
}

double Check::getSum() const {
	return sum;
}

const MyString& Check::getCode() const {
	return code;
}