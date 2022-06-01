#include "main.cpp"

TEST(Coin, test)
{
    std::ifstream input_file("test.txt");
    std::string expect{
        R"(D is the counterfeit coin and it is light.
J is the counterfeit coin and it is heavy.
A is the counterfeit coin and it is heavy.
E is the counterfeit coin and it is light.
L is the counterfeit coin and it is heavy.
C is the counterfeit coin and it is light.
F is the counterfeit coin and it is light.
F is the counterfeit coin and it is heavy.
L is the counterfeit coin and it is light.
A is the counterfeit coin and it is heavy.
A is the counterfeit coin and it is heavy.
A is the counterfeit coin and it is heavy.
A is the counterfeit coin and it is light.
A is the counterfeit coin and it is light.
A is the counterfeit coin and it is light.
)"};

    testing::internal::CaptureStdout();
    solve_uva(input_file);
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_EQ(expect, output);
}