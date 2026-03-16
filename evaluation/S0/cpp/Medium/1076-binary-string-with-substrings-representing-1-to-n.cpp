// Source: https://leetcode.com/problems/binary-string-with-substrings-representing-1-to-n/   |   Difficulty: Medium
//
// Problem Description:
// Given a binary string s and a positive integer n, return true if the binary representation of all the integers in the range [1, n] are substrings of s, or false otherwise.
//
// A substring is a contiguous sequence of characters within a string.
//
// Example:
// Input: s = "0110", n = 3
// Output: true
//
// Constraints:
// 1 <= s.length <= 1000
// 	s[i] is either '0' or '1'.
// 	1 <= n <= 109
//

class Solution {
public:
    bool queryString(string s, int n) {
        int maxLen = to_string(n).size() * 4; // Maximum length of binary representation needed
        unordered_set<int> seen;

        for (int i = 0; i < s.size(); ++i) {
            if (s[i] == '0') continue; // Skip leading zeros

            int num = 0;
            for (int j = i; j < s.size() && j < i + maxLen; ++j) {
                num = (num << 1) | (s[j] - '0');
                if (num > n) break;
                seen.insert(num);
            }
        }

        for (int i = 1; i <= n; ++i) {
            if (seen.find(i) == seen.end()) {
                return false;
            }
        }
        return true;            
    }
};
