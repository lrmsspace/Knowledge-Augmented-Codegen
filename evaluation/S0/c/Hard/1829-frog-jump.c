// Source: https://leetcode.com/problems/frog-jump/   |   Difficulty: Hard
//
// Problem Description:
// A frog is crossing a river. The river is divided into some number of units, and at each unit, there may or may not exist a stone. The frog can jump on a stone, but it must not jump into the water.
//
// Given a list of stones positions (in units) in sorted ascending order, determine if the frog can cross the river by landing on the last stone. Initially, the frog is on the first stone and assumes the first jump must be 1 unit.
//
// If the frog's last jump was k units, its next jump must be either k - 1, k, or k + 1 units. The frog can only jump in the forward direction.
//
// Example:
// Input: stones = [0,1,3,5,6,8,12,17]
// Output: true
// Explanation: The frog can jump to the last stone by jumping 1 unit to the 2nd stone, then 2 units to the 3rd stone, then 2 units to the 4th stone, then 3 units to the 6th stone, 4 units to the 7th stone, and 5 units to the 8th stone.
//
// Constraints:
// 2 <= stones.length <= 2000
// 	0 <= stones[i] <= 231 - 1
// 	stones[0] == 0
// 	stones is sorted in a strictly increasing order.
//

bool canCross(int* stones, int stonesSize) {
    bool **dp = (bool**)malloc(stonesSize * sizeof(bool*));
    for (int i = 0; i < stonesSize; ++i) {
        dp[i] = (bool*)calloc(stonesSize, sizeof(bool));
    }
    dp[0][0] = true;

    for (int i = 1; i < stonesSize; ++i) {
        for (int j = i - 1; j >= 0; --j) {
            int gap = stones[i] - stones[j];
            if (gap > j + 1) break; // cannot reach stone i from stone j

            // check possible last jumps: gap-1, gap, gap+1
            if (gap - 1 >= 0 && dp[j][gap - 1]) {
                dp[i][gap] = true;
            }
            if (dp[j][gap]) {
                dp[i][gap] = true;
            }
            if (gap + 1 < stonesSize && dp[j][gap + 1]) {
                dp[i][gap] = true;
            }
        }
    }

    bool result = false;
    for (int k = 0; k < stonesSize; ++k) {
        if (dp[stonesSize - 1][k]) {
            result = true;
            break;
        }
    }

    for (int i = 0; i < stonesSize; ++i) {
        free(dp[i]);
    }
    free(dp);

    return result;      
}
