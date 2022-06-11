#include <iostream>
#include <iostream>
#include "league.hpp"
#include "round.hpp"
#include "team.hpp"
#include "game.hpp"
#include "schedule.hpp"
int main() {
    auto* test = new BBallLeague::league();
    auto* round = test->getRound(1);
    std::cout << "test";
    return 0;
}
