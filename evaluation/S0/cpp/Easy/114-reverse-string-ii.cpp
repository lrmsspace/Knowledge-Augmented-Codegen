// Source: https://leetcode.com/problems/reverse-string-ii/   |   Difficulty: Easy
//
// Problem Description:
// Given a string s and an integer k, reverse the first k characters for every 2k characters counting from the start of the string.
//
// If there are fewer than k characters left, reverse all of them. If there are less than 2k but greater than or equal to k characters, then reverse the first k characters and leave the other as original.
//
// Example:
// Input: s = "abcdefg", k = 2
// Output: "bacdfeg"
//
// Constraints:
// 1 <= s.length <= 104
// 	s consists of only lowercase English letters.
// 	1 <= k <= 104
//

class Solution {
public:
    string reverseStr(string s, int k) {
        int n = s.length();
        for (int i = 0; i < n; i += 2 * k) {
            int left = i;
            int right = min(i + k - 1, n - 1);
            while (left < right) {
                swap(s[left], s[right]);
                left++;
                right--;
            }
        }
        return s;           
    }
};
