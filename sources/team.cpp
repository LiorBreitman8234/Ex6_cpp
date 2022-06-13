
#include "team.hpp"

namespace BBallLeague{
    team::team(std::string name) {
        this->id = 0;
        std::random_device rd{};
        std::mt19937 gen{rd()};
        std::normal_distribution<> distribution{TALENTMEAN,TALENTSTD};
        this->name = std::move(name);
        this->talent = distribution(gen);
        while(talent <= 0 or talent > 1){
            this->talent = distribution(gen);
        }
        this->currentStreak = std::pair<int,char>(0,'W');
        this->record = std::pair<int,int>(0,0);
        this->schedule = std::vector<game*>();
    }

    bool team::checkGameExists(game &game) {
        for(auto* toCheck:this->schedule){
            if(game.getAway()->getName() == toCheck->getAway()->getName() and game.getHome()->getName() == toCheck->getHome()->getName())
            {
                return true;
            }
        }
        return false;
    }

    void team::updateStreak(char sign) {
        if(this->currentStreak.second == sign)
        {
            this->currentStreak.first++;
        }
        else{
            this->currentStreak.first = 1;
            this->currentStreak.second = sign;
        }
    }
    void team::updateRecord(char sign) {
        if(sign == 'W')
        {
            this->record.first++;
        }
        else{
            this->record.second++;
        }
    }

    void team::eraseGame(game *toRemove) {
        std::vector<game*>::iterator iter;
        for(iter = this->schedule.begin();iter != this->schedule.end();)
        {
            if(toRemove->getAway()->getId() == (*iter)->getAway()->getId() and toRemove->getHome()->getId() == (*iter)->getHome()->getId())
            {
                this->schedule.erase(iter);
                return;
            }
            ++iter;
        }
    }

    std::ostream &operator<<(std::ostream &os, const team &team) {
        std::string toPrint = team.name + " ";
        toPrint += std::to_string(team.record.first) + "-" + std::to_string(team.record.second) + " ";
        toPrint+= "streak: " + std::to_string(team.currentStreak.first) + team.currentStreak.second;
        os << toPrint;
        return os;
    }

    team::team(std::string name, double talent) {
        if(talent <= 0 or talent > 1)
        {
            throw std::invalid_argument("talent not in range");
        }
        this->id = 0;
        this->name = std::move(name);
        this->talent = talent;
        this->currentStreak = std::pair<int,char>(0,'W');
        this->record = std::pair<int,int>(0,0);
        this->schedule = std::vector<game*>();
    }

    void team::showSchedule() {
        std::cout << "schedule for: " << this->name << std::endl;
        for(auto* game: this->schedule)
        {
            std::cout << (*game) << std::endl;
        }
        std::cout << "current record: " << this->record.first << "W - " << this->record.second << "L" << std::endl;
    }

    void team::showRecord() {
        std::cout << this->name <<" record: " << this->record.first << "W - " << this->record.second << "L" << std::endl;
    }

}