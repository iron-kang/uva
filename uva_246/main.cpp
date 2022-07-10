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
        deck.clear();
        piles.clear();
        remove_pile.clear();
        records.clear();

        for (int i = 0; i < pile_num_; i++)
        {
            piles.push_back(std::deque<int>());
        }
    }

    int get_rounds() { return round_; }
    void get_cards(const int &card);
    RESULT result();

private:
    unsigned int pile_num_;
    int round_;
    std::deque<int> deck;
    std::vector<std::deque<int>> piles;
    std::set<int> remove_pile;
    std::set<std::deque<int>> records;

    void check_combinations(const int &id);
};

void PokerGame::get_cards(const int &card)
{
    deck.push_back(card);
}

void PokerGame::check_combinations(const int &id)
{

    int remove_cards[3];
    int pile_size;

    pile_size = piles[id].size();
    if (pile_size < 3)
        return;

    while ((pile_size = piles[id].size()) >= 3)
    {
        int sum = piles[id][0] + piles[id][1] + piles[id][pile_size - 1];
        if ((sum % 10) == 0)
        {
            remove_cards[0] = piles[id].front();
            piles[id].pop_front();
            remove_cards[1] = piles[id].front();
            piles[id].pop_front();
            remove_cards[2] = piles[id].back();
            piles[id].pop_back();

            for (int j = 0; j < 3; j++)
                deck.push_back(remove_cards[j]);
            continue;
        }

        sum = piles[id][0] + piles[id][pile_size - 2] + piles[id][pile_size - 1];
        if ((sum % 10) == 0)
        {
            remove_cards[0] = piles[id].front();
            piles[id].pop_front();
            remove_cards[2] = piles[id].back();
            piles[id].pop_back();
            remove_cards[1] = piles[id].back();
            piles[id].pop_back();

            for (int j = 0; j < 3; j++)
                deck.push_back(remove_cards[j]);
            continue;
        }

        sum = piles[id][pile_size - 3] + piles[id][pile_size - 2] + piles[id][pile_size - 1];
        if ((sum % 10) == 0)
        {
            remove_cards[2] = piles[id].back();
            piles[id].pop_back();
            remove_cards[1] = piles[id].back();
            piles[id].pop_back();
            remove_cards[0] = piles[id].back();
            piles[id].pop_back();

            for (int j = 0; j < 3; j++)
                deck.push_back(remove_cards[j]);
            continue;
        }

        break;
    }

    if (piles[id].size() == 0)
        remove_pile.insert(id);
}

PokerGame::RESULT PokerGame::result()
{
    int i = 0;
    round_ = 0;

    while (deck.size())
    {
        if (remove_pile.find(i % pile_num_) != remove_pile.end())
        {
            i++;
            continue;
        }
        int card = deck.front();
        deck.pop_front();

        piles[i % pile_num_].push_back(card);

        check_combinations(i % pile_num_);
        round_++;
        i++;

        if (remove_pile.size() == pile_num_)
            return RESULT::WIN;

        std::deque<int> record;
        std::deque<int>::iterator it = record.begin();

        record.insert(it, deck.begin(), deck.end());
        for (auto &pile : piles)
        {
            it = record.end();
            record.insert(it, pile.begin(), pile.end());
        }

        if (records.find(record) != records.end())
            return RESULT::DRAW;
        records.insert(record);
    }

    return RESULT::LOSS;
}

void solve_uva(std::istream &in)
{
    int piles_num = 7;

    while (true)
    {
        int point, i = 0;
        PokerGame pg(piles_num);

        while (i++ < 52)
        {
            in >> point;
            if (point == 0)
                return;
            pg.get_cards(point);
        }

        switch (pg.result())
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
