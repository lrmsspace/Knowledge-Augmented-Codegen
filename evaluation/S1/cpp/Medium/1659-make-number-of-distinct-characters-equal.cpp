// Source: https://leetcode.com/problems/make-number-of-distinct-characters-equal/   |   Difficulty: Medium
//
// Problem Description:
// You are given two 0-indexed strings word1 and word2.
//
// A move consists of choosing two indices i and j such that 0 <= i < word1.length and 0 <= j < word2.length and swapping word1[i] with word2[j].
//
// Return true if it is possible to get the number of distinct characters in word1 and word2 to be equal with exactly one move. Return false otherwise.
//
// Example:
// Input: word1 = "ac", word2 = "b"
// Output: false
// Explanation: Any pair of swaps would yield two distinct characters in the first string, and one in the second string.
//
// Constraints:
// 1 <= word1.length, word2.length <= 105
// 	word1 and word2 consist of only lowercase English letters.
//
// Helpful references (internal KB):
// - The Inclusion-Exclusion Principle (string, counting)
//   • When to use: Use when you need to determine the frequency of characters or substrings within a string. It is essential for tasks like anagram detection or checking character distribution.
//   • Idea: This technique involves iterating through a string to tally the occurrences of its constituent elements, typically characters or words. It generally operates in O(N) time complexity, where N is the string's length.
//   • Invariants: The count for each character reflects its total occurrences processed so far.; All characters encountered up to the current position have been tallied.
//   • Tips: Use a hash map (dictionary) for arbitrary character sets.; Use an array for fixed-size character sets (e.g., ASCII, lowercase English).
//   • Pitfalls: Forgetting to handle case sensitivity or ignore non-alphanumeric characters.; Incorrectly handling Unicode characters with fixed-size arrays.
// - Elementary Sorts (array, enumeration)
//   • When to use: Selection sort is simple but inefficient. It's suitable for very small datasets or educational purposes where simplicity of implementation is prioritized over performance.
//   • Idea: Selection sort repeatedly finds the minimum element from the unsorted portion of the array and places it at the beginning of the sorted portion. It has a time complexity of O(N^2) and a space complexity of O(1).
//   • Invariants: The elements in the prefix of the array are sorted.; All elements in the sorted prefix are less than or equal to all elements in the unsorted suffix.
//   • Tips: Easy to understand and implement.; Performs a minimal number of swaps (exactly N-1 swaps).
//   • Pitfalls: Inefficient for large datasets due to O(N^2) time complexity.; Performance is not affected by the initial order of elements.
// - palindrome-partitioning (string, two-pointers, simulation)
//   • When to use: When a string needs to be decomposed into all possible sets of palindromic substrings. It's suitable for problems requiring exhaustive enumeration of such partitions.
//   • Idea: This algorithm finds all possible ways to partition a given string such that every substring in the partition is a palindrome. It typically uses a recursive exploration approach combined with a two-pointer check for palindrome validation, resulting in an exponential time complexity.
//   • Invariants: At any point, the `step` list contains a valid palindromic partition of the prefix processed so far.; The `s` parameter in the recursive function always represents the unpartitioned suffix of the original string.
//   • Tips: Implement the `isPalindrome` check efficiently using two pointers for O(length) time.; Use a recursive helper function to explore all possible partition points.
//   • Pitfalls: Incorrectly handling substring boundaries, leading to off-by-one errors or incorrect partitions.; Forgetting to backtrack (remove the last added substring) after a recursive call returns.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use standard C++ only; do NOT rely on non-standard extensions or platform-specific APIs.
// - Do not change input/output formats or return value semantics.
// - Conformance: Prefer modern standard C++ (C++11/14/17) features that are portable; avoid compiler-specific extensions (e.g., __int128 unless necessary and supported).
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
public:
    bool isItPossible(string word1, string word2) {
        int count1[26] = {0};
        int count2[26] = {0};
        for (char c : word1) {
            count1[c - 'a']++;
        }
        for (char c : word2) {
            count2[c - 'a']++;
        }

        int distinct1 = 0;
        int distinct2 = 0;
        for (int i = 0; i < 26; ++i) {
            if (count1[i] > 0) distinct1++;
            if (count2[i] > 0) distinct2++;
        }

        for (int i = 0; i < 26; ++i) {
            if (count1[i] == 0) continue;
            for (int j = 0; j < 26; ++j) {
                if (count2[j] == 0) continue;

                int newDistinct1 = distinct1;
                int newDistinct2 = distinct2;

                // Simulate the swap
                if (i == j) {
                    // Swapping same character, distinct counts remain the same
                } else {
                    // Character from word1 is removed
                    count1[i]--;
                    if (count1[i] == 0) newDistinct1--;

                    // Character from word2 is removed
                    count2[j]--;
                    if (count2[j] == 0) newDistinct2--;

                    // Character from word2 is added to word1
                    count1[j]++;
                    if (count1[j] == 1) newDistinct1++;

                    // Character from word1 is added to word2
                    count2[i]++;
                    if (count2[i] == 1) newDistinct2++;
                }

                if (newDistinct1 == newDistinct2) {
                    return true;
                }

                // Revert the changes for next iteration
                if (i != j) {
                    count1[j]--;
                    if (count1[j] == 0) newDistinct1--;

                    count2[i]--;
                    if (count2[i] == 0) newDistinct2--;

                    count1[i]++;
                    if (count1[i] == 1) newDistinct1++;

                    count2[j]++;
                    if (count2[j] == 1) newDistinct2++;
                }
            }
        }

        return false;           
    }
};
