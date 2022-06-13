
#include "league.hpp"

namespace BBallLeague{
    BBallLeague::league::league(const std::vector<team *>& teams) {

        if(teams.size() > numTeams)//checking amount of teams
        {
            throw std::invalid_argument("too many teams");
        }
        for(auto* first:teams)//checking duplicated teams
        {
            for(auto* second:teams)
            {
                if(first == second)
                {
                    continue;
                }
                if(first->getName() == second->getName())
                {
                    throw std::invalid_argument("2 teams with the same name");
                }
            }
        }
        this->currentRoundNum = 0;
        int counter = 1;
        for(auto* team: teams)//adding teams to table
        {
            table.push_back(team);
        }
        if(this->table.size() < numTeams)//adding extra teams if needed
        {
            addTeams();
        }
        for(auto* team: this->table)//setting ids
        {
            team->setId(counter++);
        }
        this->leagueGames = new schedule(this->table);//setting schedule
    }

    league::league() {
        this->currentRoundNum = 0;
        addTeams();//adding teams
        int counter = 1;
        for(auto* team: this->table)//setting ids
        {
            team->setId(counter++);
        }
        this->leagueGames = new schedule(this->table);//setting schedule
    }

    void league::addTeams() {
        // in this function I add enough teams from a file I wrote
        std::fstream file;
        file.open("/home/bravo8234/CLionProjects/Ex6_cpp/teams.txt",std::ios::in);
        if(!file.is_open())
        {
            std::cerr << "cant open file! "<< std::endl;
            exit(1);
        }
        std::vector<std::string> names;
        while(this->table.size() + names.size() < numTeams)//until enough teams
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

    void league::playNextRound() {
        //playing the next round of games
        if(this->currentRoundNum >= (this->table.size() -1 ) *2)
        {
            throw std::invalid_argument("league ended, cant play more rounds");
        }
        round* curr = this->leagueGames->getRound(++this->currentRoundNum);
        for(auto* currGame:curr->getGames())
        {
            currGame->PlayGame();
        }
    }

    void league::printLastRound() {
        printRound(this->currentRoundNum);
    }

    void league::playLeague() {
        //playing all the rounds left;
        for(int i =  currentRoundNum; i < 2*(numTeams-1);i++)
        {
            playNextRound();
        }
    }

    void league::printRound(int roundNum) {
        //printing a selected round
        if(roundNum > 2*(this->table.size()-1) || roundNum <=0 )
        {
            throw std::invalid_argument("round num out of range");
        }
        round* round = this->leagueGames->getRound(roundNum);
        std::cout << (*round) << std::endl;
    }

    std::ostream &operator<<(std::ostream &os, const league &league) {
        for(auto* team:league.table)
        {
            os << (*team) << std::endl;
        }
        return os;
    }
}
