#include <iostream>
#include <string>
#include "League.h"
#include "ScheduledMatch.h"
#include "PlayedMatch.h"
#include "FileManagement.h"

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
        std::cout << "\n1) List matches\n2) Enter result\n3) Edit result\n4) Show standings\n5) Teams\n6) Leagues\n0) Exit\n> ";
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
            case 3: {
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
                std::cout << "New home goals: ";
                std::cin >> homeGoals;
                std::cout << "New away goals: ";
                std::cin >> awayGoals;

                bool edited = league.editMatchResult(home, away, date, homeGoals, awayGoals);
                if (edited) {
                    std::cout << "Result updated.\n";
                } else {
                    std::cout << "Played match not found.\n";
                }
                break;
            }
            case 4:
                league.calculateStandings();
                league.printStandings();
                break;
            case 5: {
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
            case 6: {
                bool leagueMenu = true;
                while (leagueMenu) {
                    std::cout << "\n1) Save league\n2) Load league\n0)\n3) Edit league\nBack\n> ";
                    int leagueChoice = -1;
                    if (!(std::cin >> leagueChoice)) { leagueMenu = false; break; }

                    switch (leagueChoice) {
                        case 1: {
                            std::string id;
                            std::cout << "League ID: ";
                            std::getline(std::cin >> std::ws, id);
                            writeToFileLeague(id, league);
                            break;
                        }
                        case 2: {
                            std::string id;
                            std::cout << "League ID: ";
                            std::getline(std::cin >> std::ws, id);
                            League loaded;
                            readFromFileLeague(id, loaded);
                            if (!loaded.name.empty()) {
                                league = loaded;
                                std::cout << "League loaded.\n";
                            } else {
                                std::cout << "Failed to load league.\n";
                            }
                            break;
                        }
                        case 0:
                            leagueMenu = false;
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
