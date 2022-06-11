//
// Created by bravo8234 on 10/06/2022.
//

#ifndef EX6_CPP_LEAGUE_HPP
#define EX6_CPP_LEAGUE_HPP
#include <vector>
#include "round.hpp"
#include "team.hpp"
#include <fstream>
#include "schedule.hpp"
namespace BBallLeague{
    class league{
        int currentRoundNum{};
        round* currentRound;
        schedule* leagueGames;
        std::vector<team*> table;
        void addTeams();
    public:
        explicit league(const std::vector<team*>& teams);
        league();
        void playNextRound();
        int getCurrRoundNum(){return this->currentRoundNum;};
        round* getRound(int round){return leagueGames->getRound(round);};
        round* getCurrRound(){return leagueGames->getRound(this->currentRoundNum);};
    };

}
#endif //EX6_CPP_LEAGUE_HPP
