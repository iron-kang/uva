#include "main.cpp"

TEST(cryptanalysis, test1)
{
    std::ifstream input_file("test1.txt");
    std::string expect = std::string("S 7\nT 6\nI 5\nE 4\nO 3\nA 2\nH 2\n") +
                         "N 2\nU 2\nW 2\nC 1\nM 1\nQ 1\nY 1\n";

    testing::internal::CaptureStdout();
    cryptanalysis(input_file);
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_EQ(expect, output);
}

TEST(cryptanalysis, test2)
{
    std::ifstream input_file("test2.txt");

    std::string expect{
        R"(E 115
T 66
R 61
A 56
N 55
O 54
I 52
S 51
D 36
H 33
M 32
L 30
U 25
Y 22
C 18
P 17
F 10
W 10
B 8
G 8
V 8
J 4
X 4
K 3
Q 3
Z 1
)"};

    testing::internal::CaptureStdout();
    cryptanalysis(input_file);
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_EQ(expect, output);
}

TEST(extract_letters, TEXTS)
{
    std::ifstream input_file("test1.txt");
    std::string expect{
        R"(A 2
C 1
E 4
H 2
I 5
M 1
N 2
O 3
Q 1
S 7
T 6
U 2
W 2
Y 1
)"};
    string line;
    map<char, int, less<char>> letters;

    getline(input_file, line);

    int lines = stoi(line);
    extract_letters(input_file, lines, letters);
    testing::internal::CaptureStdout();

    for (auto &a : letters)
        cout << a.first << " " << a.second << endl;

    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_EQ(expect, output);
}

TEST(extract_letters, SORT)
{
    map<char, int, less<char>> letters;
    vector<pair<char, int>> result;
    std::string expect{
        R"(S 7
T 6
I 5
E 4
O 3
A 2
H 2
N 2
U 2
W 2
C 1
M 1
Q 1
Y 1
)"};

    letters['A'] = 2;
    letters['C'] = 1;
    letters['E'] = 4;
    letters['H'] = 2;
    letters['I'] = 5;
    letters['M'] = 1;
    letters['N'] = 2;
    letters['O'] = 3;
    letters['Q'] = 1;
    letters['S'] = 7;
    letters['T'] = 6;
    letters['U'] = 2;
    letters['W'] = 2;
    letters['Y'] = 1;

    testing::internal::CaptureStdout();
    sort_letters(result, letters);
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_EQ(expect, output);
}