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

class Solution {
public:
    bool isNStraightHand(vector<int>& hand, int groupSize) {
        int n = hand.size();
        if (n % groupSize != 0) return false;

        unordered_map<int, int> countMap;
        for (int card : hand) {
            countMap[card]++;
        }

        priority_queue<int, vector<int>, greater<int>> minHeap;
        for (const auto& entry : countMap) {
            minHeap.push(entry.first);
        }

        while (!minHeap.empty()) {
            int start = minHeap.top();
            for (int i = 0; i < groupSize; ++i) {
                int card = start + i;
                if (countMap.find(card) == countMap.end()) {
                    return false;
                }
                countMap[card]--;
                if (countMap[card] == 0) {
                    if (card != minHeap.top()) {
                        return false;
                    }
                    minHeap.pop();
                }
            }
        }

        return true;            
    }
};
