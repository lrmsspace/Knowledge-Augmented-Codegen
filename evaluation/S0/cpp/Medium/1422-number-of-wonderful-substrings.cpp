// Source: https://leetcode.com/problems/number-of-wonderful-substrings/   |   Difficulty: Medium
//
// Problem Description:
// A wonderful string is a string where at most one letter appears an odd number of times.
//
//
// 	For example, "ccjjc" and "abab" are wonderful, but "ab" is not.
//
//
// Given a string word that consists of the first ten lowercase English letters ('a' through 'j'), return the number of wonderful non-empty substrings in word. If the same substring appears multiple times in word, then count each occurrence separately.
//
// A substring is a contiguous sequence of characters in a string.
//
// Example:
// Input: word = "aba"
// Output: 4
// Explanation: The four wonderful substrings are underlined below:
// - "aba" -> "a"
// - "aba" -> "b"
// - "aba" -> "a"
// - "aba" -> "aba"
//
// Constraints:
// 1 <= word.length <= 105
// 	word consists of lowercase English letters from 'a' to 'j'.
//

class Solution {

public:

    long long wonderfulSubstrings(string word) {

        
        long long result = 0;
        unordered_map<int, long long> countMap;
        countMap[0] = 1; // Initial state with all even counts

        int currentState = 0;

        for (char c : word) {
            int charBit = 1 << (c - 'a');
            currentState ^= charBit; // Toggle the bit for the current character

            // Count substrings with all even counts
            result += countMap[currentState];

            // Count substrings with exactly one odd count
            for (int i = 0; i < 10; ++i) {
                int toggledState = currentState ^ (1 << i);
                result += countMap[toggledState];
            }

            // Update the count of the current state
            countMap[currentState]++;
        }

        return result;
    }

};
