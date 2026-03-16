// Source: https://leetcode.com/problems/x-of-a-kind-in-a-deck-of-cards/   |   Difficulty: Easy
//
// Problem Description:
// You are given an integer array deck where deck[i] represents the number written on the ith card.
//
// Partition the cards into one or more groups such that:
//
//
// 	Each group has exactly x cards where x > 1, and
// 	All the cards in one group have the same integer written on them.
//
//
// Return true if such partition is possible, or false otherwise.
//
// Example:
// Input: deck = [1,2,3,4,4,3,2,1]
// Output: true
// Explanation: Possible partition [1,1],[2,2],[3,3],[4,4].
//
// Constraints:
// 1 <= deck.length <= 104
// 	0 <= deck[i] < 104
//

bool hasGroupsSizeX(int* deck, int deckSize) {
    int count[10000] = {0};
    for (int i = 0; i < deckSize; i++) {
        count[deck[i]]++;
    }

    int gcd = 0;
    for (int i = 0; i < 10000; i++) {
        if (count[i] > 0) {
            if (gcd == 0) {
                gcd = count[i];
            } else {
                int a = gcd, b = count[i];
                while (b != 0) {
                    int temp = b;
                    b = a % b;
                    a = temp;
                }
                gcd = a;
            }
        }
    }

    return gcd >= 2;        
}
