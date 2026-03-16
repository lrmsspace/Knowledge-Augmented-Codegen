// Source: https://leetcode.com/problems/longest-palindrome-after-substring-concatenation-i/   |   Difficulty: Medium
//
// Problem Description:
// You are given two strings, s and t.
//
// You can create a new string by selecting a substring from s (possibly empty) and a substring from t (possibly empty), then concatenating them in order.
//
// Return the length of the longest palindrome that can be formed this way.
//
// Example:
// Input: s = "a", t = "a"
//
// Output: 2
//
// Explanation:
//
// Concatenating "a" from s and "a" from t results in "aa", which is a palindrome of length 2.
//
// Constraints:
// 1 <= s.length, t.length <= 30
// 	s and t consist of lowercase English letters.
//

class Solution {
public:
    int longestPalindrome(string s, string t) {
        int maxLength = 0;
        int n = s.size();
        int m = t.size();

        // Check all substrings of s
        for (int i = 0; i <= n; ++i) {
            for (int j = i; j <= n; ++j) {
                string subS = s.substr(i, j - i);
                string revSubS = subS;
                reverse(revSubS.begin(), revSubS.end());

                // Check all substrings of t
                for (int p = 0; p <= m; ++p) {
                    for (int q = p; q <= m; ++q) {
                        string subT = t.substr(p, q - p);
                        string candidate = subS + subT;

                        // Check if candidate is a palindrome
                        if (isPalindrome(candidate)) {
                            maxLength = max(maxLength, (int)candidate.size());
                        }
                    }
                }
            }
        }

        return maxLength;           
    }
};
