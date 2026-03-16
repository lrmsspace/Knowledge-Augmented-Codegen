// Source: https://leetcode.com/problems/reverse-words-in-a-string-iii/   |   Difficulty: Easy
//
// Problem Description:
// Given a string s, reverse the order of characters in each word within a sentence while still preserving whitespace and initial word order.
//
// Example:
// Input: s = "Let's take LeetCode contest"
// Output: "s'teL ekat edoCteeL tsetnoc"
//
// Constraints:
// 1 <= s.length <= 5 * 104
// 	s contains printable ASCII characters.
// 	s does not contain any leading or trailing spaces.
// 	There is at least one word in s.
// 	All the words in s are separated by a single space.
//

class Solution {
public:
    string reverseWords(string s) {
        int n = s.size();
        int left = 0, right = 0;

        while (right < n) {
            // Move right pointer to the end of the current word
            while (right < n && s[right] != ' ') {
                right++;
            }

            // Reverse the current word
            reverse(s.begin() + left, s.begin() + right);

            // Move to the next word
            right++; // Skip the space
            left = right;
        }

        return s;           
    }
};
