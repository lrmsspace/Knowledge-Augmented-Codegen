// Source: https://leetcode.com/problems/change-minimum-characters-to-satisfy-one-of-three-conditions/   |   Difficulty: Medium
//
// Problem Description:
// You are given two strings a and b that consist of lowercase letters. In one operation, you can change any character in a or b to any lowercase letter.
//
// Your goal is to satisfy one of the following three conditions:
//
//
// 	Every letter in a is strictly less than every letter in b in the alphabet.
// 	Every letter in b is strictly less than every letter in a in the alphabet.
// 	Both a and b consist of only one distinct letter.
//
//
// Return the minimum number of operations needed to achieve your goal.
//
// Example:
// Input: a = "aba", b = "caa"
// Output: 2
// Explanation: Consider the best way to make each condition true:
// 1) Change b to "ccc" in 2 operations, then every letter in a is less than every letter in b.
// 2) Change a to "bbb" and b to "aaa" in 3 operations, then every letter in b is less than every letter in a.
// 3) Change a to "aaa" and b to "aaa" in 2 operations, then a and b consist of one distinct letter.
// The best way was done in 2 operations (either condition 1 or condition 3).
//
// Constraints:
// 1 <= a.length, b.length <= 105
// 	a and b consist only of lowercase letters.
//
// Helpful references (internal KB):
// - N/A
//
// Notes:
// - Keep the given function signature unchanged.
// - Use standard C++ only; do NOT rely on non-standard extensions or platform-specific APIs.
// - Do not change input/output formats or return value semantics.
// - Conformance: Prefer modern standard C++ (C++11/14/17) features that are portable; avoid compiler-specific extensions (e.g., __int128 unless necessary and supported).
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
public:
    int minCharacters(string a, string b) {
        vector<int> countA(26, 0), countB(26, 0);
        for (char c : a) countA[c - 'a']++;
        for (char c : b) countB[c - 'a']++;

        int totalA = a.size(), totalB = b.size();
        int minOps = INT_MAX;

        // Condition 1: Every letter in a is less than every letter in b
        for (int i = 0; i < 25; ++i) {
            int ops = (totalA - countA[i]) + (totalB - countB[i + 1]);
            minOps = min(minOps, ops);
        }

        // Condition 2: Every letter in b is less than every letter in a
        for (int i = 0; i < 25; ++i) {
            int ops = (totalB - countB[i]) + (totalA - countA[i + 1]);
            minOps = min(minOps, ops);
        }

        // Condition 3: Both a and b consist of only one distinct letter
        for (int i = 0; i < 26; ++i) {
            int ops = (totalA - countA[i]) + (totalB - countB[i]);
            minOps = min(minOps, ops);
        }

        return minOps;          
    }
};
