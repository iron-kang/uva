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

typedef enum
{
    N = 0,
    E,
    S,
    W
} DIR;

class Position
{
public:
    Position(const int &row = 0, const int &col = 0)
        : row_(row), col_(col){};

    int row_;
    int col_;

    Position operator+(const Position &pos) const
    {
        return Position(row_ + pos.row_, col_ + pos.col_);
    }
};

class Maze
{
public:
    Maze(const int &row, const int &col)
    {
        row_ = row;
        col_ = col;

        maze.resize(row, std::vector<int>(col, 0));
    }

    void get_maze(std::istream &in)
    {
        char c;
        for (int i = 0; i < row_; i++)
        {
            for (int j = 0; j < col_; j++)
            {
                do
                {
                    in.get(c);
                } while ((c) == '\n');
                maze[i][j] = c == '*' ? 1 : 0;
            }
        }
    }
    bool is_wall(Position pos)
    {
        return maze[pos.row_][pos.col_];
    }

private:
    std::vector<std::vector<int>> maze;
    int row_;
    int col_;
};

class Robot
{
public:
    Robot(const Position &init_pos, const Maze &maze)
        : maze_(maze), dir_(N)
    {
        pos_.row_ = init_pos.row_ - 1;
        pos_.col_ = init_pos.col_ - 1;
    }

    void run(std::istream &in)
    {
        char c;
        do
        {
            in.get(c);
            if ((c == '\n') || (c == ' '))
                continue;
            if (c == 'F')
            {
                Position tmp_pos = pos_ + dir_step[dir_];
                if (!maze_.is_wall(tmp_pos))
                {
                    pos_ = tmp_pos;
                }
            }
            else
            {
                dir_ = (dir_ + cmd[c] + 4) % 4;
            }
        } while (c != 'Q');
        pos_ = pos_ + Position(1, 1);
    }
    char get_dir() { return dir_map[dir_]; }
    Position get_pos()
    {
        return pos_;
    }

private:
    Maze maze_;
    Position pos_;
    int dir_;
    Position dir_step[4] = {
        {-1, 0},
        {0, 1},
        {1, 0},
        {0, -1}};
    std::map<char, int> cmd = {
        {'R', 1},
        {'L', -1}};
    std::map<int, char> dir_map = {
        {0, 'N'},
        {1, 'E'},
        {2, 'S'},
        {3, 'W'},
    };
};

void solve_uva(std::istream &in)
{
    int sample_count = 0;
    in >> sample_count;
    int row, col;

    while (sample_count-- > 0)
    {
        in >> row;
        in >> col;

        Maze maze(row, col);
        maze.get_maze(in);

        Position pos;
        in >> pos.row_;
        in >> pos.col_;

        Robot robot(pos, maze);
        robot.run(in);
        pos = robot.get_pos();

        std::cout << pos.row_ << " " << pos.col_ << " " << robot.get_dir() << std::endl
                  << std::endl;
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
