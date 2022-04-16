#include "main.cpp"

TEST(LongetsNap, add_schedule)
{
    std::ifstream input_file("test1.txt");
    std::string expect{
        R"(11:00 12:00
12:00 12:01
12:01 13:00
13:00 15:00
15:30 15:31
)"};

    testing::internal::CaptureStdout();
    std::string line;
    auto longetsnap = std::make_shared<LongetsNap>();

    while (getline(input_file, line))
        longetsnap->add_schedule(line);

    longetsnap->print_schedule();
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_EQ(expect, output);
}

TEST(LongetsNap, get_longest_nap)
{
    std::ifstream input_file("test2.txt");
    std::string expect{
        R"(Day #1: the longest nap starts at 15:00 and will last for 30 minutes.
Day #2: the longest nap starts at 15:00 and will last for 1 hours and 45 minutes.
Day #3: the longest nap starts at 17:15 and will last for 45 minutes.
Day #4: the longest nap starts at 13:00 and will last for 5 hours and 0 minutes.
Day #5: the longest nap starts at 10:00 and will last for 2 hours and 0 minutes.
Day #6: the longest nap starts at 16:00 and will last for 1 minutes.
)"};

    testing::internal::CaptureStdout();
    solve_uva(input_file);
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_EQ(expect, output);
}
