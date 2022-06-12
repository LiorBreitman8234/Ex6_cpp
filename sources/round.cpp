#include "round.hpp"
namespace BBallLeague{

    bool round::addGame(game* game) {
        this->games.push_back(game);
        game->getHome()->addGame(game);
        game->getAway()->addGame(game);
        //std::cout << "added game between: " << game->getHome()->getName() << " and " << game->getAway()->getName() << std::endl;
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