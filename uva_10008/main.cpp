#include <iostream>
#include <fstream>
#include <map>
#include <vector>
#include <ctype.h>
#include <map>
#include <algorithm>
// #define ONLINE_JUDGE
#ifndef ONLINE_JUDGE
#include <gmock/gmock.h>
#endif

using namespace std;

bool cmp(const pair<char, int> &p1, const pair<char, int> &p2)
{
    if (p1.second > p2.second)
        return true;
    else if (p1.second == p2.second)
    {
        return p1.first < p2.first;
    }
    else
        return false;
}

void extract_letters(std::istream &in, int &lines, map<char, int, less<char>> &letters)
{
    string text;
    while (lines-- > 0)
    {
        getline(in, text);

        for (auto &c : text)
        {
            if (isalpha(c))
                letters[toupper(c)]++;
        }
    }
}

void sort_letters(vector<pair<char, int>> &result, map<char, int, less<char>> &letters)
{

    for (auto &c : letters)
        result.push_back(make_pair(c.first, c.second));

    sort(result.begin(), result.end(), cmp);

    for (auto &t : result)
        cout << t.first << " " << t.second << endl;
}

bool cryptanalysis(std::istream &in)
{
    string line;
    map<char, int, less<char>> letters;
    vector<pair<char, int>> result;

    getline(in, line);
    if (line == "")
        return false;

    int lines = stoi(line);

    extract_letters(in, lines, letters);
    sort_letters(result, letters);

    return true;
}

int main(int argc, char **argv)
{
#ifdef ONLINE_JUDGE
    while (true)
    {
        if (!cryptanalysis(cin))
            break;
    }
#else
    testing::InitGoogleMock(&argc, argv);
    return RUN_ALL_TESTS();
#endif
    return 0;
}