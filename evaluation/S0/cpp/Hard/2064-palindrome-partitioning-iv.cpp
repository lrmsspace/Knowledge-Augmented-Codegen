// Source: https://leetcode.com/problems/palindrome-partitioning-iv/   |   Difficulty: Hard
//
// Problem Description:
// Given a string s, return true if it is possible to split the string s into three non-empty palindromic substrings. Otherwise, return false.​​​​​
//
// A string is said to be palindrome if it the same string when reversed.
//
// Example:
// Input: s = "abcbdd"
// Output: true
// Explanation: "abcbdd" = "a" + "bcb" + "dd", and all three substrings are palindromes.
//
// Constraints:
// 3 <= s.length <= 2000
// 	s​​​​​​ consists only of lowercase English letters.
//

class Solution {
public:
    bool checkPartitioning(string s) {
        int n = s.size();
        vector<vector<bool>> isPal(n, vector<bool>(n, false));
        
        // Precompute palindromic substrings
        for (int len = 1; len <= n; len++) {
            for (int i = 0; i + len - 1 < n; i++) {
                int j = i + len - 1;
                if (len == 1) {
                    isPal[i][j] = true;
                } else if (len == 2) {
                    isPal[i][j] = (s[i] == s[j]);
                } else {
                    isPal[i][j] = (s[i] == s[j]) && isPal[i + 1][j - 1];
                }
            }
        }
        
        // Try all possible partitions
        for (int i = 0; i < n - 2; i++) {
            if (!isPal[0][i]) continue;
            for (int j = i + 1; j < n - 1; j++) {
                if (isPal[i + 1][j] && isPal[j + 1][n - 1]) {
                    return true;
                }
            }
        }
        
        return false;           
    }
};
