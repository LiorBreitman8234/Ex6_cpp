
#include "schedule.hpp"

namespace BBallLeague {
    schedule::schedule(const std::vector<team *>& teams) {
        std::vector<game*> allGames;
        for (int i = 0; i < 2 * (teams.size() - 1); i++) {
            this->rounds.push_back(new round());
        }
        for(auto first:teams){
            for(auto second:teams)
            {
                if(first->getId() == second->getId())
                {
                    continue;
                }
                bool exists = false;
                for(auto game:allGames)
                {
                    if(game->getAway()->getName() == second->getName() and game->getHome()->getName() == first->getName())
                    {
                        exists = true;
                        break;
                    }
                }
                if(!exists)
                {
                    game* newGame = new game(first,second);
                    allGames.push_back(newGame);
                }
            }
        }
        for(auto curr:rounds)
        {
            std::vector<int> chosen(teams.size(),0);
            bool flag = false;
            while(curr->getGames().size() < teams.size()/2)
            {
                for(int i = 0; i < chosen.size();i++)
                {
//                    if(!flag)
//                    {
//                        flag = true;
//                        std::cout << "[";
//                        for(int index:chosen)
//                        {
//                            std::cout << index <<", ";
//                        }
//                        std::cout << "]" << std::endl;
//                    }
                    if(chosen.at((size_t)i) == 0)
                    {
                        int idFirst = i+1;
                        for(int j = 0; j < allGames.size();j++)
                        {
                            game* game = allGames.at((size_t)j);
                            if(game->getHome()->getId() == idFirst)
                            {
                                if(chosen.at((size_t)game->getAway()->getId()-1) == 0)
                                {
                                    chosen.at((size_t)(idFirst-1)) = 1;
                                    chosen.at((size_t)(game->getAway()->getId()-1)) = 1;
                                    curr->addGame(game);
                                    allGames.erase(allGames.begin()+j);
                                    std::cout << "games left to set: " << allGames.size() << std::endl;
                                    flag = false;
                                    break;
                                }
                            }
                            if(game->getAway()->getId() == idFirst)
                            {
                                if(chosen.at((size_t)game->getHome()->getId()-1) == 0)
                                {
                                    chosen.at((size_t)(idFirst-1)) = 1;
                                    chosen.at((size_t)(game->getHome()->getId()-1)) = 1;
                                    curr->addGame(game);
                                    allGames.erase(allGames.begin()+j);
                                    std::cout << "games left to set: " << allGames.size() << std::endl;
                                    flag = false;
                                    break;
                                }
                            }
                        }
                    }
                }
            }
            std::cout << (*curr) << std::endl;
        }
        for(auto curr:rounds){
            for(auto game:curr->getGames())
            {
                game->getHome()->addGame(game);
                game->getAway()->addGame(game);
            }
        }
    }
}