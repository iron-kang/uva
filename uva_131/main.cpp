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

static std::map<char, int> poker_value = {
    {'A', 1},
    {'2', 2},
    {'3', 3},
    {'4', 4},
    {'5', 5},
    {'6', 6},
    {'7', 7},
    {'8', 8},
    {'9', 9},
    {'T', 10},
    {'J', 11},
    {'Q', 12},
    {'K', 13},
};

enum HandDeck
{
    HAND,
    DECK
};

class Poker
{
public:
    Poker(const std::string &card_str)
    {
        value_ = card_str[0];
        suit_ = card_str[1];
    }

    int get_value() const
    {
        return poker_value[value_];
    }

    char get_suit() const
    {
        return suit_;
    }

    std::string show()
    {
        std::stringstream out;
        out << value_ << suit_;
        return out.str();
    }

    static bool cmp_suit(const Poker &p1, const Poker &p2)
    {
        return p1.get_suit() < p2.get_suit();
    }

    static bool cmp_value(const Poker &p1, const Poker &p2)
    {
        return p1.get_value() < p2.get_value();
    }

    bool operator==(const Poker &card) const
    {
        return (get_value() == card.get_value()) && (get_suit() == card.get_suit());
    }

private:
    char value_;
    char suit_;
};

class Holdem
{

public:
    Holdem(){};

    void save_cards(const std::string &card_str, HandDeck type);
    std::string find_the_best_hand();

private:
    std::vector<Poker> decks, hands;

    bool is_flush(bool check_straight);
    bool is_four_of_a_kind();
    bool is_full_house();
    bool is_straight();
    bool is_three_of_a_kind();
    bool is_two_pairs();
    bool is_one_pairs();
};

void Holdem::save_cards(const std::string &card_str, HandDeck type)
{
    switch (type)
    {
    case HAND:
        hands.push_back(card_str);
        break;
    case DECK:
        decks.push_back(card_str);
        break;
    }
}

bool Holdem::is_flush(bool check_straight)
{
    std::map<char, int> candidate_suit;
    std::vector<Poker> tmp_hand = hands;
    std::vector<Poker> candidate_suits[5];
    std::sort(tmp_hand.begin(), tmp_hand.end(), Poker::cmp_suit);
    char cur_suit = '\0';
    int i = 0;

    cur_suit = tmp_hand[0].get_suit();
    for (auto &card : tmp_hand)
    {
        char tmp_suit = card.get_suit();

        if (cur_suit != tmp_suit)
        {
            cur_suit = tmp_suit;
            i++;
        }
        candidate_suits[i].push_back(card);
    }

    /* only one suit */
    if (candidate_suits[0].size() == 5)
        return true;

    for (i = 0; i < 5; i++)
    {
        int need_cards = 5 - candidate_suits[i].size();
        if (need_cards == 5)
            break;
        char suit = candidate_suits[i][0].get_suit();
        int j = 0;
        for (; j < need_cards; j++)
        {
            if (decks[j].get_suit() != suit)
                break;
            else
                candidate_suits[i].push_back(decks[j]);
        }
        if (j == need_cards)
        {
            if (check_straight)
            {
                int straight_cnt = 0;
                int pre_value = 0;
                std::sort(candidate_suits[i].begin(), candidate_suits[i].end(), Poker::cmp_value);
                for (auto &card : candidate_suits[i])
                {
                    int cur_value = card.get_value();
                    if ((cur_value - 1) != pre_value)
                        straight_cnt = 1;
                    else
                        straight_cnt++;
                    pre_value = cur_value;
                }

                if ((straight_cnt == 4) &&
                    (candidate_suits[i][0].get_value() == 1) &&
                    (candidate_suits[i][4].get_value() == 13))
                    straight_cnt++;

                if (straight_cnt == 5)
                    return true;
            }
            else
                return true;
        }
    }

    /* four_of_a_kind in deck*/
    cur_suit = decks[0].get_suit();
    for (size_t i = 1; i < decks.size(); i++)
    {
        if (cur_suit != decks[i].get_suit())
            return false;
    }

    return true;
}

