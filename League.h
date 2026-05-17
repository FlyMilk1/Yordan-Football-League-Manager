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
    bool recordMatchResult(const std::string& home, const std::string& away, const std::string& date,
                           int homeGoals, int awayGoals);
    bool editTeamName(const std::string& oldName, const std::string& newName);
    bool removeTeam(const std::string& name);

    void calculateStandings();

    void printStandings() const;

    Team* findTeam(const std::string& name);
};
