// Source: https://leetcode.com/problems/remove-letter-to-equalize-frequency/   |   Difficulty: Easy
//
// Problem Description:
// You are given a 0-indexed string word, consisting of lowercase English letters. You need to select one index and remove the letter at that index from word so that the frequency of every letter present in word is equal.
//
// Return true if it is possible to remove one letter so that the frequency of all letters in word are equal, and false otherwise.
//
// Note:
//
//
// 	The frequency of a letter x is the number of times it occurs in the string.
// 	You must remove exactly one letter and cannot choose to do nothing.
//
// Example:
// Input: word = "abcc"
// Output: true
// Explanation: Select index 3 and delete it: word becomes "abc" and each character has a frequency of 1.
//
// Constraints:
// 2 <= word.length <= 100
// 	word consists of lowercase English letters only.
//
// Helpful references (internal KB):
// - The Inclusion-Exclusion Principle (string, counting)
//   • When to use: Use when you need to determine the frequency of characters or substrings within a string. It is essential for tasks like anagram detection or checking character distribution.
//   • Idea: This technique involves iterating through a string to tally the occurrences of its constituent elements, typically characters or words. It generally operates in O(N) time complexity, where N is the string's length.
//   • Invariants: The count for each character reflects its total occurrences processed so far.; All characters encountered up to the current position have been tallied.
//   • Tips: Use a hash map (dictionary) for arbitrary character sets.; Use an array for fixed-size character sets (e.g., ASCII, lowercase English).
//   • Pitfalls: Forgetting to handle case sensitivity or ignore non-alphanumeric characters.; Incorrectly handling Unicode characters with fixed-size arrays.
// - Non-negative Integers without Consecutive Ones (number, enumeration, simulation)
//   • When to use: Use when counting numbers up to a given limit that satisfy a specific bit pattern constraint, particularly when the limit is small enough for direct iteration and checking.
//   • Idea: This approach iterates through every non-negative integer from 0 up to the given limit num. For each integer, it simulates checking its binary representation to determine if it contains any two consecutive '1's.
//   • Invariants: count stores the number of integers k (where 0 <= k < i) that do not have consecutive ones.; All integers j such that 0 <= j < i have been processed.
//   • Tips: Use bitwise operations like (i & (i >> 1)) to efficiently detect consecutive ones.; Remember to include 0 in the count as it satisfies the condition (no consecutive ones).
//   • Pitfalls: Performance degradation for large num due to linear scan and per-number bit check.; Incorrectly handling the upper bound of the iteration (e.g., i < num instead of i <= num).
// - Suffix Array (string, array, counting-sort, radix-sort)
//   • When to use: Use when you need to efficiently query or analyze all suffixes of a string, often for pattern matching, string searching, or finding repeated substrings. It provides a sorted order of all suffixes.
//   • Idea: The Suffix Array algorithm constructs an array containing the starting indices of all suffixes of a string, sorted lexicographically. It typically uses a doubling strategy with counting sort or radix sort in each step, achieving an O(N log N) time complexity.
//   • Invariants: After iteration k, p contains the sorted indices of all cyclic substrings of length 2^k.; After iteration k, c[i] represents the equivalence class of the cyclic substring starting at i with length 2^k.
//   • Tips: Append a unique, smallest character (e.g., '$') to the string to handle suffixes as cyclic shifts.; Utilize counting sort for efficient sorting of characters and pairs of equivalence classes.
//   • Pitfalls: Incorrectly handling the sentinel character can lead to incorrect suffix order or out-of-bounds access.; Off-by-one errors when calculating indices for cyclic shifts or substring lengths.
//
// Notes:
// - Keep the given method signatures unchanged.
// - Use only Java standard library (`java.*`); no external dependencies.
// - Do not change input/output formats or return value semantics.
// - Conformance: single public class 'Solution'; no 'package' statement; place any extra types as static inner classes.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
    private boolean areFrequenciesEqual(int[] freq) {
        Integer targetFreq = null;
        for (int f : freq) {
            if (f > 0) {
                if (targetFreq == null) {
                    targetFreq = f;
                } else if (f != targetFreq) {
                    return false;
                }
            }
        }
        return true;
    }
    public boolean equalFrequency(String word) {
        int[] freq = new int[26];
        for (char c : word.toCharArray()) {
            freq[c - 'a']++;
        }

        for (int i = 0; i < word.length(); i++) {
            char c = word.charAt(i);
            freq[c - 'a']--;

            if (areFrequenciesEqual(freq)) {
                return true;
            }

            freq[c - 'a']++;
        }

        return false;           
    }
}
