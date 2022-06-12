#include <iostream>
#include "sources/league.hpp"
#include "sources/round.hpp"
#include "sources/team.hpp"
#include "sources/game.hpp"
#include "sources/schedule.hpp"
#include "sources/statistics.hpp"
int main() {
    auto * team1 = new BBallLeague::team("golden state warriors",0.95);
    auto * team2 = new BBallLeague::team("boston celtics",0.95);
    auto * team3 = new BBallLeague::team("miami heat",0.9);
    auto * team4 = new BBallLeague::team("dallas mavricks",0.9);
    auto * team5 = new BBallLeague::team("milwakee bucks",0.85);
    auto * team6 = new BBallLeague::team("philidelphia 76ers",0.85);
    auto * team7 = new BBallLeague::team("phonix suns",0.85);
    auto * team8 = new BBallLeague::team("memphis grizzlis",0.85);
    auto * team9 = new BBallLeague::team("denver nuggets",0.8);
    auto * team10 = new BBallLeague::team("minasotta timberwolves",0.8);
    auto * team11 = new BBallLeague::team("chicago bulls",0.8);
    auto * team12 = new BBallLeague::team("new orleans pelicens",0.8);
    auto * team13 = new BBallLeague::team("utah jazz",0.8);
    auto * team14 = new BBallLeague::team("atlanta hawks",0.8);
    auto * team15 = new BBallLeague::team("toronto raptors",0.8);
    auto * team16 = new BBallLeague::team("brooklyn nets",0.8);
    auto * team17 = new BBallLeague::team("san antonio spurs",0.7);
    auto * team18 = new BBallLeague::team("los angeles clippers",0.75);
    auto * team19 = new BBallLeague::team("charlotte hornets",0.7);
    auto * team20 = new BBallLeague::team("clevland cavelries",0.75);
    std::vector<BBallLeague::team*> teams;
    teams.push_back(team1);
    teams.push_back(team2);
    teams.push_back(team3);
    teams.push_back(team4);
    teams.push_back(team5);
    teams.push_back(team6);
    teams.push_back(team7);
    teams.push_back(team8);
    teams.push_back(team9);
    teams.push_back(team10);
    teams.push_back(team11);
    teams.push_back(team12);
    teams.push_back(team13);
    teams.push_back(team14);
    teams.push_back(team15);
    teams.push_back(team16);
    teams.push_back(team17);
    teams.push_back(team18);
    teams.push_back(team19);
    teams.push_back(team20);
    BBallLeague::league* other;
    (other = new BBallLeague::league(teams));
    BBallLeague::statistics* stat;
    try{
        stat = new BBallLeague::statistics(other);
    }
    catch (std::exception& e)
    {
        std::cout << e.what() << std::endl;
    }
    (other->playLeague());
    std::cout << (other->getCurrRoundNum(), 2*(other->getTeams().size()-1)) << std::endl;
    (stat = new BBallLeague::statistics(other));
    try{
        other->playNextRound();
    }
    catch (std::exception& e)
    {
        std::cout << e.what() << std::endl;
    }
    try{
        stat->top(25,"record");
    }
    catch (std::exception& e)
    {
        std::cout << e.what() << std::endl;
    }

    try{
        stat->top(15,"difference");
    }
    catch (std::exception& e)
    {
        std::cout << e.what() << std::endl;
    }
    
    (stat->showTable());
    (stat->top(10,"record"));
}
