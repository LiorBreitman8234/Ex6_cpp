//
// Created by bravo8234 on 12/06/2022.
//
#include "doctest.h"
#include "sources/league.hpp"
#include "sources/statistics.hpp"
#include "sources/team.hpp"
TEST_CASE("good league, all my teams, play league using some round and then rest of league")
{
    BBallLeague::league* good;
    CHECK_NOTHROW(good = new BBallLeague::league());
    BBallLeague::statistics* stat;
    CHECK_THROWS(stat = new BBallLeague::statistics(good));
    CHECK_THROWS_MESSAGE(stat = new BBallLeague::statistics(good),"league didnt finish yet");
    for(int i =0; i < 5;i++)
    {
        CHECK_NOTHROW(good->playNextRound());
    }
    CHECK_THROWS(good->printRound(40));
    CHECK_THROWS(good->printRound(-1));
    CHECK_NOTHROW(good->playLeague());
    CHECK_EQ(good->getCurrRoundNum(), 2*(good->getTeams().size()-1));
    CHECK_NOTHROW(stat = new BBallLeague::statistics(good));
    CHECK_THROWS(good->playNextRound());
    CHECK_THROWS_MESSAGE(good->playNextRound(),"league ended, cant play more rounds");
    CHECK_THROWS(stat->top(25,"record"));
    CHECK_THROWS_MESSAGE(stat->top(25,"record"),"num bigger then amount of teams");
    CHECK_THROWS(stat->top(15,"difference"));
    CHECK_THROWS_MESSAGE(stat->top(15,"difference"),"no such statistic");
    CHECK_NOTHROW(stat->showTable());
    CHECK_NOTHROW(stat->top(10,"record"));
    CHECK_NOTHROW(stat->top(10,"diff"));

}
TEST_CASE("Bad league initializing")
{
    auto * first = new BBallLeague::team("macabi tel aviv");
    auto* second = new BBallLeague::team("macabi tel aviv");
    std::vector<BBallLeague::team*> test1;
    test1.push_back(first);
    test1.push_back(second);
    BBallLeague::league* bad;
    CHECK_THROWS(bad = new BBallLeague::league(test1));
    CHECK_THROWS_MESSAGE(bad = new BBallLeague::league(test1),"2 teams with the same name");
    std::vector<BBallLeague::team*> test2;
    test2.reserve(25);
    for(int i =0; i < 25;i++)
    {
        test2.push_back(first);
    }
    CHECK_THROWS(bad = new BBallLeague::league(test1));
    CHECK_THROWS_MESSAGE(bad = new BBallLeague::league(test1),"too many teams");
}
TEST_CASE("good league, other teams, playing all the league at once")
{
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
    CHECK_NOTHROW(other = new BBallLeague::league(teams));
    BBallLeague::statistics* stat;
    CHECK_THROWS(stat = new BBallLeague::statistics(other));
    CHECK_THROWS_MESSAGE(stat = new BBallLeague::statistics(other),"league didnt finish yet");
    CHECK_NOTHROW(other->playLeague());
    CHECK_EQ(other->getCurrRoundNum(), 2*(other->getTeams().size()-1));
    CHECK_NOTHROW(stat = new BBallLeague::statistics(other));
    CHECK_THROWS(other->playNextRound());
    CHECK_THROWS_MESSAGE(other->playNextRound(),"league ended, cant play more rounds");
    CHECK_NOTHROW(stat->longestStreak('W'));
    CHECK_NOTHROW(stat->longestStreak('L'));
    CHECK_THROWS(stat->longestStreak('D'));
    CHECK_NOTHROW(stat->showTable());
    CHECK_NOTHROW(stat->top(10,"scored"));
    CHECK_NOTHROW(stat->top(10,"received"));

}

TEST_CASE("good league, some teams mine some other, playing all the league through rounds, showing mid season stats")
{
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
    BBallLeague::league* someSome;
    CHECK_NOTHROW(someSome = new BBallLeague::league(teams));
    BBallLeague::statistics* stat;
    CHECK_THROWS(stat = new BBallLeague::statistics(someSome));
    CHECK_THROWS_MESSAGE(stat = new BBallLeague::statistics(someSome),"league didnt finish yet");
    for(int i = 0; i < 2*(someSome->getTeams().size()-1);i++)
    {
        CHECK_NOTHROW(someSome->playNextRound());
        if(i == 9 || i == 19 || i == 29)
        {
            for(auto* team:someSome->getTeams())
            {
                team->showRecord();
            }
            std::cout << std::endl;
        }
    }
    CHECK_EQ(someSome->getCurrRoundNum(), 2*(someSome->getTeams().size()-1));
    CHECK_NOTHROW(stat = new BBallLeague::statistics(someSome));
    CHECK_THROWS(someSome->playNextRound());
    CHECK_THROWS_MESSAGE(someSome->playNextRound(),"league ended, cant play more rounds");
    CHECK_NOTHROW(stat->showTable());
    CHECK_NOTHROW(stat->homeAwayDiff());
    CHECK_NOTHROW(stat->top(10,"home"));
    CHECK_NOTHROW(stat->top(10,"away"));
}
TEST_CASE("good league, show schedule")
{
    auto * team1 = new BBallLeague::team("golden state warriors",0.95);
    std::vector<BBallLeague::team*> teams;
    teams.push_back(team1);
    BBallLeague::league* other;
    CHECK_NOTHROW(other = new BBallLeague::league(teams));

    std::cerr << "no matches played" << std::endl;
    CHECK_NOTHROW(team1->showSchedule());

    std::cerr << "one match played" << std::endl;
    CHECK_NOTHROW(other->playNextRound());
    CHECK_NOTHROW(team1->showSchedule());

    std::cerr << "all matches played" << std::endl;
    CHECK_NOTHROW(other->playLeague());
    CHECK_NOTHROW(team1->showSchedule());


}