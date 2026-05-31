#include "FileManagement.h"
#include "PlayedMatch.h"
#include <fstream>
#include <iostream>

void writeToFileLeague(const int leagueIdName, const League& league) {
    std::ofstream outFile("league_" + std::to_string(leagueIdName) + ".txt");
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
