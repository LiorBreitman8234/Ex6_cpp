#ifndef EX6_CPP_STATISTICS_HPP
#define EX6_CPP_STATISTICS_HPP

#include <vector>
#include "team.hpp"
#include "league.hpp"
#include "game.hpp"
namespace BBallLeague{
    class statistics{
        league* leagueUse;
        std::vector<team*> sortRecord();
        std::vector<std::pair<team*,int>>  sortDiff();
        std::vector<std::pair<team*,int>>  sortScored();
        std::vector<std::pair<team*,int>> sortReceived();
        std::vector<std::pair<team*,int>> sortHomeWins();
        std::vector<std::pair<team*,int>> sortAwayWins();

    public:
        explicit statistics(league* league1);
        void top(int num, const std::string& statistic);
        void homeAwayDiff();
        void showTable();
        void scoredMore();
        //void bot(int num, std::string statistic); maybe
        void longestStreak(char type);
    };
}


#endif