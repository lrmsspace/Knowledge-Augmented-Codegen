// Source: https://leetcode.com/problems/minimum-length-of-string-after-deleting-similar-ends/   |   Difficulty: Medium
//
// Problem Description:
// Given a string s consisting only of characters 'a', 'b', and 'c'. You are asked to apply the following algorithm on the string any number of times:
//
//
// 	Pick a non-empty prefix from the string s where all the characters in the prefix are equal.
// 	Pick a non-empty suffix from the string s where all the characters in this suffix are equal.
// 	The prefix and the suffix should not intersect at any index.
// 	The characters from the prefix and suffix must be the same.
// 	Delete both the prefix and the suffix.
//
//
// Return the minimum length of s after performing the above operation any number of times (possibly zero times).
//
// Example:
// Input: s = "ca"
// Output: 2
// Explanation: You can't remove any characters, so the string stays as is.
//
// Constraints:
// 1 <= s.length <= 105
// 	s only consists of characters 'a', 'b', and 'c'.
//

class Solution {
public:
    int minimumLength(string s) {
        int left = 0;
        int right = s.size() - 1;

        while (left < right && s[left] == s[right]) {
            char currentChar = s[left];
            while (left <= right && s[left] == currentChar) {
                left++;
            }
            while (left <= right && s[right] == currentChar) {
                right--;
            }
        }

        return right - left + 1;            
    }
};
