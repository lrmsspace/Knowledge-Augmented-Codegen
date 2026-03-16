// Source: https://leetcode.com/problems/find-the-occurrence-of-first-almost-equal-substring/   |   Difficulty: Hard
//
// Problem Description:
// You are given two strings s and pattern.
//
// A string x is called almost equal to y if you can change at most one character in x to make it identical to y.
//
// Return the smallest starting index of a substring in s that is almost equal to pattern. If no such index exists, return -1.
// A substring is a contiguous non-empty sequence of characters within a string.
//
// Example:
// Input: s = "abcdefg", pattern = "bcdffg"
//
// Output: 1
//
// Explanation:
//
// The substring s[1..6] == "bcdefg" can be converted to "bcdffg" by changing s[4] to "f".
//
// Constraints:
// 1 <= pattern.length < s.length <= 105
// 	s and pattern consist only of lowercase English letters.
//
//
//  
// Follow-up: Could you solve the problem if at most k consecutive characters can be changed?
//

class Solution {
public:
    int minStartingIndex(string s, string pattern) {
        int n = s.size();
        int m = pattern.size();
        
        for (int i = 0; i <= n - m; i++) {
            int diffCount = 0;
            for (int j = 0; j < m; j++) {
                if (s[i + j] != pattern[j]) {
                    diffCount++;
                    if (diffCount > 1) break;
                }
            }
            if (diffCount <= 1) {
                return i;
            }
        }
        
        return -1;          
    }
};
