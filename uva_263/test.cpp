#include <gmock/gmock.h>
#include <string>
#include <iostream>
#include "NumberChains.h"

TEST(NumberChains, 123456789)
{
    std::string expect = std::string("Original number was 123456789\n") +
                         "987654321 - 123456789 = 864197532\n" +
                         "987654321 - 123456789 = 864197532\n" +
                         "Chain length 2\n";
    std::string out;
    NumberChains(123456789, out);

    EXPECT_EQ(expect, out);
}

TEST(NumberChains, 1234)
{
    std::string expect = std::string("Original number was 1234\n") +
                         "4321 - 1234 = 3087\n" +
                         "8730 - 378 = 8352\n" +
                         "8532 - 2358 = 6174\n" +
                         "7641 - 1467 = 6174\n" + "Chain length 4\n";
    std::string out;
    NumberChains(1234, out);

    EXPECT_EQ(expect, out);
}

TEST(NumberChains, 444)
{
    std::string expect = std::string("Original number was 444\n") +
                         "444 - 444 = 0\n" +
                         "0 - 0 = 0\n" + "Chain length 2\n";
    std::string out;
    NumberChains(444, out);

    EXPECT_EQ(expect, out);
}

TEST(NumberChains, 57878377)
{
    std::string expect = std::string("Original number was 57878377\n") +
                         "88777753 - 35777788 = 52999965\n" +
                         "99996552 - 25569999 = 74426553\n" +
                         "76554432 - 23445567 = 53108865\n" +
                         "88655310 - 1355688 = 87299622\n" +
                         "99876222 - 22267899 = 77608323\n" +
                         "87763320 - 2336778 = 85426542\n" +
                         "86554422 - 22445568 = 64108854\n" +
                         "88654410 - 1445688 = 87208722\n" +
                         "88772220 - 2227788 = 86544432\n" +
                         "86544432 - 23444568 = 63099864\n" +
                         "99866430 - 3466899 = 96399531\n" +
                         "99965331 - 13356999 = 86608332\n" +
                         "88663320 - 2336688 = 86326632\n" +
                         "86663322 - 22336668 = 64326654\n" +
                         "66654432 - 23445666 = 43208766\n" +
                         "87664320 - 2346678 = 85317642\n" +
                         "87654321 - 12345678 = 75308643\n" +
                         "87654330 - 3345678 = 84308652\n" +
                         "88654320 - 2345688 = 86308632\n" +
                         "88663320 - 2336688 = 86326632\n" +
                         "Chain length 20\n";
    std::string out;
    NumberChains(57878377, out);

    EXPECT_EQ(expect, out);
}