//
// Created by bravo8234 on 12/06/2022.
//
#include "statistics.hpp"
namespace BBallLeague{
    std::vector<team*> statistics::sortRecord() {
        std::vector<team *> sorted = this->leagueUse->getTeams();
        for(size_t i = 0; i < sorted.size();i++)
        {
            for(size_t j = i+1; j < sorted.size();j++)
            {
                if(sorted.at(j)->getScore().first > sorted.at(i)->getScore().first)
                {
                    team* temp = sorted.at(i);
                    sorted.at(i) = sorted.at(j);
                    sorted.at(j) = temp;
                }
            }
        }
        return sorted;
    }

    void statistics::top(int num, const std::string& statistic) {
        if(num > this->leagueUse->getTeams().size())
        {
            throw std::invalid_argument("num bigger then amount of teams");
        }
        if(statistic == "record")
        {
            std::vector<team*> sorted =this->sortRecord();
            for(size_t i =0; i < num;i++)
            {
                std::cout << sorted.at(i)->getName() << " record: " << sorted.at(i)->getScore().first <<"W - " << sorted.at(i)->getScore().second <<"L "<<std::endl;
            }
        }
        if(statistic == "diff")
        {
            std::vector<std::pair<team*,int>> sorted = this->sortDiff();
            for(size_t i = 0; i < num;i++)
            {
                std::cout << sorted.at(i).first->getName() << " diff (points scored - points received) :" << sorted.at(i).second << std::endl;
            }
        }
        else if(statistic == "scored")
        {
            std::vector<std::pair<team*,int>> sorted = this->sortScored();
            for(size_t i = 0; i < num;i++)
            {
                std::cout << sorted.at(i).first->getName() << " points scored :" << sorted.at(i).second << std::endl;
            }
        }
        else if(statistic == "received")
        {
            std::vector<std::pair<team*,int>> sorted = this->sortReceived();
            for(size_t i = 0; i < num;i++)
            {
                std::cout << sorted.at(i).first->getName() << " pointed received :" << sorted.at(i).second << std::endl;
            }
        }
        else if(statistic == "home")
        {
            std::vector<std::pair<team*,int>> sorted = this->sortHomeWins();
            for(size_t i = 0; i < num;i++)
            {
                std::cout << sorted.at(i).first->getName() << " home games won :" << sorted.at(i).second << std::endl;
            }
        }
        else if(statistic == "away"){
            std::vector<std::pair<team*,int>> sorted =this->sortAwayWins();
            for(size_t i = 0; i < num;i++)
            {
                std::cout << sorted.at(i).first->getName() << " away games won:" << sorted.at(i).second << std::endl;
            }
        }
        else
        {
            throw std::invalid_argument("no such statistic");
        }
        std::cout << std::endl;
    }

    void statistics::homeAwayDiff() {
        int countHome = 0;
        int countAway = 0;
        int numRound = 2*(int)(leagueUse->getTeams().size()-1);
        for(int i =0; i < numRound;i++)
        {
            round* curr = leagueUse->getRound(i+1);
            for(auto* game:curr->getGames())
            {
                if(game->getScore().first > game->getScore().second)
                {
                    countHome++;
                }
                else
                {
                    countAway++;
                }
            }
        }
        int sumGames = countHome + countAway;
        std::cout <<"home games won: " << countHome << " home game W%: " << ((double)countHome)/sumGames << std::endl;
        std::cout <<"away games won: " << countAway << " away game W%: " << ((double)countAway)/sumGames << std::endl;
        std::cout << std::endl;
    }

