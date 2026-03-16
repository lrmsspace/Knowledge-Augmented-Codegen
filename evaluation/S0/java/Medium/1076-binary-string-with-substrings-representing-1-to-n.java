// Source: https://leetcode.com/problems/binary-string-with-substrings-representing-1-to-n/   |   Difficulty: Medium
//
// Problem Description:
// Given a binary string s and a positive integer n, return true if the binary representation of all the integers in the range [1, n] are substrings of s, or false otherwise.
//
// A substring is a contiguous sequence of characters within a string.
//
// Example:
// Input: s = "0110", n = 3
// Output: true
//
// Constraints:
// 1 <= s.length <= 1000
// 	s[i] is either '0' or '1'.
// 	1 <= n <= 109
//

class Solution {
    public boolean queryString(String s, int n) {
        for (int i = 1; i <= n; i++) {
            String binary = Integer.toBinaryString(i);
            if (!s.contains(binary)) {
                return false;
            }
        }
        return true;            
    }
}
