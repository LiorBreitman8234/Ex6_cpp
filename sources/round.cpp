#include "round.hpp"
namespace BBallLeague{

    bool round::addGame(game* game) {
        //adding game to the round
        this->games.push_back(game);
        game->getHome()->addGame(game);
        game->getAway()->addGame(game);
        return true;
    }

    std::ostream &operator<<(std::ostream &os, const round &round) {
        os << "Round Number: " << round.numRound << std::endl;
        for(auto* game:round.games)
        {
            os << (*game) << std::endl;
        }
        return os;
    }
}