#include <iostream>
#include <fstream>
#include <sstream>
#include <memory>
#include <deque>
#include <vector>
#include <map>
#include <set>
#include <math.h>
#include <algorithm>
#define ONLINE_JUDGE
#ifndef ONLINE_JUDGE
#include <gmock/gmock.h>
#endif

class CounterfeitDollar
{
public:
    CounterfeitDollar(){};

    void measure_coins(std::string &left_coin, std::string &right_coin, std::string &balance);
    void get_counterfeit_coin(char &coin_id, std::string &weight);
    void remove_real_coins();

private:
    std::set<char> real_coins;
    std::vector<char> left_fake_coins, right_fake_coins;

    void filter_counterfeit_coin(std::string &left_coin,
                                 std::string &right_coin);
};

void CounterfeitDollar::filter_counterfeit_coin(std::string &left_coin,
                                                std::string &right_coin)
{
    if (left_fake_coins.size() == 0 && right_fake_coins.size() == 0)
    {
        for (size_t i = 0; i < left_coin.size(); i++)
        {
            left_fake_coins.push_back(left_coin[i]);
            right_fake_coins.push_back(right_coin[i]);
        }
        std::sort(left_fake_coins.begin(), left_fake_coins.end());
        std::sort(right_fake_coins.begin(), right_fake_coins.end());
    }
    else
    {
        std::vector<char> tmp_left, tmp_right, tmp;
        for (size_t i = 0; i < left_coin.size(); i++)
        {
            tmp_left.push_back(left_coin[i]);
            tmp_right.push_back(right_coin[i]);
        }
        std::sort(tmp_left.begin(), tmp_left.end());
        std::sort(tmp_right.begin(), tmp_right.end());
        std::set_intersection(left_fake_coins.begin(), left_fake_coins.end(),
                              tmp_left.begin(), tmp_left.end(),
                              std::back_inserter(tmp));
        left_fake_coins = tmp;
        tmp.clear();
        std::set_intersection(right_fake_coins.begin(), right_fake_coins.end(),
                              tmp_right.begin(), tmp_right.end(),
                              std::back_inserter(tmp));
        right_fake_coins = tmp;
    }
}

void CounterfeitDollar::remove_real_coins()
{
    if (real_coins.size() != 0)
    {
        for (auto it = left_fake_coins.begin(); it != left_fake_coins.end();)
        {
            if (real_coins.find(*it) != real_coins.end())
            {
                it = left_fake_coins.erase(it);
            }
            else
                ++it;
        }

        for (auto it = right_fake_coins.begin(); it != right_fake_coins.end();)
        {
            if (real_coins.find(*it) != real_coins.end())
            {
                it = right_fake_coins.erase(it);
            }
            else
                ++it;
        }
    }
}

void CounterfeitDollar::measure_coins(std::string &left_coin,
                                      std::string &right_coin,
                                      std::string &balance)
{
    if (balance == "even")
    {
        for (size_t i = 0; i < left_coin.size(); i++)
        {
            real_coins.insert(left_coin[i]);
            real_coins.insert(right_coin[i]);
        }
        return;
    }

    if (balance == "down")
    {
        std::string tmp = left_coin;
        left_coin = right_coin;
        right_coin = tmp;
    }

    filter_counterfeit_coin(left_coin, right_coin);
}

void CounterfeitDollar::get_counterfeit_coin(char &coin_id, std::string &weight)
{
    if (left_fake_coins.size() == 1)
    {
        coin_id = left_fake_coins[0];
        weight = "heavy";
    }
    else if (right_fake_coins.size() == 1)
    {
        coin_id = right_fake_coins[0];
        weight = "light";
    }
}

void solve_uva(std::istream &in)
{
    std::string line;
    std::string tok;

    while (true)
    {
        std::getline(in, line);
        if (line == "")
            return;

        int cnt = stoi(line);

        while (cnt-- > 0)
        {
            int i = 0;
            CounterfeitDollar counterfeit;

            while (i++ < 3)
            {
                std::getline(in, line);
                std::istringstream ss(line);
                std::string left_coin_str, right_coin_str, balance, tmp;

                ss >> left_coin_str >> right_coin_str >> balance;

                counterfeit.measure_coins(left_coin_str, right_coin_str, balance);
            }

            counterfeit.remove_real_coins();
            char fake_coin;
            std::string fake_coin_weight;
            counterfeit.get_counterfeit_coin(fake_coin, fake_coin_weight);

            std::cout << fake_coin << " is the counterfeit coin and it is " << fake_coin_weight << "." << std::endl;
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
