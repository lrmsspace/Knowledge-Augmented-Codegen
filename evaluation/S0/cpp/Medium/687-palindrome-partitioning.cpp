// Source: https://leetcode.com/problems/palindrome-partitioning/   |   Difficulty: Medium
//
// Problem Description:
// Given a string s, partition s such that every substring of the partition is a palindrome. Return all possible palindrome partitioning of s.
//
// Example:
// Input: s = "aab"
// Output: [["a","a","b"],["aa","b"]]
//
// Constraints:
// 1 <= s.length <= 16
// 	s contains only lowercase English letters.
//

class Solution {
public:
    vector<vector<string>> partition(string s) {
        vector<vector<string>> result;
        vector<string> current;
        backtrack(s, 0, current, result);
        return result;          
    }
};
