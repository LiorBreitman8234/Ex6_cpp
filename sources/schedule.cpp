
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
        std::vector<game *> allGames;// to check game validity
        for (int i = 0; i < 2 * (teams.size() - 1); i++) {
            this->rounds.push_back(new round());
        }
        //adding all the possible games
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
        //setting games to round and adding round num
        for(auto* curr:rounds)
        {
            curr->setNum(counter++);
            std::vector<int> chosen(teams.size(),0);//to check which teams played in this round
            while(!checkChosen(chosen))
            {
                int firstID = getFirst(chosen);//first that didn't play in this round
                team* team = teams.at(0);
                for(auto* check:teams)
                {
                    if(check->getId() == firstID)
                    {
                        team = check;
                        break;
                    }
                }
                std::vector<game*> games = team->getGames();//getting all the games of the team
                for(int i = 0; i < games.size() ;i++)
                {
                    game* game = team->getGames().at((size_t)i);
                    if(game->getHome()->getId() == firstID)
                    {
                        //curr team is home
                        auto secondID = (size_t)(game->getAway()->getId()-1);
                        if(chosen.at(secondID) == 0)//checking if the second team is also free in the round
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
                        // curr team is away
                        auto secondID = (size_t)(game->getHome()->getId()-1);
                        if(chosen.at(secondID) == 0)//checking if the second team is also free in the round
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
            team->clearGame();//clearing the removed games
        }
        for(auto* curr:rounds)
        {
            for(auto* game:curr->getGames())
            {
                //adding the games by the round order
                game->getAway()->addGame(game);
                game->getHome()->addGame(game);
            }
        }
        if(checkValid((int)teams.size())){
            std::cout << "schedule is valid!" << std::endl;
        }
        else
        {
            throw std::logic_error("invalid schedule");
        }
    }

    bool schedule::checkValid(int teamsNum) {
        // this function check if the schedule is valid i.e each team plays once in each round
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