#include "game.hpp"
namespace BBallLeague{
    game::game(team *home, team *away) {
        this->away = away;
        this->home = home;
        this->winner = "";
        this->status = "not played yet";
        this->score = std::pair<int,int>(0,0);
    }

    team *game::getHome() {
        return this->home;
    }

    team *game::getAway() {
        return this->away;
    }

    std::string game::getWinner() {
        return this->winner;
    }

    std::pair<int, int> game::getScore() {
        return this->score;
    }

    std::ostream &operator<<(std::ostream &os, const game &game) {
        std::string toPrint = "Home: " + game.home->getName() + "\n";
        toPrint += "Away: " + game.away->getName() + "\n";
        toPrint += "Score: " + std::to_string(game.score.first) + " - " + std::to_string(game.score.second) + "\n";
        toPrint += "Winner: " + game.winner + "\n";
        toPrint += "Status: " + game.status + "\n";
        os << toPrint;
        return os;
    }

    void game::PlayGame() {
        std::random_device rd;
        std::mt19937 gen{rd()};
        std::normal_distribution<> homeP{mean,std};
        std::normal_distribution<> awayP{mean,std};
        int homeS = (int)std::round(homeP(gen));
        int awayS = (int)std::round(awayP(gen));
        while(homeS < minHome or homeS > maxScore)
        {
            homeS = (int)std::round(homeP(gen));
        }
        while(awayS < minAway or awayS > maxScore){
            awayS = (int)std::round(awayP(gen));
        }
        homeS += (int)(this->home->getTalent() * meanOver);
        awayS += (int)(this->away->getTalent() * meanOver);
        int overTimeCounter = 0;
        while(awayS == homeS)
        {
            overTimeCounter++;
            std::normal_distribution<> overTime{meanOver,stdOver};
            homeS += (int)(overTime(gen));
            awayS += (int)(overTime(gen));
        }
        if(overTimeCounter == 0)
        {
            this->status = "finished in regular time";
        }
        else
        {
            this->status = "finished in over time";
        }
        this->score = std::pair<int,int>(homeS,awayS);
        if(homeS > awayS)
        {
            this->winner = home->getName();
            this->home->updateRecord('W');
            this->home->updateStreak('W');
            this->away->updateRecord('L');
            this->away->updateStreak('L');
            return;
        }
        this->winner = away->getName();
        this->home->updateRecord('L');
        this->home->updateStreak('L');
        this->away->updateRecord('W');
        this->away->updateStreak('W');

    }
}