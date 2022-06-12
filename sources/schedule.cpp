
#include "schedule.hpp"

namespace BBallLeague {
    bool checkChosen(const std::vector<int>& chosen)
    {
        for(auto i : chosen){
            if(i == 0)
            {
                return false;
            }
        }
        return true;
    }
    int getFirst(const std::vector<int>& chosen)
    {
        for(int i = 0; i < chosen.size();i++)
        {
            if(chosen.at((size_t)i) == 0)
            {
                return i+1;
            }
        }
        return -1;
    }
    schedule::schedule(const std::vector<team *> &teams) {
        std::vector<game *> allGames;
        for (int i = 0; i < 2 * (teams.size() - 1); i++) {
            this->rounds.push_back(new round());
        }
        for (auto *first: teams) {
            for (auto *second: teams) {
                if (first->getId() == second->getId()) {
                    continue;
                }
                bool exists = false;
                for (auto *game: allGames) {
                    if (game->getAway()->getName() == second->getName() and
                        game->getHome()->getName() == first->getName()) {
                        exists = true;
                        break;
                    }
                }
                if (!exists) {
                    game * newGame = new game(first, second);
                    first->addGame(newGame);
                    second->addGame(newGame);
                }
            }
        }
        int counter = 1;
        for(auto* curr:rounds)
        {
            curr->setNum(counter++);
            std::vector<int> chosen(teams.size(),0);
            while(!checkChosen(chosen))
            {
                int firstID = getFirst(chosen);
                team* team = teams.at(0);
                for(auto* check:teams)
                {
                    if(check->getId() == firstID)
                    {
                        team = check;
                        break;
                    }
                }
                std::vector<game*> games =team->getGames();
                for(int i = 0; i < games.size() ;i++)
                {
                    game* game = team->getGames().at((size_t)i);
                    if(game->getHome()->getId() == firstID)
                    {
                        auto secondID = (size_t)(game->getAway()->getId()-1);
                        if(chosen.at(secondID) == 0)
                        {
                            curr->addGame(game);
                            chosen.at(secondID) = 1;
                            chosen.at((size_t)firstID-1) = 1;
                            team->eraseGame(game);
                            game->getAway()->eraseGame(game);
                            break;
                        }
                    }
                    else
                    {
                        auto secondID = (size_t)(game->getHome()->getId()-1);
                        if(chosen.at(secondID) == 0)
                        {
                            curr->addGame(game);
                            chosen.at(secondID) = 1;
                            chosen.at((size_t)firstID-1) = 1;
                            team->eraseGame(game);
                            game->getHome()->eraseGame(game);
                            break;
                        }
                    }
                }
            }
        }
        for(auto* team:teams)
        {
            team->clearGame();
        }
        for(auto* curr:rounds)
        {
            for(auto* game:curr->getGames())
            {
                game->getAway()->addGame(game);
                game->getHome()->addGame(game);
            }
        }
        if(checkValid((int)teams.size())){
            std::cout << "schedule is valid!" << std::endl;
        }
    }

    bool schedule::checkValid(int teamsNum) {
        for(auto* curr:rounds)
        {
            std::vector<int> check((size_t)teamsNum,0);
            for(auto* game: curr->getGames())
            {
                if(check.at((size_t)(game->getHome()->getId()-1)) == 0 and check.at((size_t)(game->getAway()->getId()-1)) == 0)
                {
                    check.at((size_t)(game->getHome()->getId()-1)) = 1;
                    check.at((size_t)(game->getAway()->getId()-1)) = 1;
                }
                else
                {
                    return false;
                }
            }
        }
        return true;
    }
}