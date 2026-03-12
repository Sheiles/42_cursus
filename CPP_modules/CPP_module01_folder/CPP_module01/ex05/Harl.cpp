#include "Harl.hpp"
#include <iostream>

typedef void (Harl::*HarlMemFuncPtr)(void);

static HarlMemFuncPtr kFuncs[4] = {
	&Harl::debug,
	&Harl::info,
	&Harl::warning,
	&Harl::error
};

static const char *kLevels[4] = {
	"DEBUG",
	"INFO",
	"WARNING",
	"ERROR"
};

Harl::Harl(void) {}

Harl::~Harl(void) {}

void Harl::complain(std::string level)
{
	int i = 0;
	while (i < 4)
	{
		if (kLevels[i] == level)
		{
			(this->*kFuncs[i])();
			return ;
		}
		i++;
	}
	std::cout << "[ Unknown level ]" << std::endl;
}
