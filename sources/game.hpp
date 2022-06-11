

#ifndef EX6_CPP_GAME_HPP
#define EX6_CPP_GAME_HPP
#include "team.hpp"
namespace BBallLeague{
    class team;
    class game{
        team* home;
        team* away;
        std::string winner;
        std::pair<int,int> score;
    public:
        game(team* home, team* away);
        team* getHome();
        team* getAway();
        std::string getWinner();
        std::pair<int,int> getScore();
        friend std::ostream &operator<<(std::ostream &os, const game &game);
    };
}
#endif