// Source: https://leetcode.com/problems/the-k-th-lexicographical-string-of-all-happy-strings-of-length-n/   |   Difficulty: Medium
//
// Problem Description:
// A happy string is a string that:
//
//
// 	consists only of letters of the set ['a', 'b', 'c'].
// 	s[i] != s[i + 1] for all values of i from 1 to s.length - 1 (string is 1-indexed).
//
//
// For example, strings "abc", "ac", "b" and "abcbabcbcb" are all happy strings and strings "aa", "baa" and "ababbc" are not happy strings.
//
// Given two integers n and k, consider a list of all happy strings of length n sorted in lexicographical order.
//
// Return the kth string of this list or return an empty string if there are less than k happy strings of length n.
//
// Example:
// Input: n = 1, k = 3
// Output: "c"
// Explanation: The list ["a", "b", "c"] contains all happy strings of length 1. The third string is "c".
//
// Constraints:
// 1 <= n <= 10
// 	1 <= k <= 100
//

class Solution {
public:
    string getHappyString(int n, int k) {
        int total = 3 * (1 << (n - 1)); // Total happy strings of length n
        if (k > total) return "";

        string result;
        k--; // Convert to 0-based index

        // Determine the first character
        int firstCharIndex = k / (1 << (n - 1));
        result += 'a' + firstCharIndex;
        k %= (1 << (n - 1));

        // Determine the remaining characters
        for (int i = 1; i < n; ++i) {
            int half = 1 << (n - 1 - i);
            int nextCharIndex = k / half;
            k %= half;

            // Get the last character added to result
            char lastChar = result.back();
            char nextChar;

            // Choose the next character based on last character and nextCharIndex
            if (lastChar == 'a') {
                nextChar = (nextCharIndex == 0) ? 'b' : 'c';
            } else if (lastChar == 'b') {
                nextChar = (nextCharIndex == 0) ? 'a' : 'c';
            } else { // lastChar == 'c'
                nextChar = (nextCharIndex == 0) ? 'a' : 'b';
            }

            result += nextChar;
        }

        return result;          
    }
};
