// Source: https://leetcode.com/problems/construct-k-palindrome-strings/   |   Difficulty: Medium
//
// Problem Description:
// Given a string s and an integer k, return true if you can use all the characters in s to construct non-empty k palindrome strings or false otherwise.
//
// Example:
// Input: s = "annabelle", k = 2
// Output: true
// Explanation: You can construct two palindromes using all characters in s.
// Some possible constructions "anna" + "elble", "anbna" + "elle", "anellena" + "b"
//
// Constraints:
// 1 <= s.length <= 105
// 	s consists of lowercase English letters.
// 	1 <= k <= 105
//

class Solution {
public:
    bool canConstruct(string s, int k) {
        if (s.length() < k) {
            return false;
        }

        vector<int> charCount(26, 0);
        for (char c : s) {
            charCount[c - 'a']++;
        }

        int oddCount = 0;
        for (int count : charCount) {
            if (count % 2 != 0) {
                oddCount++;
            }
        }

        return oddCount <= k;           
    }
};
