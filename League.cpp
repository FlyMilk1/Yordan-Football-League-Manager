#include "League.h"
#include "PlayedMatch.h"
#include <algorithm>
#include <iostream>

League::League(const std::string& name) : name(name) {}

League::~League() {
    delete[] matches.data();
}

void League::addTeam(const Team& t) {
    if (findTeam(t.name) == nullptr) teams.push_back(t);
}

void League::addMatch(Match* m) {
    matches.push_back(m);
}

Team* League::findTeam(const std::string& tname) {
    for (auto &t : teams) {
        if (t.name == tname) return &t;
    }
    return nullptr;
}

void League::calculateStandings() {
    for (auto &t : teams) t.reset();

    for (Match* m : matches) {
        PlayedMatch* pm = dynamic_cast<PlayedMatch*>(m);
        if (!pm) continue;

        const std::string& home = pm->getHome();
        const std::string& away = pm->getAway();
        int hg = pm->getHomeGoals();
        int ag = pm->getAwayGoals();

        Team* homeTeam = findTeam(home);
        if (!homeTeam) {
            teams.emplace_back(home);
            homeTeam = &teams.back();
        }
        Team* awayTeam = findTeam(away);
        if (!awayTeam) {
            teams.emplace_back(away);
            awayTeam = &teams.back();
        }

        int homePts = 0, awayPts = 0;
        if (hg > ag) homePts = 3;
        else if (hg < ag) awayPts = 3;
        else { homePts = 1; awayPts = 1; }

        homeTeam->updateStats(hg, ag, homePts);
        awayTeam->updateStats(ag, hg, awayPts);
    }
}

void League::printStandings() const {

}

