// Source: https://leetcode.com/problems/hand-of-straights/   |   Difficulty: Medium
//
// Problem Description:
// Alice has some number of cards and she wants to rearrange the cards into groups so that each group is of size groupSize, and consists of groupSize consecutive cards.
//
// Given an integer array hand where hand[i] is the value written on the ith card and an integer groupSize, return true if she can rearrange the cards, or false otherwise.
//
// Example:
// Input: hand = [1,2,3,6,2,3,4,7,8], groupSize = 3
// Output: true
// Explanation: Alice's hand can be rearranged as [1,2,3],[2,3,4],[6,7,8]
//
// Constraints:
// 1 <= hand.length <= 104
// 	0 <= hand[i] <= 109
// 	1 <= groupSize <= hand.length
//
//
//  
// Note: This question is the same as 1296: https://leetcode.com/problems/divide-array-in-sets-of-k-consecutive-numbers/
//

bool isNStraightHand(int* hand, int handSize, int groupSize) {
    if (handSize % groupSize != 0) {
        return false;
    }

    // Count the frequency of each card
    #define MAX_CARDS 10000
    #define OFFSET 1000000000
    int count[2 * OFFSET + 1] = {0};
    for (int i = 0; i < handSize; i++) {
        count[hand[i] + OFFSET]++;
    }

    // Try to form groups starting from the smallest card
    for (int i = 0; i < 2 * OFFSET + 1; i++) {
        while (count[i] > 0) {
            for (int j = 0; j < groupSize; j++) {
                if (count[i + j] <= 0) {
                    return false;
                }
                count[i + j]--;
            }
        }
    }

    return true;        
}
