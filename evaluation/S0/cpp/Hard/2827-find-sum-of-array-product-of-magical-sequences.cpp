// Source: https://leetcode.com/problems/find-sum-of-array-product-of-magical-sequences/   |   Difficulty: Hard
//
// Problem Description:
// You are given two integers, m and k, and an integer array nums.
// A sequence of integers seq is called magical if:
//
//
// 	seq has a size of m.
// 	0 <= seq[i] < nums.length
// 	The binary representation of 2seq[0] + 2seq[1] + ... + 2seq[m - 1] has k set bits.
//
//
// The array product of this sequence is defined as prod(seq) = (nums[seq[0]] * nums[seq[1]] * ... * nums[seq[m - 1]]).
//
// Return the sum of the array products for all valid magical sequences.
//
// Since the answer may be large, return it modulo 109 + 7.
//
// A set bit refers to a bit in the binary representation of a number that has a value of 1.
//
// Example:
// Input: m = 5, k = 5, nums = [1,10,100,10000,1000000]
//
// Output: 991600007
//
// Explanation:
//
// All permutations of [0, 1, 2, 3, 4] are magical sequences, each with an array product of 1013.
//
// Constraints:
// 1 <= k <= m <= 30
// 	1 <= nums.length <= 50
// 	1 <= nums[i] <= 108
//

class Solution {
public:
    int magicalSum(int m, int k, vector<int>& nums) {
        const int MOD = 1e9 + 7;
        int n = nums.size();
        
        // Precompute powers of nums[i]
        vector<vector<long long>> powNums(n, vector<long long>(m + 1, 1));
        for (int i = 0; i < n; i++) {
            for (int j = 1; j <= m; j++) {
                powNums[i][j] = (powNums[i][j - 1] * nums[i]) % MOD;
            }
        }
        
        // DP table: dp[i][j][b] = sum of products using first i numbers, j elements, b set bits
        vector<vector<vector<long long>>> dp(n + 1, vector<vector<long long>>(m + 1, vector<long long>(m + 1, 0)));
        dp[0][0][0] = 1;
        
        for (int i = 1; i <= n; i++) {
            for (int j = 0; j <= m; j++) {
                for (int b = 0; b <= m; b++) {
                    for (int x = 0; x <= j; x++) {
                        int newBits = __builtin_popcount(x);
                        if (b + newBits <= m) {
                            dp[i][j][b + newBits] = (dp[i][j][b + newBits] + dp[i - 1][j - x][b] * powNums[i - 1][x]) % MOD;
                        }
                    }
                }
            }
        }
        
        return dp[n][m][k];         
    }
};
