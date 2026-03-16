// Source: https://leetcode.com/problems/find-the-maximum-sequence-value-of-array/   |   Difficulty: Hard
//
// Problem Description:
// You are given an integer array nums and a positive integer k.
//
// The value of a sequence seq of size 2 * x is defined as:
//
//
// 	(seq[0] OR seq[1] OR ... OR seq[x - 1]) XOR (seq[x] OR seq[x + 1] OR ... OR seq[2 * x - 1]).
//
//
// Return the maximum value of any subsequence of nums having size 2 * k.
//
// Example:
// Input: nums = [2,6,7], k = 1
//
// Output: 5
//
// Explanation:
//
// The subsequence [2, 7] has the maximum value of 2 XOR 7 = 5.
//
// Constraints:
// 2 <= nums.length <= 400
// 	1 <= nums[i] < 27
// 	1 <= k <= nums.length / 2
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
    int maxValue(vector<int>& nums, int k) {
        int n = nums.size();
        vector<vector<int>> dp(n + 1, vector<int>(k + 1, 0));
        for (int i = 1; i <= n; ++i) {
            for (int j = 1; j <= min(i / 2, k); ++j) {
                dp[i][j] = max(dp[i - 1][j], dp[i - 2][j - 1] ^ nums[i - 1]);
            }
        }
        return dp[n][k];            
    }
};