bool Holdem::is_four_of_a_kind()
{
    std::map<int, int> candidate_value;

    for (auto &card : hands)
    {
        int tmp_value = card.get_value();
        candidate_value[tmp_value]++;
    }

    for (auto &values : candidate_value)
    {
        int exchange_cards = 5 - values.second;
        int need_cards = 4 - values.second;
        int value = values.first;
        int i;

        if (need_cards == 0)
            return true;

        for (i = 0; i < exchange_cards; i++)
        {
            if (decks[i].get_value() == value)
                need_cards--;
        }
        if (0 == need_cards)
            return true;
    }

    /* four_of_a_kind in deck*/
    candidate_value.clear();
    for (auto &card : decks)
    {
        int tmp_value = card.get_value();
        candidate_value[tmp_value]++;

        if (candidate_value[tmp_value] == 4)
            return true;
    }

    return false;
}

bool Holdem::is_full_house()
{
    std::map<int, int> candidate_value, candidate_value_tmp;

    /* count card's value */
    for (auto &card : hands)
    {
        int tmp_value = card.get_value();
        candidate_value[tmp_value]++;
    }

    for (auto it_1 = candidate_value.begin(); it_1 != candidate_value.end(); ++it_1)
    {
        candidate_value_tmp = candidate_value;
        for (auto it_2 = it_1; it_2 != candidate_value.end(); ++it_2)
        {
            if (it_2 == it_1)
                continue;
            int need_cards = 5 - it_1->second - it_2->second;

            int value_1 = it_1->first;
            int value_2 = it_2->first;

            for (int i = 0; i < need_cards; i++)
            {
                int deck_value = decks[i].get_value();
                if ((deck_value == value_1) || (deck_value == value_2))
                    candidate_value_tmp[deck_value]++;
            }

            if (((candidate_value_tmp[value_1] == 2) && (candidate_value_tmp[value_2] == 3)) ||
                ((candidate_value_tmp[value_1] == 3) && (candidate_value_tmp[value_2] == 2)))
                return true;
        }
    }

    /* full_house in deck*/
    candidate_value.clear();
    for (auto &card : decks)
    {
        int tmp_value = card.get_value();
        candidate_value[tmp_value]++;
    }

    if (candidate_value.size() == 2)
    {
        for (auto it = candidate_value.begin(); it != candidate_value.end(); ++it)
            if ((it->second == 2) || (it->second == 3))
                return true;
    }

    return false;
}

bool Holdem::is_straight()
{
    std::vector<Poker> tmp_hand = hands;
    std::vector<int> candidate_values[5];
    std::sort(tmp_hand.begin(), tmp_hand.end(), Poker::cmp_value);
    int prev_value = 0;
    int i = 0;

    for (auto &hand : tmp_hand)
    {
        int cur_value = hand.get_value();
        if (prev_value == 0)
        {
            prev_value = cur_value;
            candidate_values[i].push_back(cur_value);
            continue;
        }

        if (cur_value == (prev_value + 1))
        {
            candidate_values[i].push_back(cur_value);
        }
        else if (cur_value != prev_value)
        {
            i++;
            candidate_values[i].push_back(cur_value);
        }
        prev_value = cur_value;
    }

    if (candidate_values[0].size() == 5)
        return true;
    else if ((candidate_values[0][0] == 1) && (candidate_values[1][3] == 13))
    {
        /* handle A 10 11 12 13 case */
        return true;
    }

    for (int i = 0; i < 5; i++)
    {
        if (candidate_values[i].size() == 0)
            break;

        int need_cards = 5 - candidate_values[i].size();
        int j = 0;
        prev_value = candidate_values[i].back();

        std::vector<int> wanted_cards;
        for (j = 0; j < need_cards; j++)
        {
            int next_value = prev_value + j + 1;
            if (next_value > 13)
            {
                if (j == (need_cards - 1))
                    next_value = 1;
                else
                    break;
            }
            wanted_cards.push_back(prev_value + j + 1);
        }

        if (j != need_cards)
            continue;

        for (j = 0; j < need_cards; j++)
        {
            for (auto it = wanted_cards.begin(); it != wanted_cards.end(); ++it)
            {
                if (decks[j].get_value() == *it)
                {
                    wanted_cards.erase(it);
                    break;
                }
            }
        }

        if (wanted_cards.empty())
            return true;
    }

    return false;
}

