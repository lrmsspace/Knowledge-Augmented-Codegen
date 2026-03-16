// Source: https://leetcode.com/problems/partition-string-into-minimum-beautiful-substrings/   |   Difficulty: Medium
//
// Problem Description:
// Given a binary string s, partition the string into one or more substrings such that each substring is beautiful.
//
// A string is beautiful if:
//
//
// 	It doesn't contain leading zeros.
// 	It's the binary representation of a number that is a power of 5.
//
//
// Return the minimum number of substrings in such partition. If it is impossible to partition the string s into beautiful substrings, return -1.
//
// A substring is a contiguous sequence of characters in a string.
//
// Example:
// Input: s = "1011"
// Output: 2
// Explanation: We can paritition the given string into ["101", "1"].
// - The string "101" does not contain leading zeros and is the binary representation of integer 51 = 5.
// - The string "1" does not contain leading zeros and is the binary representation of integer 50 = 1.
// It can be shown that 2 is the minimum number of beautiful substrings that s can be partitioned into.
//
// Constraints:
// 1 <= s.length <= 15
// 	s[i] is either '0' or '1'.
//

class Solution {
public:
    int minimumBeautifulSubstrings(string s) {
        const vector<int> powersOf5 = {
            1, 5, 25, 125, 625, 3125, 15625, 78125, 390625, 1953125, 9765625, 48828125, 244140625
        };

        const int n = s.size();
        vector<int> dp(n + 1, INT_MAX);
        dp[0] = 0;

        for (int i = 1; i <= n; ++i) {
            for (int j = i - 1; j >= 0; --j) {
                if (s[j] == '0') continue; // Leading zero check

                int num = 0;
                for (int k = j; k < i; ++k) {
                    num = (num << 1) | (s[k] - '0');
                }

                if (find(powersOf5.begin(), powersOf5.end(), num) != powersOf5.end()) {
                    dp[i] = min(dp[i], dp[j] + 1);
                }
            }
        }

        return dp[n] == INT_MAX ? -1 : dp[n];           
    }
};
