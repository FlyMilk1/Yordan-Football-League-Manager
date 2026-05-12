#pragma once

#include "Match.h"
#include <iostream>

class PlayedMatch : public Match {
private:
    int homeGoals;
    int awayGoals;

public:
    PlayedMatch(const std::string& home, const std::string& away, const std::string& date,
                int homeGoals, int awayGoals);

    int getHomeGoals() const;
    int getAwayGoals() const;

    void print() const override;
};

