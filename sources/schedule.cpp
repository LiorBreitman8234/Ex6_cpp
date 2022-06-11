
#include "schedule.hpp"

namespace BBallLeague {
    schedule::schedule(const std::vector<team *>& teams) {
        std::random_device rd;
        std::mt19937 gen{rd()};
        std::uniform_int_distribution<> distribution(0, (int) teams.size() - 1);
        std::vector<std::vector<int>> checkMatrix;
        checkMatrix.reserve(teams.size());
        for(auto team:teams){
            checkMatrix.emplace_back(teams.size(),0);
        }
        for (int i = 0; i < 2 * (teams.size() - 1); i++) {
            this->rounds.push_back(new round());
        }
        for(auto round:this->rounds)
        {

        }
//        for(int i =0; i<checkMatrix.size();i++)
//        {
//            std::cout << "[";
//            for(int j = 0; j < checkMatrix.at(i).size();j++)
//            {
//                std::cout << checkMatrix.at(i).at(j)<< " ";
//            }
//            std::cout << "]\n";
//        }



    }
}