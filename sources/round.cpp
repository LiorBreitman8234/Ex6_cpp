#include "round.hpp"
namespace BBallLeague{

    bool round::addGame(game* game) {
        bool check = game->getHome()->checkGameExists(*game);
        if(check)
        {
            return false;
        }
        this->games.push_back(game);
        std::cout << "added game between: " << game->getHome()->getName() << " and " << game->getAway()->getName() << std::endl;
        return true;
    }

    std::ostream &operator<<(std::ostream &os, const round &round) {
        for(auto game:round.games)
        {
            os << (*game) << std::endl;
        }
        return os;
    }
}