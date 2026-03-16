// Source: https://leetcode.com/problems/split-a-string-in-balanced-strings/   |   Difficulty: Easy
//
// Problem Description:
// Balanced strings are those that have an equal quantity of 'L' and 'R' characters.
//
// Given a balanced string s, split it into some number of substrings such that:
//
//
// 	Each substring is balanced.
//
//
// Return the maximum number of balanced strings you can obtain.
//
// Example:
// Input: s = "RLRRLLRLRL"
// Output: 4
// Explanation: s can be split into "RL", "RRLL", "RL", "RL", each substring contains same number of 'L' and 'R'.
//
// Constraints:
// 2 <= s.length <= 1000
// 	s[i] is either 'L' or 'R'.
// 	s is a balanced string.
//

class Solution {
    public int balancedStringSplit(String s) {
        int balance = 0;
        int count = 0;

        for (char c : s.toCharArray()) {
            if (c == 'L') {
                balance++;
            } else {
                balance--;
            }

            if (balance == 0) {
                count++;
            }
        }

        return count;           
    }
}
