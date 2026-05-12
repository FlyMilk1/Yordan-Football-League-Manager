#pragma once

#include "Match.h"
#include <iostream>

class ScheduledMatch : public Match {
public:
    ScheduledMatch(const std::string& home, const std::string& away, const std::string& date);
    void print() const override;
};