bool Holdem::is_three_of_a_kind()
{
    std::map<int, int> candidate_value, candidate_value_tmp;

    for (auto &card : hands)
    {
        int tmp_value = card.get_value();
        candidate_value[tmp_value]++;
    }

    for (auto &values : candidate_value)
    {
        int exchange_cards = 5 - values.second;
        int need_cards = 3 - values.second;
        int value = values.first;
        int i;

        if (need_cards == 0)
            return true;

        for (i = 0; i < exchange_cards; i++)
        {
            if (decks[i].get_value() == value)
                need_cards--;
        }
        if (0 == need_cards)
            return true;
    }

    /* four_of_a_kind in deck*/
    candidate_value.clear();
    for (auto &card : decks)
    {
        int tmp_value = card.get_value();
        candidate_value[tmp_value]++;

        if (candidate_value[tmp_value] == 4)
            return true;
    }

    return false;
}

bool Holdem::is_two_pairs()
{
    std::map<int, int> candidate_value, candidate_value_tmp;

    for (auto &card : hands)
    {
        int tmp_value = card.get_value();
        candidate_value[tmp_value]++;
    }

    for (auto it_1 = candidate_value.begin(); it_1 != candidate_value.end(); ++it_1)
    {
        candidate_value_tmp = candidate_value;
        for (auto it_2 = it_1; it_2 != candidate_value.end(); ++it_2)
        {
            if (it_2 == it_1)
                continue;
            int need_cards = 5 - it_1->second - it_2->second;

            int value_1 = it_1->first;
            int value_2 = it_2->first;

            for (int i = 0; i < need_cards; i++)
            {
                int deck_value = decks[i].get_value();
                if ((deck_value == value_1) || (deck_value == value_2))
                    candidate_value_tmp[deck_value]++;
            }

            if ((candidate_value_tmp[value_1] == 2) && (candidate_value_tmp[value_2] == 2))
                return true;
        }
    }

    /* full_house in deck*/
    candidate_value.clear();
    for (auto &card : decks)
    {
        int tmp_value = card.get_value();
        candidate_value[tmp_value]++;
    }

    for (auto it = candidate_value.begin(); it != candidate_value.end();)
    {
        if (it->second < 2)
        {
            it = candidate_value.erase(it);
        }
        else
            ++it;
    }

    if (candidate_value.size() == 2)
        return true;

    return false;
}

bool Holdem::is_one_pairs()
{
    std::map<int, int> candidate_value;

    for (auto &hand : hands)
    {
        int tmp_value = hand.get_value();
        candidate_value[tmp_value]++;

        if (candidate_value[tmp_value] == 2)
            return true;
    }

    for (auto &hand : hands)
    {
        int exchange_cards = 4;

        for (int i = 0; i < exchange_cards; i++)
        {
            if (hand.get_value() == decks[i].get_value())
                return true;
        }
    }

    /* full_house in deck*/
    candidate_value.clear();
    for (auto &deck : hands)
    {
        int tmp_value = deck.get_value();
        candidate_value[tmp_value]++;

        if (candidate_value[tmp_value] == 2)
            return true;
    }

    return false;
}

std::string Holdem::find_the_best_hand()
{
    if (is_flush(true))
        return "straight-flush";
    else if (is_four_of_a_kind())
        return "four-of-a-kind";
    else if (is_full_house())
        return "full-house";
    else if (is_flush(false))
        return "flush";
    else if (is_straight())
        return "straight";
    else if (is_three_of_a_kind())
        return "three-of-a-kind";
    else if (is_two_pairs())
        return "two-pairs";
    else if (is_one_pairs())
        return "one-pair";
    else
        return "highest-card";
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

        Holdem holdem;
        std::stringstream ss(line);
        int i = 0;
        std::string hand_str;
        std::string deck_str;
        while (std::getline(ss, tok, ' '))
        {
            if (i++ > 4)
            {
                deck_str += tok + " ";
                holdem.save_cards(tok, HandDeck::DECK);
            }
            else
            {
                hand_str += tok + " ";
                holdem.save_cards(tok, HandDeck::HAND);
            }
        }

        std::string ret;
        ret = "Hand: " + hand_str + "Deck: " + deck_str + "Best hand: ";
        ret += holdem.find_the_best_hand();

        std::cout << ret << std::endl;
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
