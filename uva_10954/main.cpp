#include <iostream>
#include <fstream>
#include <sstream>
#include <deque>
#include <queue>
#include <algorithm>
//#define ONLINE_JUDGE
#ifndef ONLINE_JUDGE
#include <gmock/gmock.h>
#endif

int add_cost(std::string &input)
{
    std::deque<int> nums;
    std::deque<int>::iterator it;
    std::string tok;
    uint32_t costs = 0;

    std::stringstream ss(input);

    while (std::getline(ss, tok, ' '))
    {
        nums.push_back(stoi(tok));
    }
    std::sort(nums.begin(), nums.end());

    while (nums.size() != 1)
    {
        int cost = 0;
        cost += nums.front();
        nums.pop_front();
        cost += nums.front();
        nums.pop_front();

        for (it = nums.begin(); it != nums.end(); ++it)
        {
            if (cost <= *it)
            {
                nums.insert(it, cost);
                break;
            }
        }
        if (it == nums.end())
            nums.push_back(cost);

        costs += cost;
    }

    std::cout << costs << std::endl;
    return costs;
}

bool add_all(std::istream &in)
{
    std::string line;

    std::getline(in, line);
    if (line == "" || stoi(line) == 0)
        return false;

    std::getline(in, line);

    add_cost(line);

    return true;
}

int main(int argc, char **argv)
{
#ifdef ONLINE_JUDGE
    while (true)
    {
        if (!add_all(std::cin))
            break;
    }
#else
    testing::InitGoogleMock(&argc, argv);
    return RUN_ALL_TESTS();
#endif
    return 0;
}
