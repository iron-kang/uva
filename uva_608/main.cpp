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

typedef struct
{
    char id;
    int weight;
} Coin;

// void handle_left(std::map<char, std::string> &coins,
//                  const std::string &left_coins,
//                  const std::string &balance)
// {
//     std::string weight = "";

//     weight = balance == "up" ? "heavy" : "light";

//     for (auto &coin : left_coins)
//     {
//         if (coins[coin] == 0)
//             coins[coin] = 1;
//         else if (coins[coin] != 1)
//             coins.erase(coin);

//         // std::cout << "coin[" << coin << "]" << coins[coin] << std::endl;
//     }
// }

void solve_uva(std::istream &in)
{
    std::string line;
    std::string tok;
    std::vector<char> coin;
    std::vector<std::string> left_coins, right_coins, balances;

    while (true)
    {
        std::getline(in, line);
        if (line == "")
            return;

        int cnt = stoi(line);
        while (cnt-- > 0)
        {
            int i = 0;
            std::set<char> real_coins;
            std::vector<char> left_coins, right_coins;

            std::string left, right;
            while (i++ < 3)
            {
                std::getline(in, line);
                std::istringstream ss(line);
                std::string left_coin_str, right_coin_str, balance, tmp;

                ss >> left_coin_str >> right_coin_str >> balance;

                // std::cout << "left: " << left_coin_str << ", right: "
                //           << right_coin_str << ", balance: " << balance << std::endl;

                if (balance == "down")
                {
                    tmp = left_coin_str;
                    left_coin_str = right_coin_str;
                    right_coin_str = tmp;
                }
                else if (balance == "even")
                {
                    for (int j = 0; j < left_coin_str.size(); j++)
                    {
                        real_coins.insert(left_coin_str[j]);
                        real_coins.insert(right_coin_str[j]);
                    }
                    continue;
                }

                if (left_coins.size() == 0 && right_coins.size() == 0)
                {
                    for (int j = 0; j < left_coin_str.size(); j++)
                    {
                        left_coins.push_back(left_coin_str[j]);
                        right_coins.push_back(right_coin_str[j]);
                    }
                    std::sort(left_coins.begin(), left_coins.end());
                    std::sort(right_coins.begin(), right_coins.end());
                }
                else
                {
                    std::vector<char> tmp_left, tmp_right, tmp;
                    for (int j = 0; j < left_coin_str.size(); j++)
                    {
                        tmp_left.push_back(left_coin_str[j]);
                        tmp_right.push_back(right_coin_str[j]);
                    }
                    std::sort(tmp_left.begin(), tmp_left.end());
                    std::sort(tmp_right.begin(), tmp_right.end());
                    std::set_intersection(left_coins.begin(), left_coins.end(),
                                          tmp_left.begin(), tmp_left.end(),
                                          std::back_inserter(tmp));
                    left_coins = tmp;
                    tmp.clear();
                    std::set_intersection(right_coins.begin(), right_coins.end(),
                                          tmp_right.begin(), tmp_right.end(),
                                          std::back_inserter(tmp));
                    right_coins = tmp;
                }

                // balances.push_back(balance);
            }

            if (real_coins.size() != 0)
            {
                for (auto it = left_coins.begin(); it != left_coins.end();)
                {
                    if (real_coins.find(*it) != real_coins.end())
                    {
                        it = left_coins.erase(it);
                    }
                    else
                        ++it;
                }

                for (auto it = right_coins.begin(); it != right_coins.end();)
                {
                    if (real_coins.find(*it) != real_coins.end())
                    {
                        it = right_coins.erase(it);
                    }
                    else
                        ++it;
                }
            }
            char fake_coin;
            std::string fake_coin_weight;
            if (left_coins.size() == 1)
            {
                fake_coin = left_coins[0];
                fake_coin_weight = "heavy";
            }
            else if (right_coins.size() == 1)
            {
                fake_coin = right_coins[0];
                fake_coin_weight = "light";
            }

            std::cout << fake_coin << " is the counterfeit coin and it is " << fake_coin_weight << "." << std::endl;

            // for (auto &a : fake_cons_possible)
            // {
            //     std::cout << a << " ";
            // }
            // std::cout << std::endl;
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
