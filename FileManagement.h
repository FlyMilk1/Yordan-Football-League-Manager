#pragma once
#include <string>

#include "League.h"

void writeToFileLeague(const std::string leagueIdName, const League& league);
void readFromFileLeague(const std::string leagueIdName, League& league);
