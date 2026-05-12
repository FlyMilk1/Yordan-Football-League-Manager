#include "Match.h"

Match::Match(const std::string& home, const std::string& away, const std::string& date)
    : homeTeam(home), awayTeam(away), date(date) {}

Match::~Match() {}

const std::string& Match::getHome() const { return homeTeam; }
const std::string& Match::getAway() const { return awayTeam; }
const std::string& Match::getDate() const { return date; }

