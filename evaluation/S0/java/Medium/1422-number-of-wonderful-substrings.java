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

    public long wonderfulSubstrings(String word) {

        
        long result = 0;
        int[] count = new int[1024];
        int mask = 0;
        count[0] = 1;

        for (char c : word.toCharArray()) {
            mask ^= 1 << (c - 'a');
            result += count[mask];

            for (int i = 0; i < 10; i++) {
                result += count[mask ^ (1 << i)];
            }

            count[mask]++;
        }

        return result;
    }

}
