
#include "league.hpp"

namespace BBallLeague{

    BBallLeague::league::league(const std::vector<team *>& teams) {
        this->currentRoundNum = 0;
        int counter = 1;
        for(auto team: teams)
        {
            table.push_back(team);
        }
        if(this->table.size() < 20){
            addTeams();
        }
        for(auto team: this->table)
        {
            team->setId(counter++);
        }
        this->leagueGames = new schedule(this->table);
        this->currentRound = nullptr;
    }

    league::league() {
        this->currentRoundNum = 0;
        addTeams();
        int counter = 1;
        for(auto team: this->table)
        {
            team->setId(counter++);
        }
        this->leagueGames = new schedule(this->table);
        this->currentRound = nullptr;
    }

    void league::addTeams() {
        std::fstream file;
        file.open("../teams.txt",std::ios::in);
        if(!file.is_open())
        {
            std::cerr << "cant open file! "<< std::endl;
            exit(1);
        }
        std::vector<std::string> names;
        while(this->table.size() + names.size() < 8)
        {
            std::string name;
            std::getline(file,name);
            names.push_back(name);
        }
        file.close();
        for(const std::string& name: names)
        {
            this->table.push_back(new team(name));
        }
    }
}
