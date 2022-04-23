#include <iostream>
#include <fstream>
#include <sstream>
#include <memory>
#include <deque>
#include <vector>
#include <algorithm>
#define ONLINE_JUDGE
#ifndef ONLINE_JUDGE
#include <gmock/gmock.h>
#endif

void solve_uva(std::istream &in)
{
    std::string line;
    std::string tok;
    std::deque<int> train_tmp, trains_out, trains_in_sta;

    while (true)
    {
        std::getline(in, line);
        if (line == "")
            break;

        int N = stoi(line);
        int i = 0;

        while (N != 0)
        {
            std::getline(in, line);
            if ((line.length() == 1) && stoi(line) == 0)
            {
                std::cout << std::endl;
                break;
            }
            std::stringstream ss(line);
            trains_out.clear();
            trains_in_sta.clear();
            train_tmp.clear();
            while (std::getline(ss, tok, ' '))
            {
                trains_out.push_back(stoi(tok));
            }

            i = 1;
            while (trains_out.size() > 0)
            {

                if (trains_in_sta.size() && (trains_in_sta.back() == trains_out.front()))
                {
                    train_tmp.push_back(trains_in_sta.back());
                    trains_in_sta.pop_back();
                    trains_out.pop_front();
                }
                else
                {
                    if (i <= N)
                        trains_in_sta.push_back(i++);
                    else
                        break;
                }
            }

            if (trains_in_sta.size() > 0)
                std::cout << "No" << std::endl;
            else
                std::cout << "Yes" << std::endl;
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
