#include "Account.hpp"
#include <iostream>
#include <iomanip>
#include <ctime>

int Account::_nbAccounts = 0;
int Account::_totalAmount = 0;
int Account::_totalNbDeposits = 0;
int Account::_totalNbWithdrawals = 0;

static void print2(int v)
{
	std::cout << std::setw(2) << std::setfill('0') << v;
}

static void print4(int v)
{
	std::cout << std::setw(4) << std::setfill('0') << v;
}

void Account::_displayTimestamp(void)
{
	std::time_t now = std::time(NULL);
	std::tm *lt = std::localtime(&now);

	std::cout << "[";
	print4(lt->tm_year + 1900);
	print2(lt->tm_mon + 1);
	print2(lt->tm_mday);
	std::cout << "_";
	print2(lt->tm_hour);
	print2(lt->tm_min);
	print2(lt->tm_sec);
	std::cout << "] ";
	std::cout << std::setfill(' '); // reset
}

Account::Account(void) {}

Account::Account(int initial_deposit)
	: _accountIndex(Account::_nbAccounts)
	, _amount(initial_deposit)
	, _nbDeposits(0)
	, _nbWithdrawals(0)
{
	Account::_displayTimestamp();
	std::cout << "index:" << this->_accountIndex << ";"
			  << "amount:" << this->_amount << ";"
			  << "created" << std::endl;

	Account::_nbAccounts++;
	Account::_totalAmount += this->_amount;
}

Account::~Account(void)
{
	Account::_displayTimestamp();
	std::cout << "index:" << this->_accountIndex << ";"
			  << "amount:" << this->_amount << ";"
			  << "closed" << std::endl;
}

int Account::getNbAccounts(void) { return Account::_nbAccounts; }
int Account::getTotalAmount(void) { return Account::_totalAmount; }
int Account::getNbDeposits(void) { return Account::_totalNbDeposits; }
int Account::getNbWithdrawals(void) { return Account::_totalNbWithdrawals; }

void Account::displayAccountsInfos(void)
{
	Account::_displayTimestamp();
	std::cout << "accounts:" << Account::getNbAccounts() << ";"
			  << "total:" << Account::getTotalAmount() << ";"
			  << "deposits:" << Account::getNbDeposits() << ";"
			  << "withdrawals:" << Account::getNbWithdrawals()
			  << std::endl;
}

void Account::displayStatus(void) const
{
	Account::_displayTimestamp();
	std::cout << "index:" << this->_accountIndex << ";"
			  << "amount:" << this->_amount << ";"
			  << "deposits:" << this->_nbDeposits << ";"
			  << "withdrawals:" << this->_nbWithdrawals
			  << std::endl;
}

void Account::makeDeposit(int deposit)
{
	Account::_displayTimestamp();
	std::cout << "index:" << this->_accountIndex << ";"
			  << "p_amount:" << this->_amount << ";"
			  << "deposit:" << deposit << ";";

	this->_amount += deposit;
	this->_nbDeposits++;

	Account::_totalAmount += deposit;
	Account::_totalNbDeposits++;

	std::cout << "amount:" << this->_amount << ";"
			  << "nb_deposits:" << this->_nbDeposits
			  << std::endl;
}

bool Account::makeWithdrawal(int withdrawal)
{
	Account::_displayTimestamp();
	std::cout << "index:" << this->_accountIndex << ";"
			  << "p_amount:" << this->_amount << ";";

	if (withdrawal > this->_amount)
	{
		std::cout << "withdrawal:refused" << std::endl;
		return false;
	}

	std::cout << "withdrawal:" << withdrawal << ";";

	this->_amount -= withdrawal;
	this->_nbWithdrawals++;

	Account::_totalAmount -= withdrawal;
	Account::_totalNbWithdrawals++;

	std::cout << "amount:" << this->_amount << ";"
			  << "nb_withdrawals:" << this->_nbWithdrawals
			  << std::endl;
	return true;
}

int Account::checkAmount(void) const
{
	return this->_amount;
}
