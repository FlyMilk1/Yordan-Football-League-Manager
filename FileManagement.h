#pragma once
#include <string>
#include "League.h"

class FileManagement {
public:
	FileManagement();
	void writeToFileLeague(const std::string& leagueIdName, const League& league) const;
	bool loadLeague(const std::string& leagueIdName);
	League* getLoadedLeague();

private:
	League loaded;
};
