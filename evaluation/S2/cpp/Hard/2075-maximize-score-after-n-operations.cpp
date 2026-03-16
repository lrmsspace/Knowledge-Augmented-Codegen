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
// Helpful references (internal KB):
// - N/A
//
// Notes:
// - Keep the given function signature unchanged.
// - Use standard C++ only; do NOT rely on non-standard extensions or platform-specific APIs.
// - Do not change input/output formats or return value semantics.
// - Conformance: Prefer modern standard C++ (C++11/14/17) features that are portable; avoid compiler-specific extensions (e.g., __int128 unless necessary and supported).
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
public:
    int maxScore(vector<int>& nums) {
        int n = nums.size() / 2;
        vector<vector<int>> gcd(n * 2, vector<int>(n * 2, 0));
        
        // Precompute GCD values for all pairs
        for (int i = 0; i < nums.size(); ++i) {
            for (int j = i + 1; j < nums.size(); ++j) {
                gcd[i][j] = gcd[j][i] = std::gcd(nums[i], nums[j]);
            }
        }

        // DP array to store maximum score for each state of used numbers
        vector<int> dp(1 << (n * 2), 0);

        // Iterate through all states of used numbers
        for (int mask = 0; mask < (1 << (n * 2)); ++mask) {
            int count = __builtin_popcount(mask); // Count how many numbers are used
            if (count % 2 != 0) continue; // We can only pair up numbers

            int operation = count / 2 + 1; // Current operation number
            for (int i = 0; i < nums.size(); ++i) {
                if ((mask & (1 << i)) != 0) continue; // Skip if number is already used
                for (int j = i + 1; j < nums.size(); ++j) {
                    if ((mask & (1 << j)) != 0) continue; // Skip if number is already used

                    int newMask = mask | (1 << i) | (1 << j); // Mark these two numbers as used
                    dp[newMask] = max(dp[newMask], dp[mask] + operation * gcd[i][j]); // Update DP with the new score
                }
            }
        }

        return dp[(1 << (n * 2)) - 1]; // Return the maximum score when all numbers are used            
    }
};
