// Source: https://leetcode.com/problems/minimum-cost-to-move-chips-to-the-same-position/   |   Difficulty: Easy
//
// Problem Description:
// We have n chips, where the position of the ith chip is position[i].
//
// We need to move all the chips to the same position. In one step, we can change the position of the ith chip from position[i] to:
//
//
// 	position[i] + 2 or position[i] - 2 with cost = 0.
// 	position[i] + 1 or position[i] - 1 with cost = 1.
//
//
// Return the minimum cost needed to move all the chips to the same position.
//
// Example:
// Input: position = [1,2,3]
// Output: 1
// Explanation: First step: Move the chip at position 3 to position 1 with cost = 0.
// Second step: Move the chip at position 2 to position 1 with cost = 1.
// Total cost is 1.
//
// Constraints:
// 1 <= position.length <= 100
// 	1 <= position[i] <= 10^9
//

class Solution {
public:
    int minCostToMoveChips(vector<int>& position) {
        int evenCount = 0;
        int oddCount = 0;

        for (int pos : position) {
            if (pos % 2 == 0) {
                evenCount++;
            } else {
                oddCount++;
            }
        }

        return min(evenCount, oddCount);            
    }
};
