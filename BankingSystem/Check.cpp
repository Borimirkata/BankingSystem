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

void Check::setCode(const MyString& code) {
	this->code = code;
}

double Check::getSum() const {
	return sum;
}

const MyString& Check::getCode() const {
	return code;
}

void Check::writeToFile(std::ofstream& ofs) const {
	writeStringToFile(ofs, code);
	ofs.write((const char*)&sum, sizeof(double));
}

void Check::readFromFile(std::ifstream& ifs) {
	code = readStringFromFile(ifs);
	ifs.read((char*)&sum, sizeof(double));
}