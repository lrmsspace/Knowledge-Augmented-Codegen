// Source: https://leetcode.com/problems/smallest-palindromic-rearrangement-i/   |   Difficulty: Medium
//
// Problem Description:
// You are given a palindromic string s.
//
// Return the lexicographically smallest palindromic permutation of s.
//
// Example:
// Input: s = "z"
//
// Output: "z"
//
// Explanation:
//
// A string of only one character is already the lexicographically smallest palindrome.
//
// Constraints:
// 1 <= s.length <= 105
// 	s consists of lowercase English letters.
// 	s is guaranteed to be palindromic.
//

class Solution {
public:
    string smallestPalindrome(string s) {
        vector<int> count(26, 0);
        for (char c : s) {
            count[c - 'a']++;
        }

        string half = "";
        for (int i = 0; i < 26; ++i) {
            half += string(count[i] / 2, 'a' + i);
        }

        string palindrome = half;
        // If the length of s is odd, add the middle character
        for (int i = 0; i < 26; ++i) {
            if (count[i] % 2 == 1) {
                palindrome += ('a' + i);
                break;
            }
        }
        reverse(half.begin(), half.end());
        palindrome += half;

        return palindrome;          
    }
};
