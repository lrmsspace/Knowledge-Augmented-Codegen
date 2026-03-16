// Source: https://leetcode.com/problems/valid-palindrome-ii/   |   Difficulty: Easy
//
// Problem Description:
// Given a string s, return true if the s can be palindrome after deleting at most one character from it.
//
// Example:
// Input: s = "aba"
// Output: true
//
// Constraints:
// 1 <= s.length <= 105
// 	s consists of lowercase English letters.
//

class Solution {
public:
    bool validPalindrome(string s) {
        int left = 0, right = s.size() - 1;

        while (left < right) {
            if (s[left] != s[right]) {
                return isPalindrome(s, left + 1, right) || isPalindrome(s, left, right - 1);
            }
            left++;
            right--;
        }

        return true;            
    }
};
