#include <iostream>
#include <fstream>
#include <sstream>
#include <memory>
#include <deque>
#include <vector>
#include <stack>
#include <algorithm>
#define ONLINE_JUDGE
#ifndef ONLINE_JUDGE
#include <gmock/gmock.h>
#endif

bool trains_dispatch(std::deque<int> &trains_order, const int &trainsNum)
{
    std::stack<int> trains_in_sta;
    int i = 1;

    while (trains_order.size() > 0)
    {
        if (trains_in_sta.size() && (trains_in_sta.top() == trains_order.front()))
        {
            trains_in_sta.pop();
            trains_order.pop_front();
        }
        else
        {
            if (i <= trainsNum)
                trains_in_sta.push(i++);
            else
                break;
        }
    }

    if (trains_in_sta.size() > 0)
    {
        std::cout << "No" << std::endl;
        return false;
    }
    else
        std::cout << "Yes" << std::endl;

    return true;
}

bool get_trains_order(std::istream &in, std::deque<int> &trains_order)
{
    std::string tok;
    std::string line;

    trains_order.clear();
    std::getline(in, line);
    if ((line.length() == 1) && stoi(line) == 0)
    {
        std::cout << std::endl;
        return false;
    }

    std::stringstream ss(line);
    trains_order.clear();
    while (std::getline(ss, tok, ' '))
    {
        trains_order.push_back(stoi(tok));
    }

    return true;
}

void solve_uva(std::istream &in)
{
    std::string line;

    std::deque<int> trains_order;

    while (true)
    {
        std::getline(in, line);
        if (line == "")
            break;

        int N = stoi(line);

        while (N != 0)
        {
            if (!get_trains_order(in, trains_order))
                break;
            trains_dispatch(trains_order, N);
        }
    }
}

int main(int argc, char **argv)
{
#ifdef ONLINE_JUDGE
    solve_uva(std::cin);
#else
    testing::InitGoogleMock(&argc, argv);
    return RUN_ALL_TESTS();
#endif
    return 0;
}
