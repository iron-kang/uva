#include <iostream>
#include <vector>
#include <math.h>
#include <algorithm>
#include <time.h>
#include <map>
#include <deque>
#include <string>
#define ONLINE_JUDGE
#ifndef ONLINE_JUDGE
#include <gmock/gmock.h>
#endif
// #include "NumberChains.h"

using namespace std;

/*
 * sort numbers and store ascend/descend
 * @param ascend
 *        descend
 */
void sort(deque<uint8_t> &nums, string &ascend, string &descend)
{
    deque<uint8_t> nums_new;
    int id = 0;

    int i = 0;
    int len = 0;

    for (auto num : nums)
    {
        deque<uint8_t>::iterator it = nums_new.begin();
        i = 0;
        id = 0;

        for (; it != nums_new.end(); ++it)
        {
            i++;
            if (num > *it)
                id = i;
        }
        nums_new.insert(nums_new.begin() + id, num);
        ascend.insert(id, to_string(num));
        len = ascend.length();
        /*descend_id = len(descend) - 1 - ascend_id*/
        descend.insert(len - id - 1, to_string(num));
    }
}

/*
 * sort numbers and store ascend/descend
 * @param num: input number
 *        out: uva_263 result
 */
void NumberChains(int num, string &out)
{
    deque<uint8_t> nums;
    int ascend_num = 0;
    int descend_num = 0;
    int diff = 0;
    string ascend, descend;
    static int chain_len = 0;
    static map<int, bool> diffs;
    static string str_out = "";

    if (chain_len == 0)
    {
        str_out = "Original number was " + to_string(num) + "\n";
    }

    while (num > 0)
    {
        nums.push_back(num % 10);
        num = num / 10;
    }

    sort(nums, ascend, descend);
    descend_num = descend == "" ? 0 : stoi(descend);
    ascend_num = ascend == "" ? 0 : stoi(ascend);
    diff = descend_num - ascend_num;

    str_out = str_out + to_string(descend_num) + " - " +
              to_string(ascend_num) + " = " + to_string(diff) + "\n";
    chain_len++;

    if (diffs.find(diff)->second)
    {
        str_out = str_out + "Chain length " + to_string(chain_len) + "\n";
        out = str_out;

        str_out = "";
        chain_len = 0;
        diffs.clear();
        return;
    }
    else
    {
        diffs.insert({diff, true});
        NumberChains(diff, out);
    }
}

int main(int argc, char **argv)
{
#ifdef ONLINE_JUDGE
    int num = 0;
    string out;

    while (cin >> num)
    {
        if (num == 0)
            break;

        NumberChains(num, out);
        printf("%s\n", out.c_str());
    }
    return 0;
#else
    testing::InitGoogleMock(&argc, argv);
    return RUN_ALL_TESTS();
#endif
}