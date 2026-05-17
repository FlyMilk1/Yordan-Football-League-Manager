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
        std::cout << "\n1) List matches\n2) Enter result\n3) Show standings\n4) Teams\n0) Exit\n> ";
        int choice = -1;
        if (!(std::cin >> choice)) break;

        switch (choice) {
            case 1:
                for (Match* m : league.matches) m->print();
                break;
            case 2: {
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
                break;
            }
            case 3:
                league.calculateStandings();
                league.printStandings();
                break;
            case 4: {
                bool teamMenu = true;
                while (teamMenu) {
                    std::cout << "\n1) List teams\n2) Add team\n3) Edit team\n4) Remove team\n0) Back\n> ";
                    int teamChoice = -1;
                    if (!(std::cin >> teamChoice)) { teamMenu = false; break; }

                    switch (teamChoice) {
                        case 1:
                            for (const auto& t : league.teams) std::cout << t.name << "\n";
                            break;
                        case 2: {
                            std::string name;
                            std::cout << "Team name: ";
                            std::getline(std::cin >> std::ws, name);
                            league.addTeam(Team(name));
                            break;
                        }
                        case 3: {
                            std::string oldName;
                            std::string newName;
                            std::cout << "Current name: ";
                            std::getline(std::cin >> std::ws, oldName);
                            std::cout << "New name: ";
                            std::getline(std::cin >> std::ws, newName);
                            bool ok = league.editTeamName(oldName, newName);
                            std::cout << (ok ? "Updated.\n" : "Update failed.\n");
                            break;
                        }
                        case 4: {
                            std::string name;
                            std::cout << "Team name: ";
                            std::getline(std::cin >> std::ws, name);
                            bool ok = league.removeTeam(name);
                            std::cout << (ok ? "Removed.\n" : "Remove failed.\n");
                            break;
                        }
                        case 0:
                            teamMenu = false;
                            break;
                        default:
                            break;
                    }
                }
                break;
            }
            case 0:
                running = false;
                break;
            default:
                break;
        }
    }

    return 0;
}
