#include "game.hpp"
namespace BBallLeague{
    game::game(team *home, team *away) {
        this->away = away;
        this->home = home;
        this->winner = "";
        this->score = std::pair<int,int>(0,0);
    }

    team *game::getHome() {
        return this->home;
    }

    team *game::getAway() {
        return this->away;
    }

    std::string game::getWinner() {
        return this->winner;
    }

    std::pair<int, int> game::getScore() {
        return this->score;
    }

    std::ostream &operator<<(std::ostream &os, const game &game) {
        std::string toPrint = "Home: " + game.home->getName() + "\n";
        toPrint += "Away: " + game.away->getName() + "\n";
        toPrint += "Score: " + std::to_string(game.score.first) + " - " + std::to_string(game.score.second) + "\n";
        toPrint += "Winner: " + game.winner + "\n";
        os << toPrint;
        return os;
    }
}