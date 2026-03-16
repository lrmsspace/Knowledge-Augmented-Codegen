// Source: https://leetcode.com/problems/reverse-only-letters/   |   Difficulty: Easy
//
// Problem Description:
// Given a string s, reverse the string according to the following rules:
//
//
// 	All the characters that are not English letters remain in the same position.
// 	All the English letters (lowercase or uppercase) should be reversed.
//
//
// Return s after reversing it.
//
// Example:
// Input: s = "ab-cd"
// Output: "dc-ba"
//
// Constraints:
// 1 <= s.length <= 100
// 	s consists of characters with ASCII values in the range [33, 122].
// 	s does not contain '\"' or '\\'.
//

class Solution {
public:
    string reverseOnlyLetters(string s) {
        int left = 0, right = s.size() - 1;

        while (left < right) {
            if (!isalpha(s[left])) {
                left++;
            } else if (!isalpha(s[right])) {
                right--;
            } else {
                swap(s[left], s[right]);
                left++;
                right--;
            }
        }

        return s;           
    }
};
