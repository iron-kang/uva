#include "main.cpp"

TEST(cryptanalysis, test1)
{
    std::ifstream input_file("test1.txt");
    std::string expect = std::string("S 7\nT 6\nI 5\nE 4\nO 3\nA 2\nH 2\n") +
                         "N 2\nU 2\nW 2\nC 1\nM 1\nQ 1\nY 1\n";

    char tmp[256];
    getcwd(tmp, 256);
    cout << "Current working directory: " << tmp << endl;
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