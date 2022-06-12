
#include "league.hpp"

namespace BBallLeague{
    BBallLeague::league::league(const std::vector<team *>& teams) {
        if(teams.size() > numTeams)
        {
            throw std::invalid_argument("too many teams");
        }
        for(auto* first:teams)
        {
            for(auto* second:teams)
            {
                if(first->getName() == second->getName())
                {
                    throw std::invalid_argument("2 teams with the same name");
                }
            }
        }
        std::random_device rd{};
        std::mt19937 gen{rd()};
        this->mt19937 = gen;
        this->currentRoundNum = 0;
        int counter = 1;
        for(auto* team: teams)
        {
            table.push_back(team);
        }
        if(this->table.size() < numTeams){
            addTeams();
        }
        for(auto* team: this->table)
        {
            team->setId(counter++);
        }
        this->leagueGames = new schedule(this->table);
        this->currentRound = nullptr;
    }

    league::league() {
        std::random_device rd{};
        std::mt19937 gen{rd()};
        this->mt19937 = gen;
        this->currentRoundNum = 0;
        addTeams();
        int counter = 1;
        for(auto* team: this->table)
        {
            team->setId(counter++);
        }
        this->leagueGames = new schedule(this->table);
        this->currentRound = nullptr;
    }

    void league::addTeams() {
        std::fstream file;
        file.open("/home/bravo8234/CLionProjects/Ex6_cpp/teams.txt",std::ios::in);
        if(!file.is_open())
        {
            std::cerr << "cant open file! "<< std::endl;
            exit(1);
        }
        std::vector<std::string> names;
        while(this->table.size() + names.size() < numTeams)
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
        if(this->currentRoundNum >= (this->table.size() -1 ) *2)
        {
            throw std::invalid_argument("league ended, cant play more rounds");
        }
        round* curr = this->leagueGames->getRound(++this->currentRoundNum);
        this->currentRound = curr;
        for(auto* currGame:curr->getGames())
        {
            currGame->PlayGame(this->mt19937);
        }
        std::cout << (*curr) << std::endl;
    }

    void league::printLastRound() {
        printRound(this->currentRoundNum);
    }

    void league::playLeague() {
        for(int i = currentRoundNum; i < 2*(numTeams-1);i++)
        {
            playNextRound();
        }
    }

    void league::printRound(int roundNum) {
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
