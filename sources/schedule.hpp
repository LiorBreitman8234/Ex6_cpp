#ifndef EX6_CPP_SCHEDULE_HPP
#define EX6_CPP_SCHEDULE_HPP
#include <vector>
#include "round.hpp"
namespace BBallLeague{
    class round;
    class schedule{
        std::vector<round*> rounds;
    public:
        schedule(const std::vector<team*>& teams);
        round* getRound(int num){return this->rounds.at((size_t)(num-1));};
    };

}
#endif