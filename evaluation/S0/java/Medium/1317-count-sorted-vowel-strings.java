// Source: https://leetcode.com/problems/count-sorted-vowel-strings/   |   Difficulty: Medium
//
// Problem Description:
// Given an integer n, return the number of strings of length n that consist only of vowels (a, e, i, o, u) and are lexicographically sorted.
//
// A string s is lexicographically sorted if for all valid i, s[i] is the same as or comes before s[i+1] in the alphabet.
//
// Example:
// Input: n = 1
// Output: 5
// Explanation: The 5 sorted strings that consist of vowels only are ["a","e","i","o","u"].
//
// Constraints:
// 1 <= n <= 50
//

class Solution {
    public int countVowelStrings(int n) {
        // Using combinatorial mathematics:
        // The number of ways to choose n vowels from 5 types (a, e, i, o, u) with repetition allowed
        // and order not mattering is given by the formula: C(n + k - 1, k - 1)
        // where k is the number of vowel types (5 in this case).
        int k = 5;
        return combination(n + k - 1, k - 1);           
    }
}
