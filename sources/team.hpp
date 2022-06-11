#ifndef EX6_CPP_TEAM_HPP
#define EX6_CPP_TEAM_HPP
#include <iostream>
#include <ctime>
#include <utility>
#include <random>
#include "game.hpp"
#include <string>
namespace BBallLeague{
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
        void setId(int getID){this->id = getID;};
        bool checkGameExists(game& game);
        int getId() const{return this->id;};
        std::string getName(){return this->name;};
        void addGame(game* game){this->schedule.push_back(game);};
    };
}
#endif