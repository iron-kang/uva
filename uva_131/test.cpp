#include "main.cpp"

TEST(Poker, test)
{
    std::ifstream input_file("test.txt");
    std::string expect{
        R"(Hand: TH JH QC QD QS Deck: QH KH AH 2S 6S Best hand: straight-flush
Hand: 2H 2S 3H 3S 3C Deck: 2D 3D 6C 9C TH Best hand: four-of-a-kind
Hand: 2H 2S 3H 3S 3C Deck: 2D 9C 3D 6C TH Best hand: full-house
Hand: 2H AD 5H AC 7H Deck: AH 6H 9H 4H 3C Best hand: flush
Hand: AC 2D 9C 3S KD Deck: 5S 4D KS AS 4C Best hand: straight
Hand: KS AH 2H 3C 4H Deck: KC 2C TC 2D AS Best hand: three-of-a-kind
Hand: AH 2C 9S AD 3C Deck: QH KS JS JD KD Best hand: two-pairs
Hand: 6C 9C 8C 2D 7C Deck: 2H TC 4C 9S AH Best hand: one-pair
Hand: 3D 5S 2H QD TD Deck: 6S KH 9H AD QH Best hand: highest-card
Hand: TH JH QC QD QS Deck: QH KH AH 2S 6S Best hand: straight-flush
Hand: 2D 3D 6C 9C TH Deck: 2H 2S 3H 3S 3C Best hand: full-house
Hand: 2D 9C 3D 6C TH Deck: 2H 2S 3H 3S 3C Best hand: full-house
Hand: AH 6H 9H 4H 3C Deck: 2H AD 5H AC 7H Best hand: flush
Hand: 5S 4D KS AS 4C Deck: AC 2D 9C 3S KD Best hand: two-pairs
Hand: KC 2C TC 2D AS Deck: KS AH 2H 3C 4H Best hand: three-of-a-kind
Hand: QH KS JS JD KD Deck: AH 2C 9S AD 3C Best hand: two-pairs
Hand: 2H TC 4C 9S AH Deck: 6C 9C 8C 2D 7C Best hand: flush
Hand: 6S KH 9H AD QH Deck: 3D 5S 2H QD TD Best hand: one-pair
)"};

    testing::internal::CaptureStdout();
    solve_uva(input_file);
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_EQ(expect, output);
}