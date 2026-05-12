#include "PlayedMatch.h"

PlayedMatch::PlayedMatch(const std::string& home, const std::string& away, const std::string& date,
                         int homeGoals, int awayGoals)
    : Match(home, away, date), homeGoals(homeGoals), awayGoals(awayGoals) {}

int PlayedMatch::getHomeGoals() const { return homeGoals; }
int PlayedMatch::getAwayGoals() const { return awayGoals; }

void PlayedMatch::print() const {
    std::cout << "Played: " << homeTeam << " " << homeGoals << " - " << awayGoals << " " << awayTeam << " on " << date << "\n";
}