    std::vector<std::pair<team*,int>>  statistics::sortDiff() {
        std::vector<std::pair<int,int>> sumPoints;
        std::vector<team*> teams = this->leagueUse->getTeams();
        sumPoints.reserve(teams.size());
        for(int i = 0; i < teams.size();i++)
        {
            sumPoints.emplace_back(0,0);
        }
        int numRound = 2*(int)(leagueUse->getTeams().size()-1);
        for(int i =0; i <numRound;i++)
        {
            round* round =this->leagueUse->getRound(i+1);
            for(auto* game:round->getGames())
            {
                sumPoints.at((size_t)(game->getHome()->getId()-1)).first += game->getScore().first;
                sumPoints.at((size_t)(game->getHome()->getId()-1)).second += game->getScore().second;
                sumPoints.at((size_t)(game->getAway()->getId()-1)).first += game->getScore().second;
                sumPoints.at((size_t)(game->getAway()->getId()-1)).second += game->getScore().first;
            }
        }
        std::vector<std::pair<team*,int>> diffList;
        for(size_t i =0; i < sumPoints.size();i++)
        {
            team* currTeam = teams.at(i);
            int diff = sumPoints.at(i).first - sumPoints.at(i).second;
            diffList.emplace_back(currTeam,diff);
        }
        for(size_t i = 0; i < diffList.size();i++)
        {
            for(size_t j = i+1; j < diffList.size();j++)
            {
                if(diffList.at(j).second > diffList.at(i).second)
                {
                    std::pair<team*,int> temp = diffList.at(i);
                    diffList.at(i) = diffList.at(j);
                    diffList.at(j) = temp;
                }
            }
        }
        return diffList;
    }

    void statistics::showTable() {
        std::vector<team*> sortedRecord = this->sortRecord();
        std::vector<std::pair<team*,int>> sortedDiff = this->sortDiff();
        std::vector<team*> beforeLastSort = sortedRecord;
        for(size_t i = 0; i < beforeLastSort.size(); i++)
        {
            for(size_t j = i+1; j < beforeLastSort.size(); j++)
            {
                std::pair<int,int> firstRecord = beforeLastSort.at(i)->getScore();
                std::pair<int,int> secondRecord = beforeLastSort.at(j)->getScore();
                if(firstRecord.first == secondRecord.first && firstRecord.second == secondRecord.second){
                    int firstID = beforeLastSort.at(i)->getId();
                    int secondID = beforeLastSort.at(j)->getId();
                    int firstDiff = 0;
                    int secondDiff = 0;
                    for(auto pair:sortedDiff)
                    {
                        if(pair.first->getId() == firstID)
                        {
                            firstDiff = pair.second;
                        }
                        else if(pair.first->getId() == secondID)
                        {
                            secondDiff = pair.second;
                        }
                    }
                    if(firstDiff < secondDiff)
                    {
                        team* temp = beforeLastSort.at(i);
                        beforeLastSort.at(i) = beforeLastSort.at(j);
                        beforeLastSort.at(j) = temp;
                    }
                }
            }
        }
        std::vector<std::pair<team*,int>> lastSort;
        for(auto* team:beforeLastSort)
        {
            int id = team->getId();
            for(auto pair:sortedDiff)
            {
                if(pair.first->getId() == id)
                {
                    lastSort.emplace_back(pair);
                }
            }
        }
        for(auto & i : lastSort)
        {
            std::cout << i.first->getName() <<" record: " << i.first->getScore().first << "-" <<i.first->getScore().second<< " points diff:" << i.second << std::endl;
        }
        std::cout << std::endl;
    }

    void statistics::longestStreak(char type) {
        int longest = 0;
        for(auto* team:this->leagueUse->getTeams())
        {
            int currentStreak = 0;
            std::vector<game*> games= team->getGames();
            for(size_t i =0; i< games.size();i++)
            {
                if(type == 'W'){
                    if(games.at(i)->getWinner() == team->getName())
                    {
                        currentStreak++;
                    }
                    else
                    {
                        if(longest < currentStreak)
                        {
                            longest = currentStreak;
                        }
                        currentStreak = 0;
                    }
                }
                else
                {
                    if(games.at(i)->getWinner() != team->getName())
                    {
                        currentStreak++;
                    }
                    else
                    {
                        if(longest < currentStreak)
                        {
                            longest = currentStreak;
                        }
                        currentStreak = 0;
                    }
                }
            }
        }
        if(type == 'W')
        {
            std::cout<< "longest winning streak was: " << longest << std::endl;
        }
        if(type == 'L')
        {
            std::cout<< "longest losing streak was: " << longest << std::endl;

        }
    }

