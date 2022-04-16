#include <iostream>
#include <fstream>
#include <sstream>
#include <memory>
#include <queue>
#include <iomanip>
#include <algorithm>
// #define ONLINE_JUDGE
#ifndef ONLINE_JUDGE
#include <gmock/gmock.h>
#endif

class LongetsNap
{
public:
    struct schedule_t
    {
        int start_time_;
        int end_time_;
        schedule_t(int start, int end)
            : start_time_(start), end_time_(end)
        {
        }
    };

    LongetsNap()
    {
        schedules_.push_back(schedule_t(10 * 60, 10 * 60));
        schedules_.push_back(schedule_t(18 * 60, 18 * 60));
    };

    void add_schedule(const std::string &schedule)
    {
        std::istringstream ss(schedule);
        char c1, c2;
        int hh, mm, hh2, mm2;

        ss >> hh >> c1 >> mm >> hh2 >> c2 >> mm2;

        schedules_.push_back(schedule_t(hh * 60 + mm, hh2 * 60 + mm2));
    }

    void print_schedule(void)
    {
        std::sort(schedules_.begin(), schedules_.end(), cmp);
        for (std::size_t i = 1; i < schedules_.size() - 1; i++)
        {
            std::cout << schedules_[i].start_time_ / 60 << ":"
                      << std::setw(2) << std::setfill('0')
                      << schedules_[i].start_time_ % 60
                      << " " << schedules_[i].end_time_ / 60
                      << ":" << std::setw(2) << std::setfill('0')
                      << schedules_[i].end_time_ % 60 << std::endl;
        }
    }

    void get_longest_nap(int &longest_nap, int &start_time)
    {
        std::sort(schedules_.begin(), schedules_.end(), cmp);

        for (std::size_t i = 0; i < schedules_.size() - 1; i++)
        {
            int nap = schedules_[i + 1].start_time_ - schedules_[i].end_time_;
            if (nap > longest_nap)
            {
                longest_nap = nap;
                start_time = schedules_[i].end_time_;
            }
        }
    }

private:
    std::vector<schedule_t> schedules_;

    static bool cmp(const schedule_t &s1, const schedule_t &s2)
    {
        return s1.start_time_ < s2.start_time_;
    }
};

void solve_uva(std::istream &in)
{
    std::string line;
    int day = 1;

    while (true)
    {
        std::getline(in, line);
        if (line == "")
            break;

        int nums = stoi(line);

        auto longetsnap = std::make_shared<LongetsNap>();

        while (nums-- > 0)
        {
            std::getline(in, line);

            longetsnap->add_schedule(line);
        }

        int longest_nap = 0;
        int start_time = 0;
        longetsnap->get_longest_nap(longest_nap, start_time);
        std::ostringstream out;
        out << "Day #" << day++ << ": "
            << "the longest nap starts at " << start_time / 60 << ":" << std::setw(2) << std::setfill('0')
            << start_time % 60 << " and will last for ";
        if ((longest_nap / 60) > 0)
            out << longest_nap / 60 << " hours and ";

        out << longest_nap % 60 << " minutes.";
        std::cout << out.str() << std::endl;
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
