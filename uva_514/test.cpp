#include "main.cpp"

TEST(Rails, test1)
{
    std::ifstream input_file("test1.txt");
    std::string expect{
        R"(Yes
Yes
No

Yes


)"};

    testing::internal::CaptureStdout();
    solve_uva(input_file);
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_EQ(expect, output);
}

TEST(Rails, test2)
{
    std::ifstream input_file("test2.txt");
    std::string expect{
        R"(Yes
No
Yes
Yes
Yes
Yes

Yes
Yes
Yes
Yes
No
Yes

Yes
Yes
Yes
Yes
No
Yes
Yes
Yes
Yes
Yes
No
Yes
No
No
Yes
Yes
No
Yes
No
No
No
No
No
Yes

Yes
Yes


)"};

    testing::internal::CaptureStdout();
    solve_uva(input_file);
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_EQ(expect, output);
}

TEST(Rails, test3)
{
    std::ifstream input_file("test3.txt");
    std::string expect{
        R"(Yes
No
Yes
Yes
No
Yes
Yes
No
No
No
Yes
Yes
No
No
No
Yes
Yes
Yes
Yes
No

Yes
Yes
No
Yes
No
No
Yes
No
No

Yes
No
Yes
Yes
Yes
No
No
Yes
No
Yes

Yes
Yes
No
No
No
No
Yes
No
No
Yes
No
No
Yes
Yes
No
Yes
Yes
No
Yes
Yes
No

No
Yes
Yes
Yes
No
Yes
No
No
No
No
No
Yes
No
Yes
Yes
Yes
No
No
No

No
Yes
Yes
No
No
Yes
Yes
Yes
No
No
Yes
Yes
Yes
Yes
No

No
No
No
Yes
No
No
No
No
Yes
Yes
Yes
No

No
No
No
No
Yes
No
Yes
Yes
No
No
Yes
Yes

No
No
Yes
No
Yes
No
Yes
No
No
Yes
No
Yes
Yes
No
No
No
No
Yes
Yes
Yes
Yes

Yes
No
Yes
Yes
Yes
Yes
Yes
No
No
Yes
Yes

No
No
Yes
No
Yes
Yes
Yes
Yes
Yes
Yes
Yes
Yes

Yes
Yes
Yes
No
Yes
Yes
No
Yes
No
Yes
Yes
Yes
No
Yes
Yes
No
Yes
Yes
No
Yes
No

Yes
No
No
No
Yes
No
Yes
No
No
Yes
Yes
No
Yes
Yes
No
Yes
No
No
No

No
Yes

Yes
No
No
Yes
Yes
No
Yes
No
Yes
Yes
No
Yes
No
No
Yes
Yes

No
No
No
No
No
No
No
Yes
No
No
No
No
No
Yes
No
No
No
Yes
Yes

No
Yes
No

Yes
Yes
No
No
No
Yes
No
No

No
No
No
No
Yes
Yes
No
Yes
Yes
No
No
Yes
No
Yes
No
Yes

Yes
Yes
Yes
Yes
Yes
No

No
Yes
No
No
No
Yes
Yes


)"};

    testing::internal::CaptureStdout();
    solve_uva(input_file);
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_EQ(expect, output);
}