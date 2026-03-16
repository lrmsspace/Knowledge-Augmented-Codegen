// Source: https://leetcode.com/problems/minimum-deletions-to-make-string-balanced/   |   Difficulty: Medium
//
// Problem Description:
// You are given a string s consisting only of characters 'a' and 'b'​​​​.
//
// You can delete any number of characters in s to make s balanced. s is balanced if there is no pair of indices (i,j) such that i < j and s[i] = 'b' and s[j]= 'a'.
//
// Return the minimum number of deletions needed to make s balanced.
//
// Example:
// Input: s = "aababbab"
// Output: 2
// Explanation: You can either:
// Delete the characters at 0-indexed positions 2 and 6 ("aababbab" -> "aaabbb"), or
// Delete the characters at 0-indexed positions 3 and 6 ("aababbab" -> "aabbbb").
//
// Constraints:
// 1 <= s.length <= 105
// 	s[i] is 'a' or 'b'​​.
//

class Solution {
    public int minimumDeletions(String s) {
        int bCount = 0; // Count of 'b's encountered so far
        int deletions = 0; // Minimum deletions needed

        for (char c : s.toCharArray()) {
            if (c == 'a') {
                // If we encounter 'a', we have two choices:
                // 1. Delete this 'a' (increment deletions)
                // 2. Delete all previous 'b's (set deletions to bCount)
                deletions = Math.min(deletions + 1, bCount);
            } else {
                // If we encounter 'b', just increment the count of 'b's
                bCount++;
            }
        }

        return deletions;           
    }
}
