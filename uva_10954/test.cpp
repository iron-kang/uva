#include "main.cpp"

TEST(add_cost, test1)
{

    std::string expect = std::string("9\n");
    std::string input("1 2 3");

    testing::internal::CaptureStdout();
    add_cost(input);
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_EQ(expect, output);
}

TEST(add_cost, test2)
{

    std::string expect = std::string("19\n");
    std::string input("1 2 3 4");

    testing::internal::CaptureStdout();
    add_cost(input);
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_EQ(expect, output);
}

TEST(add_all, test3)
{
    std::ifstream input_file("test3.txt");
    std::string expect{
        R"(3349
147
1454
5488
5479
992
120
2353
430
127
3185
1418
391
3774
5045
5984
4125
4118
626
2893
324
842
1138
2256
12
3470
1163
4379
1745
5413
782
1068
1584
2796
2113
2983
283
4560
5122
120
3536
1459
4748
1572
884
603
4361
918
3229
2709
)"};

    testing::internal::CaptureStdout();
    while (true)
    {
        if (!add_all(input_file))
            break;
    }
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_EQ(expect, output);
}

TEST(add_all, test4)
{
    std::ifstream input_file("test4.txt");
    std::string expect{
        R"(3034495442
6180738192
)"};
    testing::internal::CaptureStdout();
    while (true)
    {
        if (!add_all(input_file))
            break;
    }
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_EQ(expect, output);
}
