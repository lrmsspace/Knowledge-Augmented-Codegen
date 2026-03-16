// Source: https://leetcode.com/problems/generate-binary-strings-without-adjacent-zeros/   |   Difficulty: Medium
//
// Problem Description:
// You are given a positive integer n.
//
// A binary string x is valid if all substrings of x of length 2 contain at least one "1".
//
// Return all valid strings with length n, in any order.
//
// Example:
// Input: n = 3
//
// Output: ["010","011","101","110","111"]
//
// Explanation:
//
// The valid strings of length 3 are: "010", "011", "101", "110", and "111".
//
// Constraints:
// 1 <= n <= 18
//

class Solution {
public:
    vector<string> validStrings(int n) {
        vector<string> result;
        string current;
        backtrack(n, current, result);
        return result;          
    }
};
