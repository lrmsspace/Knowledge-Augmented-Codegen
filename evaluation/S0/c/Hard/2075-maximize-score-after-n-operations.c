// Source: https://leetcode.com/problems/maximize-score-after-n-operations/   |   Difficulty: Hard
//
// Problem Description:
// You are given nums, an array of positive integers of size 2 * n. You must perform n operations on this array.
//
// In the ith operation (1-indexed), you will:
//
//
// 	Choose two elements, x and y.
// 	Receive a score of i * gcd(x, y).
// 	Remove x and y from nums.
//
//
// Return the maximum score you can receive after performing n operations.
//
// The function gcd(x, y) is the greatest common divisor of x and y.
//
// Example:
// Input: nums = [1,2]
// Output: 1
// Explanation: The optimal choice of operations is:
// (1 * gcd(1, 2)) = 1
//
// Constraints:
// 1 <= n <= 7
// 	nums.length == 2 * n
// 	1 <= nums[i] <= 106
//

int maxScore(int* nums, int numsSize) {
    int n = numsSize / 2;
    int maxState = 1 << numsSize;
    int gcdTable[numsSize][numsSize];
    int dp[maxState];
    memset(dp, 0, sizeof(dp));

    // Precompute GCD for all pairs
    for (int i = 0; i < numsSize; ++i) {
        for (int j = 0; j < numsSize; ++j) {
            int a = nums[i], b = nums[j];
            while (b) {
                int temp = b;
                b = a % b;
                a = temp;
            }
            gcdTable[i][j] = a;
        }
    }

    // DP over all states
    for (int state = 0; state < maxState; ++state) {
        int count = __builtin_popcount(state);
        if (count % 2 != 0) continue; // Only consider states with even number of elements

        int operation = count / 2 + 1;
        for (int i = 0; i < numsSize; ++i) {
            if (!(state & (1 << i))) {
                for (int j = i + 1; j < numsSize; ++j) {
                    if (!(state & (1 << j))) {
                        int newState = state | (1 << i) | (1 << j);
                        int score = operation * gcdTable[i][j];
                        dp[newState] = fmax(dp[newState], dp[state] + score);
                    }
                }
            }
        }
    }

    return dp[maxState - 1];
}
