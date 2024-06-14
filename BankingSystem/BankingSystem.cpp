#include "BankingSystem.h"
# include "Bank.h"
# include "Client.h"

MyVector<Bank> BankingSystem::banks;

void BankingSystem::create_bank(const MyString& bankName) {
	banks.push_back(Bank(bankName));
}

Bank* BankingSystem::get_bank_by_name(const MyString& bankName)
{
	int index = -1;
	size_t banksCount = banks.getSize();

	for (size_t i = 0; i < banksCount; i++) {
		if ((banks[i].getBankName() == bankName)) {
			return &banks[i];
		}
	}
	return nullptr;
}