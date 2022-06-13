

#ifndef EX6_CPP_GAME_HPP
#define EX6_CPP_GAME_HPP
#include "team.hpp"
namespace BBallLeague{
    constexpr int mean = 80;
    constexpr int std = 7;
    constexpr int meanOver = 10;
    constexpr int stdOver = 3;
    constexpr int maxScore = 100;
    constexpr int minHome = 55;
    constexpr int minAway = 50;
    class team;
    class game{
        // this class holds a single game between 2 teams;
        std::string status;
        team* home;
        team* away;
        std::string winner;
        std::pair<int,int> score;
    public:
        game(team* home, team* away);
        void PlayGame();//plays the game
        team* getHome();
        team* getAway();
        std::string getWinner();
        std::pair<int,int> getScore();
        friend std::ostream &operator<<(std::ostream &os, const game &game);
    };
}
#endif