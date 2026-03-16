// Source: https://leetcode.com/problems/flip-string-to-monotone-increasing/   |   Difficulty: Medium
//
// Problem Description:
// A binary string is monotone increasing if it consists of some number of 0's (possibly none), followed by some number of 1's (also possibly none).
//
// You are given a binary string s. You can flip s[i] changing it from 0 to 1 or from 1 to 0.
//
// Return the minimum number of flips to make s monotone increasing.
//
// Example:
// Input: s = "00110"
// Output: 1
// Explanation: We flip the last digit to get 00111.
//
// Constraints:
// 1 <= s.length <= 105
// 	s[i] is either '0' or '1'.
//

class Solution {
public:
    int minFlipsMonoIncr(string s) {
        int n = s.size();
        vector<int> prefixOnes(n + 1, 0);
        for (int i = 0; i < n; ++i) {
            prefixOnes[i + 1] = prefixOnes[i] + (s[i] == '1' ? 1 : 0);
        }

        int minFlips = n; // Initialize with a large number
        for (int j = 0; j <= n; ++j) {
            int flips = prefixOnes[j] + (n - j) - (prefixOnes[n] - prefixOnes[j]);
            minFlips = min(minFlips, flips);
        }

        return minFlips;            
    }
};
