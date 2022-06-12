#ifndef EX6_CPP_TEAM_HPP
#define EX6_CPP_TEAM_HPP
#include <iostream>
#include <ctime>
#include <utility>
#include <random>
#include "game.hpp"
#include <string>
namespace BBallLeague{
    constexpr double TALENTMEAN =  0.7;
    constexpr double TALENTSTD = 0.2;
    class game;
    class team{
        int id; //used for scheduling
        std::string name;
        double talent;
        std::pair<int,char> currentStreak;
        std::pair<int,int> record;
        std::vector<game*> schedule;
    public:
        explicit team(std::string name);
        team(std::string name, double talent);
        double getTalent() const{return this->talent;};
        void setId(int getID){this->id = getID;};
        void updateStreak(char sign);
        void updateRecord(char sign);
        void clearGame(){this->schedule.clear();};
        void eraseGame(game* toRemove);
        bool checkGameExists(game& game);
        std::pair<int,int> getScore(){return this->record;};
        std::vector<game*> getGames(){return this->schedule;};
        int getId() const{return this->id;};
        std::string getName(){return this->name;};
        void addGame(game* game){this->schedule.push_back(game);};
        friend std::ostream &operator<<(std::ostream &os, const team &team);

    };
}
#endif