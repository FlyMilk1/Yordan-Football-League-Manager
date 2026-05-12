#pragma once

#include <string>

class Match {
protected:
    std::string homeTeam;
    std::string awayTeam;
    std::string date;

public:
    Match(const std::string& home, const std::string& away, const std::string& date);
    virtual ~Match();

    const std::string& getHome() const;
    const std::string& getAway() const;
    const std::string& getDate() const;

    virtual void print() const = 0;
};

