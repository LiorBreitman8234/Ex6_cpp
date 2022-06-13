#include <iostream>
#include "sources/league.hpp"
#include "sources/round.hpp"
#include "sources/team.hpp"
#include "sources/game.hpp"
#include "sources/schedule.hpp"
#include "sources/statistics.hpp"
using namespace  BBallLeague;
int main() {
    int state = 0;
    std::vector<team*> teams;
    league* league;
    statistics* stat;
    int choice = -1;
    while(state != 3)
    {
        if(state == 0)
        {
            std::cout << "Welcome to basketball team simulator" << std::endl;
            std::cout << "press 1 to add teams to league" << std::endl;
            std::cout << "press 2 to start league(teams will be added until 20)" << std::endl;
            std::cout << "press 3 to exit"<< std::endl;
            std::cin >> choice;
            if(choice == 1)
            {
                std::string name;
                double talent;
                std::cout << "enter team name";
                std::cin >> name;
                std::cout << "enter team talent (between 0 and 1), press 0 for random";
                std::cin >> talent;
                if(talent == 0)
                {
                    teams.push_back(new team(name));
                }
                else
                {
                    teams.push_back(new team(name, talent));
                }
            }
            else if(choice == 2)
            {
                state = 1;
                std::cout << "starting league!" <<std::endl;
                league = new BBallLeague::league(teams);
            }
            else if(choice == 3)
            {
                state = 3;
                std::cout << "bye bye!" << std::endl;
            }
        }
        else if(state == 1)
        {
            std::cout << " mid season - select action" << std::endl;
            std::cout << "press 1 to play next round" << std::endl;
            std::cout << "press 2 to play whole league" << std::endl;
            std::cout << "press 3 to print round" << std::endl;
            std::cout << "press 4 to show team schedule" << std::endl;
            std::cout << "press 5 to show team record" << std::endl;
            std::cout << "press 6 to exit" << std::endl;
            std::cin >> choice;
            if(choice == 1)
            {
                league->playNextRound();
                if(league->getCurrRoundNum() == 2*(league->getTeams().size()-1))
                {
                    std::cout << "finished league!" << std::endl;
                    state =2 ;
                }
            }
            if(choice == 2)
            {
                league->playLeague();
                std::cout << "finished league!" << std::endl;
                state =2 ;
            }
            if(choice == 3)
            {
                int round = 0;
                std::cout << " what round do you want to print?" << std::endl;
                std::cin >> round;
                league->printRound(round);
            }
            if(choice == 4 || choice == 5)
            {
                int id = 0;
                for(auto* team:league->getTeams())
                {
                    std::cout << team->getName() << " id: " << team->getId() << std::endl;
                }
                std::cout << "what team do you want to see? select by id"<< std::endl;
                std::cin >> id;
                int flag = 0;
                for(auto* team: league->getTeams())
                {
                    if(team->getId() == id)
                    {
                        if(choice == 5)
                        {
                            team->showRecord();
                        }
                        else
                        {
                            team->showSchedule();
                        }
                        flag = 1;
                        break;
                    }
                }
                if(flag == 0)
                {
                    std::cout << "wrong team id" << std::endl;
                }
            }
            if(choice == 6)
            {
                std::cout << "bye bye" << std::endl;
                state = 3;
            }
        }
        else {
            std::cout << " season has ended you can now see statistics about it" << std::endl;
            std::cout << "press 1 to show statistic, else 2 to exit" << std::endl;
            std::cin >> choice;
            if (choice == 2) {
                state = 3;
                std::cout << "bye bye!" << std::endl;
            }
            else if(choice == 1) {
                stat =new statistics(league);
                std::cout << "press 1 for top " << std::endl;
                std::cout << "press 2 to see how many team scored more then they recevied" << std::endl;
                std::cout << "press 3 to see difference between home and away game" << std::endl;
                std::cout << "press 4 to show final table" << std::endl;
                std::cout << "press 5 to show longest winning or losing streak" << std::endl;
                std::cout << "press 6 to exit" << std::endl;
                std::cin >> choice;
                if(choice == 1)
                {
                    int num = 0;
                    std::cout<<"choose number of teams to show" <<std::endl;
                    std::cin >> num;
                    std::cout<<"choose statistic"<< std::endl;
                    std::cout<<"1. record " << std::endl;
                    std::cout<<"2. difference in scored/recevied " << std::endl;
                    std::cout<<"3. home wins " << std::endl;
                    std::cout<<"4. away wins " << std::endl;
                    std::cout<<"5. scored most  " << std::endl;
                    std::cout<<"6. recevied most " << std::endl;
                    std::cin >> choice;
                    if(choice == 1)
                    {
                        stat->top(num,"record");
                    }
                    else if(choice == 2)
                    {
                        stat->top(num,"diff");
                    }
                    else if(choice == 3)
                    {
                        stat->top(num,"home");
                    }
                    else if(choice == 4)
                    {
                        stat->top(num,"away");
                    }
                    else if(choice == 5)
                    {
                        stat->top(num,"scored");
                    }
                    else if(choice == 6)
                    {
                        stat->top(num,"received");
                    }
                }
                else if(choice == 2)
                {
                    stat->scoredMore();
                }
                else if(choice == 3)
                {
                    stat->homeAwayDiff();
                }
                else if(choice == 4)
                {
                    stat->showTable();
                }
                else if(choice == 5)
                {
                    char type;
                    std::cout << "choose streak type, W for wins and L for loses" << std::endl;
                    std::cin >> type;
                    stat->longestStreak(type);
                }
            }
        }
    }
}
