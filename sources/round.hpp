#ifndef EX6_CPP_ROUND_HPP
#define EX6_CPP_ROUND_HPP
#include <vector>
#include "game.hpp"
namespace BBallLeague{
    class round{
        std::vector<game*> games;
    public:
        round():games(std::vector<game*>()){};
        bool addGame(game* game);
        std::vector<game*> getGames(){return this->games;};
    };
}

#endif