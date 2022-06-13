#ifndef EX6_CPP_ROUND_HPP
#define EX6_CPP_ROUND_HPP
#include <vector>
#include "game.hpp"
namespace BBallLeague{
    class round{
        // this class holds a round of games in the league
        std::vector<game*> games;
        int numRound{};
    public:
        round() = default;
        void setNum(int num){this->numRound = num;};
        bool addGame(game* game);
        int getNum() const{return this->numRound;};
        std::vector<game*> getGames(){return this->games;};
        friend std::ostream &operator<<(std::ostream &os, const round &round);
    };
}

#endif