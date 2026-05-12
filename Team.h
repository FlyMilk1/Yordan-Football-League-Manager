#pragma once

#include <string>

class Team {
public:
    std::string name;
    int points;
    int goalsScored;
    int goalsAgainst;

    Team(const std::string& name = "");

    void updateStats(int scored, int conceded, int pts);

    void reset();
};

