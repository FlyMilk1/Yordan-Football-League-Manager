#include "FileManagement.h"
#include "PlayedMatch.h"
#include <fstream>
#include <iostream>

#include "ScheduledMatch.h"

void writeToFileLeague(const std::string leagueIdName, const League& league) {
    std::ofstream outFile("league_" + leagueIdName + ".txt");
    if (!outFile) {
        std::cerr << "Error opening file for writing.\n";
        return;
    }

    outFile << league.name << "\n";
    outFile << league.teams.size() << "\n";
    for (const Team& t : league.teams) {
        outFile << t.name << " " << t.points << " " << t.goalsScored << " " << t.goalsAgainst << "\n";
    }

    outFile << league.matches.size() << "\n";
    for (const Match* m : league.matches) {
        const PlayedMatch* pm = dynamic_cast<const PlayedMatch*>(m);
        if (pm) {
            outFile << "P " << pm->getHome() << " " << pm->getAway() << " " << pm->getDate() << " "
                    << pm->getHomeGoals() << " " << pm->getAwayGoals() << "\n";
        } else {
            outFile << "S " << m->getHome() << " " << m->getAway() << " " << m->getDate() << "\n";
        }
    }
}

void readFromFileLeague(const std::string leagueIdName, League& league) {
    std::ifstream inFile("league_" + leagueIdName + ".txt");
    if (!inFile) {
        std::cerr << "Error opening file for reading.\n";
        return;
    }

    std::getline(inFile, league.name);
    int numTeams;
    inFile >> numTeams;
    inFile.ignore();

    for (int i = 0; i < numTeams; ++i) {
        Team t;
        inFile >> t.name >> t.points >> t.goalsScored >> t.goalsAgainst;
        league.teams.push_back(t);
    }

    int numMatches;
    inFile >> numMatches;
    inFile.ignore();

    for (int i = 0; i < numMatches; ++i) {
        char matchType;
        inFile >> matchType;
        if (matchType == 'P') {
            std::string home;
            std::string away;
            std::string date;
            int homeGoals;
            int awayGoals;
            inFile >> home >> away >> date >> homeGoals >> awayGoals;
            league.matches.push_back(new PlayedMatch(home, away, date, homeGoals, awayGoals));
        } else {
            std::string home;
            std::string away;
            std::string date;
            inFile >> home >> away >> date;
            league.matches.push_back(new ScheduledMatch(home, away, date));
        }
    }
}
