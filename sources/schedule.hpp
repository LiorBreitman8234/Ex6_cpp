#ifndef EX6_CPP_SCHEDULE_HPP
#define EX6_CPP_SCHEDULE_HPP
#include <vector>
#include "round.hpp"
#include <map>
namespace BBallLeague{
    class round;
    class schedule{
        //this class hold all the round in the league
        std::vector<round*> rounds;
    public:
        explicit schedule(const std::vector<team*>& teams);
        round* getRound(int num){return this->rounds.at((size_t)(num-1));};
        bool checkValid(int teamsNum);
    };

}
#endif