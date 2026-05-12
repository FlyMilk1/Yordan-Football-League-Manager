#include "Team.h"

Team::Team(const std::string& name)
    : name(name), points(0), goalsScored(0), goalsAgainst(0) {}

void Team::updateStats(int scored, int conceded, int pts) {
    goalsScored += scored;
    goalsAgainst += conceded;
    points += pts;
}

void Team::reset() {
    points = 0;
    goalsScored = 0;
    goalsAgainst = 0;
}

