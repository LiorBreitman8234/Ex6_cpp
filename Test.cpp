//
// Created by bravo8234 on 12/06/2022.
//
#include "doctest.h"
#include "sources/league.hpp"
#include "sources/statistics.hpp"
TEST_CASE("good league, all my teams")
{
    BBallLeague::league* good;
    CHECK_NOTHROW(good = new BBallLeague::league());
    BBallLeague::statistics* stat;
    CHECK_THROWS(stat = new BBallLeague::statistics(good));
    CHECK_THROWS_MESSAGE(stat = new BBallLeague::statistics(good),"league didnt finish yet");
    CHECK_NOTHROW(good->playLeague());
    CHECK_EQ(good->getCurrRoundNum(), 2*(good->getTeams().size()-1));
    CHECK_NOTHROW(stat = new BBallLeague::statistics(good));
    CHECK_THROWS(good->playNextRound());
    CHECK_THROWS_MESSAGE(good->playNextRound(),"league ended, cant play more rounds");
    CHECK_THROWS(stat->top(25,"record"));
    CHECK_THROWS_MESSAGE(stat->top(25,"record"),"num bigger then amount of teams");
    CHECK_THROWS(stat->top(15,"difference"));
    CHECK_THROWS_MESSAGE(stat->top(15,"difference"),"no such statistic");
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