#include "League.h"
#include "PlayedMatch.h"
#include <algorithm>
#include <iostream>

League::League(const std::string& name) : name(name) {}

League::~League() {
    for (Match* m : matches) {
        delete m;
    }
    matches.clear();
}

void League::addTeam(const Team& t) {
    if (findTeam(t.name) == nullptr) teams.push_back(t);
}

void League::addMatch(Match* m) {
    matches.push_back(m);
}

bool League::recordMatchResult(const std::string& home, const std::string& away, const std::string& date,
                               int homeGoals, int awayGoals) {
    for (size_t i = 0; i < matches.size(); ++i) {
        Match* m = matches[i];
        if (m->getHome() == home && m->getAway() == away && m->getDate() == date) {
            if (dynamic_cast<PlayedMatch*>(m) != nullptr) return false;
            delete m;
            matches[i] = new PlayedMatch(home, away, date, homeGoals, awayGoals);
            return true;
        }
    }
    return false;
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
    auto copy = teams;
    std::sort(copy.begin(), copy.end(), [](const Team& a, const Team& b){
        if (a.points != b.points) return a.points > b.points;
        int gdA = a.goalsScored - a.goalsAgainst;
        int gdB = b.goalsScored - b.goalsAgainst;
        if (gdA != gdB) return gdA > gdB;
        if (a.goalsScored != b.goalsScored) return a.goalsScored > b.goalsScored;
        return a.name < b.name;
    });

    std::cout << "Standings for league: " << name << "\n";
    std::cout << "Pos | Team                 | Pts | GF | GA | GD\n";
    std::cout << "-----------------------------------------------\n";
    int pos = 1;
    for (const auto &t : copy) {
        int gd = t.goalsScored - t.goalsAgainst;
        char buf[64];
        snprintf(buf, sizeof(buf), "%3d | %-20s | %3d | %2d | %2d | %3d\n",
                 pos, t.name.c_str(), t.points, t.goalsScored, t.goalsAgainst, gd);
        std::cout << buf;
        ++pos;
    }
}
