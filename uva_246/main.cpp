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
#include <iterator>
#define ONLINE_JUDGE
#ifndef ONLINE_JUDGE
#include <gmock/gmock.h>
#endif

class PokerGame
{
public:
    enum class RESULT
    {
        WIN = 0,
        LOSS,
        DRAW
    };
    PokerGame(const int &pile_num) : pile_num_(pile_num)
    {
        round_ = 0;
        for (int i = 0; i < pile_num_; i++)
        {
            piles.push_back(std::deque<int>());
        }
    }

    int get_rounds() { return round_; }
    void get_cards(const int &card);
    RESULT check_result();

private:
    unsigned int pile_num_;
    int round_;
    std::deque<int> deck;
    std::vector<std::deque<int>> piles;
    std::set<int> remove_pile;

    std::set<std::string> records;

    bool check_win();
    bool check_draw();
    bool check_sum_cond(const int &sum);
    void check_combinations(const int &i);
};

bool PokerGame::check_sum_cond(const int &sum)
{
    if ((sum == 10) || (sum == 20) || (sum == 30))
        return true;
    return false;
}

void PokerGame::get_cards(const int &card)
{
    deck.push_back(card);
}

void PokerGame::check_combinations(const int &i)
{

    int remove_cards[3];

    int pile_size;
    pile_size = piles[i].size();
    if (pile_size < 3)
        return;

    while ((pile_size = piles[i].size()) >= 3)
    {
        int sum = piles[i][0] + piles[i][1] + piles[i][pile_size - 1];
        if (check_sum_cond(sum))
        {
            remove_cards[0] = piles[i].front();
            piles[i].pop_front();
            remove_cards[1] = piles[i].front();
            piles[i].pop_front();
            remove_cards[2] = piles[i].back();
            piles[i].pop_back();

            for (int j = 0; j < 3; j++)
                deck.push_back(remove_cards[j]);
            continue;
        }

        sum = piles[i][0] + piles[i][pile_size - 2] + piles[i][pile_size - 1];
        if (check_sum_cond(sum))
        {
            remove_cards[0] = piles[i].front();
            piles[i].pop_front();
            remove_cards[2] = piles[i].back();
            piles[i].pop_back();
            remove_cards[1] = piles[i].back();
            piles[i].pop_back();

            for (int j = 0; j < 3; j++)
                deck.push_back(remove_cards[j]);
            continue;
        }

        sum = piles[i][pile_size - 3] + piles[i][pile_size - 2] + piles[i][pile_size - 1];
        if (check_sum_cond(sum))
        {
            remove_cards[2] = piles[i].back();
            piles[i].pop_back();
            remove_cards[1] = piles[i].back();
            piles[i].pop_back();
            remove_cards[0] = piles[i].back();
            piles[i].pop_back();

            for (int j = 0; j < 3; j++)
                deck.push_back(remove_cards[j]);
            continue;
        }

        break;
    }

    if (piles[i].size() == 0)
        remove_pile.insert(i);
}

PokerGame::RESULT PokerGame::check_result()
{
    int i = 0;
    round_ = 0;

    while (deck.size())
    {
        if (remove_pile.find(i % 7) != remove_pile.end())
        {
            i++;
            continue;
        }
        int card = deck.front();
        deck.pop_front();

        piles[i % 7].push_back(card);

        check_combinations(i % 7);
        round_++;
        i++;

        if (remove_pile.size() == pile_num_)
            return RESULT::WIN;

        std::stringstream record;
        std::copy(deck.begin(), deck.end(), std::ostream_iterator<int>(record, " "));
        for (auto &pile : piles)
        {
            std::stringstream tmp;
            std::copy(pile.begin(), pile.end(), std::ostream_iterator<int>(tmp, " "));
            record << tmp.str();
        }
        if (records.find(record.str()) != records.end())
            return RESULT::DRAW;
        records.insert(record.str());
    }

    return RESULT::LOSS;
}

void solve_uva(std::istream &in)
{
    std::string line;

    while (true)
    {
        int point, i = 0;
        PokerGame pg(7);
        while (i++ < 52)
        {
            in >> point;
            if (point == 0)
                return;
            pg.get_cards(point);
        }

        switch (pg.check_result())
        {
        case PokerGame::RESULT::WIN:
            std::cout << "Win : " << pg.get_rounds() << std::endl;
            break;
        case PokerGame::RESULT::DRAW:
            std::cout << "Draw: " << pg.get_rounds() << std::endl;
            break;
        case PokerGame::RESULT::LOSS:
            std::cout << "Loss: " << pg.get_rounds() << std::endl;
            break;
        default:
            std::cout << "unknown" << std::endl;
            break;
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
