
#include "team.hpp"

namespace BBallLeague{
    team::team(std::string name) {
        this->id = 0;
        std::random_device rd{};
        std::mt19937 gen{rd()};
        std::normal_distribution<> distribution{0.5,0.1};
        this->name = std::move(name);
        this->talent = distribution(gen);
        while(talent <= 0 or talent >= 1){
            this->talent = distribution(gen);
        }
        this->currentStreak = std::pair<int,char>(0,'w');
        this->record = std::pair<int,int>(0,0);
        this->schedule = std::vector<game*>();
    }

    bool team::checkGameExists(game &game) {
        for(auto toCheck:this->schedule){
            if(game.getAway()->getName() == toCheck->getAway()->getName())
            {
                return true;
            }
            if(game.getHome()->getName() == toCheck->getHome()->getName()){
                return true;
            }
        }
        return false;
    }

}