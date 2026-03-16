// Source: https://leetcode.com/problems/count-the-number-of-inversions/   |   Difficulty: Hard
//
// Problem Description:
// You are given an integer n and a 2D array requirements, where requirements[i] = [endi, cnti] represents the end index and the inversion count of each requirement.
//
// A pair of indices (i, j) from an integer array nums is called an inversion if:
//
//
// 	i < j and nums[i] > nums[j]
//
//
// Return the number of permutations perm of [0, 1, 2, ..., n - 1] such that for all requirements[i], perm[0..endi] has exactly cnti inversions.
//
// Since the answer may be very large, return it modulo 109 + 7.
//
// Example:
// Input: n = 3, requirements = [[2,2],[0,0]]
//
// Output: 2
//
// Explanation:
//
// The two permutations are:
//
//
// 	[2, 0, 1]
//
// 	
// 		Prefix [2, 0, 1] has inversions (0, 1) and (0, 2).
// 		Prefix [2] has 0 inversions.
// 	
// 	
// 	[1, 2, 0]
// 	
// 		Prefix [1, 2, 0] has inversions (0, 2) and (1, 2).
// 		Prefix [1] has 0 inversions.
//
// Constraints:
// 2 <= n <= 300
// 	1 <= requirements.length <= n
// 	requirements[i] = [endi, cnti]
// 	0 <= endi <= n - 1
// 	0 <= cnti <= 400
// 	The input is generated such that there is at least one i such that endi == n - 1.
// 	The input is generated such that all endi are unique.
//

class Solution {
public:
    int numberOfPermutations(int n, vector<vector<int>>& requirements) {
        const int MOD = 1e9 + 7;
        vector<vector<int>> dp(n, vector<int>(n * (n - 1) / 2 + 1, 0));
        dp[0][0] = 1;

        for (int i = 1; i < n; ++i) {
            for (int j = 0; j <= i * (i - 1) / 2; ++j) {
                for (int k = 0; k <= i; ++k) {
                    if (j + k <= n * (n - 1) / 2) {
                        dp[i][j + k] = (dp[i][j + k] + dp[i - 1][j]) % MOD;
                    }
                }
            }
        }

        unordered_map<int, int> reqMap;
        for (const auto& req : requirements) {
            reqMap[req[0]] = req[1];
        }

        long long result = 0;
        for (int invCount = 0; invCount <= n * (n - 1) / 2; ++invCount) {
            bool valid = true;
            for (const auto& [endIdx, cnt] : reqMap) {
                if (invCount < cnt || invCount > endIdx * (endIdx + 1) / 2) {
                    valid = false;
                    break;
                }
            }
            if (valid) {
                result = (result + dp[n - 1][invCount]) % MOD;
            }
        }

        return static_cast<int>(result);            
    }
};
