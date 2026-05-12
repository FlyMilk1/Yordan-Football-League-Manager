#pragma once

#include <string>
#include <vector>
#include "Team.h"
#include "Match.h"

class League {
public:
    std::string name;
    std::vector<Team> teams;
    std::vector<Match*> matches;

    League(const std::string& name = "");
    ~League();

    void addTeam(const Team& t);
    void addMatch(Match* m);

    void calculateStandings();

    void printStandings() const;

    Team* findTeam(const std::string& name);
};

