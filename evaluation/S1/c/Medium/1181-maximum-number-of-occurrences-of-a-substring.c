// Source: https://leetcode.com/problems/maximum-number-of-occurrences-of-a-substring/   |   Difficulty: Medium
//
// Problem Description:
// Given a string s, return the maximum number of occurrences of any substring under the following rules:
//
//
// 	The number of unique characters in the substring must be less than or equal to maxLetters.
// 	The substring size must be between minSize and maxSize inclusive.
//
// Example:
// Input: s = "aababcaab", maxLetters = 2, minSize = 3, maxSize = 4
// Output: 2
// Explanation: Substring "aab" has 2 occurrences in the original string.
// It satisfies the conditions, 2 unique letters and size 3 (between minSize and maxSize).
//
// Constraints:
// 1 <= s.length <= 105
// 	1 <= maxLetters <= 26
// 	1 <= minSize <= maxSize <= min(26, s.length)
// 	s consists of only lowercase English letters.
//
// Helpful references (internal KB):
// - Search the subarray with the maximum/minimum sum (array, greedy, dp-1d)
//   • When to use: When you need to find the contiguous subarray within a one-dimensional array of numbers that has the largest or smallest sum, typically in linear time.
//   • Idea: This algorithm efficiently finds the maximum (or minimum) sum of a contiguous subarray by iterating through the array and maintaining a current sum, resetting it if it becomes detrimental. It operates in O(N) time complexity with O(1) space complexity.
//   • Invariants: `global_max` holds the maximum sum of any contiguous subarray encountered up to the current element.; `current_max` holds the maximum sum of a contiguous subarray ending at the current element.
//   • Tips: Initialize current and global maximums appropriately (e.g., to negative infinity or first element).; Adapt for minimum sum by resetting current sum if it becomes positive.
//   • Pitfalls: Failing to correctly initialize maximum/minimum sum variables.; Not handling arrays where all elements are negative (for max sum) or positive (for min sum).
// - String Hashing (string, array, hashing)
//   • When to use: Use when you need to efficiently compare strings or substrings, detect duplicates, or perform pattern matching in large text datasets. It's particularly useful for speeding up operations that would otherwise be O(N*M) or O(N^2).
//   • Idea: String hashing maps strings to numerical values, allowing for fast comparisons and operations like substring search. It typically uses a polynomial rolling hash function, achieving O(N) preprocessing and O(1) or O(log N) query time for substrings.
//   • Invariants: The hash of any prefix of the string is correctly computed based on its characters and chosen parameters.; For a rolling hash, the hash of the current window is always maintained correctly as the window slides.
//   • Tips: Choose a large prime modulus (or two) to minimize collision probability.; Select a base (prime number) larger than the alphabet size to ensure unique contributions from characters.
//   • Pitfalls: Hash collisions are possible and can lead to incorrect results if not properly handled or verified.; A poorly chosen base or modulus can significantly increase the frequency of collisions.
// - The Inclusion-Exclusion Principle (string, counting)
//   • When to use: Use when you need to determine the frequency of characters or substrings within a string. It is essential for tasks like anagram detection or checking character distribution.
//   • Idea: This technique involves iterating through a string to tally the occurrences of its constituent elements, typically characters or words. It generally operates in O(N) time complexity, where N is the string's length.
//   • Invariants: The count for each character reflects its total occurrences processed so far.; All characters encountered up to the current position have been tallied.
//   • Tips: Use a hash map (dictionary) for arbitrary character sets.; Use an array for fixed-size character sets (e.g., ASCII, lowercase English).
//   • Pitfalls: Forgetting to handle case sensitivity or ignore non-alphanumeric characters.; Incorrectly handling Unicode characters with fixed-size arrays.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use the C standard library only; no external packages.
// - Do not change input/output formats or return value semantics.
// - Conformance: ISO C (C89/C99/C11). Do NOT use GNU C extensions (nested functions, statement expressions, typeof, __auto_type, etc.). Avoid VLAs and non-standard builtins.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

int maxFreq(char* s, int maxLetters, int minSize, int maxSize) {
    int len = 0;
    while (s[len] != '\0') {
        len++;
    }

    int maxCount = 0;
    int substringCounts[100000] = {0};
    int base = 31;
    unsigned long long mod = 1000000007;
    unsigned long long hash = 0;
    unsigned long long power = 1;

    int charCount[26] = {0};
    int uniqueChars = 0;

    for (int i = 0; i < minSize; i++) {
        hash = (hash * base + (s[i] - 'a' + 1)) % mod;
        charCount[s[i] - 'a']++;
        if (charCount[s[i] - 'a'] == 1) {
            uniqueChars++;
        }
        if (i < minSize - 1) {
            power = (power * base) % mod;
        }
    }

    if (uniqueChars <= maxLetters) {
        substringCounts[hash]++;
        if (substringCounts[hash] > maxCount) {
            maxCount = substringCounts[hash];
        }
    }

    for (int i = minSize; i < len; i++) {
        hash = (hash + mod - (power * (s[i - minSize] - 'a' + 1)) % mod) % mod;
        hash = (hash * base + (s[i] - 'a' + 1)) % mod;

        charCount[s[i - minSize] - 'a']--;
        if (charCount[s[i - minSize] - 'a'] == 0) {
            uniqueChars--;
        }
        charCount[s[i] - 'a']++;
        if (charCount[s[i] - 'a'] == 1) {
            uniqueChars++;
        }

        if (uniqueChars <= maxLetters) {
            substringCounts[hash]++;
            if (substringCounts[hash] > maxCount) {
                maxCount = substringCounts[hash];
            }
        }
    }

    return maxCount;        
}
