// Source: https://leetcode.com/problems/minimum-consecutive-cards-to-pick-up/   |   Difficulty: Medium
//
// Problem Description:
// You are given an integer array cards where cards[i] represents the value of the ith card. A pair of cards are matching if the cards have the same value.
//
// Return the minimum number of consecutive cards you have to pick up to have a pair of matching cards among the picked cards. If it is impossible to have matching cards, return -1.
//
// Example:
// Input: cards = [3,4,2,3,4,7]
// Output: 4
// Explanation: We can pick up the cards [3,4,2,3] which contain a matching pair of cards with value 3. Note that picking up the cards [4,2,3,4] is also optimal.
//
// Constraints:
// 1 <= cards.length <= 105
// 	0 <= cards[i] <= 106
//

class Solution {
public:
    int minimumCardPickup(vector<int>& cards) {
        unordered_map<int, int> lastIndex;
        int minLength = INT_MAX;

        for (int i = 0; i < cards.size(); ++i) {
            int card = cards[i];
            if (lastIndex.find(card) != lastIndex.end()) {
                int length = i - lastIndex[card] + 1;
                minLength = min(minLength, length);
            }
            lastIndex[card] = i;
        }

        return (minLength == INT_MAX) ? -1 : minLength;         
    }
};