    void statistics::scoredMore() {
        int count = 0;
        std::vector<std::pair<team*,int>> sorted = sortDiff();
        for(auto pair:sorted)
        {
            if(pair.second > 0)
            {
                count++;
            }
            else
            {
                break;
            }
        }
        std::cout << count << " teams scored more then they received" << std::endl;
    }

    statistics::statistics(league *league1) {
        if(league1->getCurrRoundNum() < 2*(league1->getTeams().size()-1))
        {
            throw std::invalid_argument("league didnt finish yet");
        }
        this->leagueUse = league1;

    }

    std::vector<std::pair<team *, int>> statistics::sortScored() {
        std::vector<team*> teams = this->leagueUse->getTeams();
        std::vector<std::pair<team*,int>> sort;
        for(auto* currTeam:teams)
        {
            int scored = 0;
            for(auto* game:currTeam->getGames())
            {
                if(game->getAway()->getName() == currTeam->getName())
                {
                    scored += game->getScore().second;
                }
                else
                {
                    scored += game->getScore().first;
                }
            }
            sort.emplace_back(std::pair<team*,int>(currTeam,scored));
        }
        for(size_t i =0; i < sort.size();i++)
        {
            for(size_t j = i+1; j < sort.size();j++)
            {
                if(sort.at(i).second < sort.at(j).second)
                {
                    std::pair<team*,int> temp = sort.at(i);
                    sort.at(i) = sort.at(j);
                    sort.at(j) = temp;
                }
            }
        }
        return sort;

    }

    std::vector<std::pair<team *, int>> statistics::sortReceived() {
        std::vector<team*> teams = this->leagueUse->getTeams();
        std::vector<std::pair<team*,int>> sort;
        for(auto* currTeam:teams)
        {
            int recv = 0;
            for(auto* game:currTeam->getGames())
            {
                if(game->getAway()->getName() == currTeam->getName())
                {
                    recv += game->getScore().first;
                }
                else
                {
                    recv += game->getScore().second;
                }
            }
            sort.emplace_back(std::pair<team*,int>(currTeam,recv));
        }
        for(size_t i =0; i < sort.size();i++) {
            for (size_t j = i + 1; j < sort.size(); j++) {
                if (sort.at(i).second < sort.at(j).second) {
                    std::pair<team *, int> temp = sort.at(i);
                    sort.at(i) = sort.at(j);
                    sort.at(j) = temp;
                }
            }
        }
        return sort;
    }

    std::vector<std::pair<team *, int>> statistics::sortHomeWins() {
        std::vector<team*> teams = this->leagueUse->getTeams();
        std::vector<std::pair<team*,int>> sort;
        for(auto* currTeam:teams)
        {
            int count = 0;
            for(auto* game: currTeam->getGames())
            {
                if(game->getHome()->getId() == currTeam->getId() && game->getWinner() == currTeam->getName())
                {
                    count++;
                }
            }
            sort.emplace_back(std::pair<team*,int>(currTeam,count));
        }
        for(size_t i =0; i < sort.size();i++)
        {
            for(size_t j = i+1; j < sort.size();j++)
            {
                if(sort.at(i).second < sort.at(j).second)
                {
                    std::pair<team *, int> temp = sort.at(i);
                    sort.at(i) = sort.at(j);
                    sort.at(j) = temp;
                }
            }
        }
        return sort;
    }

    std::vector<std::pair<team *, int>> statistics::sortAwayWins() {
        std::vector<team*> teams = this->leagueUse->getTeams();
        std::vector<std::pair<team*,int>> sort;
        for(auto* currTeam:teams)
        {
            int count = 0;
            for(auto* game: currTeam->getGames())
            {
                if(game->getAway()->getId() == currTeam->getId() && game->getWinner() == currTeam->getName())
                {
                    count++;
                }
            }
            sort.emplace_back(std::pair<team*,int>(currTeam,count));
        }
        for(size_t i =0; i < sort.size();i++)
        {
            for(size_t j = i+1; j < sort.size();j++)
            {
                if(sort.at(i).second < sort.at(j).second)
                {
                    std::pair<team *, int> temp = sort.at(i);
                    sort.at(i) = sort.at(j);
                    sort.at(j) = temp;
                }
            }
        }
        return sort;
    }
}