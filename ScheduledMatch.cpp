#include "ScheduledMatch.h"

ScheduledMatch::ScheduledMatch(const std::string& home, const std::string& away, const std::string& date)
    : Match(home, away, date) {}

void ScheduledMatch::print() const {
    std::cout << "Scheduled: " << homeTeam << " vs " << awayTeam << " on " << date << "\n";
}

