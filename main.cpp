#include <iostream>
#include <string>
#include "League.h"
#include "ScheduledMatch.h"
#include "PlayedMatch.h"

int main() {
    League league("Demo League");
    league.addTeam(Team("Alpha"));
    league.addTeam(Team("Beta"));
    league.addTeam(Team("Gamma"));
    league.addTeam(Team("Delta"));

    league.addMatch(new ScheduledMatch("Alpha", "Beta", "2026-05-17"));
    league.addMatch(new ScheduledMatch("Gamma", "Delta", "2026-05-18"));

    bool running = true;
    while (running) {
        std::cout << "\n1) List matches\n2) Enter result\n3) Show standings\n0) Exit\n> ";
        int choice = -1;
        if (!(std::cin >> choice)) break;

        if (choice == 1) {
            for (Match* m : league.matches) m->print();
        } else if (choice == 2) {
            std::string home;
            std::string away;
            std::string date;
            int homeGoals = 0;
            int awayGoals = 0;

            std::cout << "Home team: ";
            std::getline(std::cin >> std::ws, home);
            std::cout << "Away team: ";
            std::getline(std::cin >> std::ws, away);
            std::cout << "Date (YYYY-MM-DD): ";
            std::getline(std::cin >> std::ws, date);
            std::cout << "Home goals: ";
            std::cin >> homeGoals;
            std::cout << "Away goals: ";
            std::cin >> awayGoals;

            bool recorded = league.recordMatchResult(home, away, date, homeGoals, awayGoals);
            if (recorded) {
                std::cout << "Result recorded.\n";
            } else {
                std::cout << "Match not found or already played.\n";
            }
        } else if (choice == 3) {
            league.calculateStandings();
            league.printStandings();
        } else if (choice == 0) {
            running = false;
        }
    }

    return 0;
}
