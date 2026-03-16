// Source: https://leetcode.com/problems/valid-permutations-for-di-sequence/   |   Difficulty: Hard
//
// Problem Description:
// You are given a string s of length n where s[i] is either:
//
//
// 	'D' means decreasing, or
// 	'I' means increasing.
//
//
// A permutation perm of n + 1 integers of all the integers in the range [0, n] is called a valid permutation if for all valid i:
//
//
// 	If s[i] == 'D', then perm[i] > perm[i + 1], and
// 	If s[i] == 'I', then perm[i] < perm[i + 1].
//
//
// Return the number of valid permutations perm. Since the answer may be large, return it modulo 109 + 7.
//
// Example:
// Input: s = "DID"
// Output: 5
// Explanation: The 5 valid permutations of (0, 1, 2, 3) are:
// (1, 0, 3, 2)
// (2, 0, 3, 1)
// (2, 1, 3, 0)
// (3, 0, 2, 1)
// (3, 1, 2, 0)
//
// Constraints:
// n == s.length
// 	1 <= n <= 200
// 	s[i] is either 'I' or 'D'.
//

class Solution {
public:
    int numPermsDISequence(string s) {
        const int MOD = 1e9 + 7;
        int n = s.size();
        vector<vector<int>> dp(n + 1, vector<int>(n + 1, 0));
        
        // Base case: for length 1, there's only one permutation
        for (int j = 0; j <= n; j++) {
            dp[0][j] = 1;
        }
        
        for (int i = 1; i <= n; i++) {
            if (s[i - 1] == 'I') {
                // For 'I', accumulate counts from left to right
                int cumSum = 0;
                for (int j = 0; j < i; j++) {
                    cumSum = (cumSum + dp[i - 1][j]) % MOD;
                    dp[i][j] = cumSum;
                }
            } else { // s[i - 1] == 'D'
                // For 'D', accumulate counts from right to left
                int cumSum = 0;
                for (int j = i - 1; j >= 0; j--) {
                    cumSum = (cumSum + dp[i - 1][j]) % MOD;
                    dp[i][j] = cumSum;
                }
            }
        }
        
        // Sum all valid permutations of length n
        int result = 0;
        for (int j = 0; j <= n; j++) {
            result = (result + dp[n][j]) % MOD;
        }
        
        return result;          
    }
};
