#pragma once
#include "MyString.h"
#include "SerializeFunctions.h"

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
	void setCode(const MyString& code);

	void writeToFile(std::ofstream& ofs) const;
	void readFromFile(std::ifstream& ifs);

	~Check() = default;

};
