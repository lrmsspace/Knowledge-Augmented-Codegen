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

long long wonderfulSubstrings(char * word){


    int count[1024] = {0};
    int mask = 0;
    long long result = 0;

    count[0] = 1;  // Empty prefix

    for (int i = 0; word[i] != '\0'; i++) {
        // Update the mask for the current character
        mask ^= (1 << (word[i] - 'a'));

        // Count substrings with even counts of all characters
        result += count[mask];

        // Count substrings with exactly one character having an odd count
        for (int j = 0; j < 10; j++) {
            result += count[mask ^ (1 << j)];
        }

        // Record the current mask
        count[mask]++;
    }

    return result;
}
