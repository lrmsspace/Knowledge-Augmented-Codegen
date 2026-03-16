// Source: https://leetcode.com/problems/maximize-the-number-of-partitions-after-operations/   |   Difficulty: Hard
//
// Problem Description:
// You are given a string s and an integer k.
//
// First, you are allowed to change at most one index in s to another lowercase English letter.
//
// After that, do the following partitioning operation until s is empty:
//
//
// 	Choose the longest prefix of s containing at most k distinct characters.
// 	Delete the prefix from s and increase the number of partitions by one. The remaining characters (if any) in s maintain their initial order.
//
//
// Return an integer denoting the maximum number of resulting partitions after the operations by optimally choosing at most one index to change.
//
// Example:
// Input: s = "accca", k = 2
//
// Output: 3
//
// Explanation:
//
// The optimal way is to change s[2] to something other than a and c, for example, b. then it becomes "acbca".
//
// Then we perform the operations:
//
//
// 	The longest prefix containing at most 2 distinct characters is "ac", we remove it and s becomes "bca".
// 	Now The longest prefix containing at most 2 distinct characters is "bc", so we remove it and s becomes "a".
// 	Finally, we remove "a" and s becomes empty, so the procedure ends.
//
//
// Doing the operations, the string is divided into 3 partitions, so the answer is 3.
//
// Constraints:
// 1 <= s.length <= 104
// 	s consists only of lowercase English letters.
// 	1 <= k <= 26
//
// Helpful references (internal KB):
// - The Inclusion-Exclusion Principle (string, counting)
//   • When to use: Use when you need to determine the frequency of characters or substrings within a string. It is essential for tasks like anagram detection or checking character distribution.
//   • Idea: This technique involves iterating through a string to tally the occurrences of its constituent elements, typically characters or words. It generally operates in O(N) time complexity, where N is the string's length.
//   • Invariants: The count for each character reflects its total occurrences processed so far.; All characters encountered up to the current position have been tallied.
//   • Tips: Use a hash map (dictionary) for arbitrary character sets.; Use an array for fixed-size character sets (e.g., ASCII, lowercase English).
//   • Pitfalls: Forgetting to handle case sensitivity or ignore non-alphanumeric characters.; Incorrectly handling Unicode characters with fixed-size arrays.
// - palindrome-partitioning (string, two-pointers, simulation)
//   • When to use: When a string needs to be decomposed into all possible sets of palindromic substrings. It's suitable for problems requiring exhaustive enumeration of such partitions.
//   • Idea: This algorithm finds all possible ways to partition a given string such that every substring in the partition is a palindrome. It typically uses a recursive exploration approach combined with a two-pointer check for palindrome validation, resulting in an exponential time complexity.
//   • Invariants: At any point, the `step` list contains a valid palindromic partition of the prefix processed so far.; The `s` parameter in the recursive function always represents the unpartitioned suffix of the original string.
//   • Tips: Implement the `isPalindrome` check efficiently using two pointers for O(length) time.; Use a recursive helper function to explore all possible partition points.
//   • Pitfalls: Incorrectly handling substring boundaries, leading to off-by-one errors or incorrect partitions.; Forgetting to backtrack (remove the last added substring) after a recursive call returns.
// - kth-largest-element-in-an-array (array, quickselect, randomized)
//   • When to use: Use when you need to efficiently find the k-th smallest or largest element in an unsorted array without fully sorting it, especially when average-case linear time complexity is acceptable and in-place modification is desired.
//   • Idea: QuickSelect is a divide-and-conquer algorithm that partitions an array around a pivot and recursively searches for the k-th element in the relevant partition. It offers an average-case O(N) time complexity and O(1) space.
//   • Invariants: The pivot element is always placed at its correct sorted position within the current sub-array.; All elements to the left of the pivot are less than or equal to it, and all elements to its right are greater than or equal to it.
//   • Tips: Randomly select pivots to ensure average-case O(N) performance and avoid worst-case scenarios.; Adjust the target index k based on whether you're seeking the k-th smallest or k-th largest element.
//   • Pitfalls: Poor pivot selection can lead to a worst-case O(N^2) time complexity, though rare with randomization.; Off-by-one errors are common when mapping k-th largest/smallest to 0-indexed array positions.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use the C standard library only; no external packages.
// - Do not change input/output formats or return value semantics.
// - Conformance: ISO C (C89/C99/C11). Do NOT use GNU C extensions (nested functions, statement expressions, typeof, __auto_type, etc.). Avoid VLAs and non-standard builtins.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

int maxPartitionsAfterOperations(char* s, int k) {
    int freq[26] = {0};
    int distinctCount = 0;
    int partitions = 0;
    int left = 0;

    // Count the frequency of each character in the string
    for (int i = 0; s[i] != '\0'; i++) {
        int idx = s[i] - 'a';
        if (freq[idx] == 0) {
            distinctCount++;
        }
        freq[idx]++;
    }

    // If the number of distinct characters is already less than or equal to k, we can partition the string as is
    if (distinctCount <= k) {
        return 1; // The entire string can be one partition
    }

    // Try changing each character and see how it affects the partitions
    for (int i = 0; s[i] != '\0'; i++) {
        int originalIdx = s[i] - 'a';

        // Temporarily change the character at index i to a different character
        for (int c = 0; c < 26; c++) {
            if (c == originalIdx) continue; // Skip the original character

            // Decrease frequency of the original character
            freq[originalIdx]--;
            if (freq[originalIdx] == 0) {
                distinctCount--;
            }

            // Increase frequency of the new character
            freq[c]++;
            if (freq[c] == 1) {
                distinctCount++;
            }

            // Check how many partitions we can create with this change
            int currentPartitions = 0;
            int currentDistinctCount = distinctCount;

            for (int j = 0; s[j] != '\0'; j++) {
                int idx = s[j] - 'a';
                if (freq[idx] > 0) {
                    currentDistinctCount++;
                }
                if (currentDistinctCount > k) {
                    currentPartitions++;
                    currentDistinctCount = 1; // Reset for the next partition
                }
            }
            currentPartitions++; // Account for the last partition

            // Update maximum partitions
            if (currentPartitions > partitions) {
                partitions = currentPartitions;
            }

            // Revert the changes to frequencies and distinct count
            freq[c]--;
            if (freq[c] == 0) {
                distinctCount--;
            }
            freq[originalIdx]++;
            if (freq[originalIdx] == 1) {
                distinctCount++;
            }
        }
        
    }
    return partitions;
}
