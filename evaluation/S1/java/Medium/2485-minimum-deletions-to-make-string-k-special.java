// Source: https://leetcode.com/problems/minimum-deletions-to-make-string-k-special/   |   Difficulty: Medium
//
// Problem Description:
// You are given a string word and an integer k.
//
// We consider word to be k-special if |freq(word[i]) - freq(word[j])| <= k for all indices i and j in the string.
//
// Here, freq(x) denotes the frequency of the character x in word, and |y| denotes the absolute value of y.
//
// Return the minimum number of characters you need to delete to make word k-special.
//
// Example:
// Input: word = "aabcaba", k = 0
//
// Output: 3
//
// Explanation: We can make word 0-special by deleting 2 occurrences of "a" and 1 occurrence of "c". Therefore, word becomes equal to "baba" where freq('a') == freq('b') == 2.
//
// Constraints:
// 1 <= word.length <= 105
// 	0 <= k <= 105
// 	word consists only of lowercase English letters.
//
// Helpful references (internal KB):
// - The Inclusion-Exclusion Principle (string, counting)
//   • When to use: Use when you need to determine the frequency of characters or substrings within a string. It is essential for tasks like anagram detection or checking character distribution.
//   • Idea: This technique involves iterating through a string to tally the occurrences of its constituent elements, typically characters or words. It generally operates in O(N) time complexity, where N is the string's length.
//   • Invariants: The count for each character reflects its total occurrences processed so far.; All characters encountered up to the current position have been tallied.
//   • Tips: Use a hash map (dictionary) for arbitrary character sets.; Use an array for fixed-size character sets (e.g., ASCII, lowercase English).
//   • Pitfalls: Forgetting to handle case sensitivity or ignore non-alphanumeric characters.; Incorrectly handling Unicode characters with fixed-size arrays.
// - Generating all K-combinations (array, enumeration, greedy)
//   • When to use: Use this when you need to iterate through all possible subsets of a fixed size K from a larger set, especially when a specific order like lexicographical is required.
//   • Idea: This algorithm systematically generates all unique combinations of K elements from a set of N elements. It typically proceeds in lexicographical order, allowing for efficient enumeration of all C(N, K) possibilities.
//   • Invariants: The current combination C is always sorted: C[0] < C[1] < ... < C[K-1].; All elements C[i] are distinct and within the range [0, N-1] (assuming 0-indexed).
//   • Tips: Start with the smallest lexicographical combination (e.g., {1, 2, ..., K}).; To find the next combination, locate the rightmost element that can be incremented.
//   • Pitfalls: Incorrectly handling boundary conditions when incrementing elements.; Duplicating combinations if not careful with the increment logic.
// - Minimum stack / Minimum queue (queue, stack, simulation)
//   • When to use: Use when needing to efficiently query the minimum element of a stack or queue in O(1) average time. Also applicable for finding minimums in all fixed-length subarrays using a sliding window.
//   • Idea: This technique augments a stack or queue to support O(1) average time retrieval of its minimum element, typically by storing minimums alongside data or using auxiliary structures. It achieves amortized constant time for all operations.
//   • Invariants: For a minimum stack, the auxiliary minimum stack's top element is always the minimum of all elements currently in the main stack.; For a minimum queue implemented with two stacks, the output stack is only refilled from the input stack when the output stack becomes empty.
//   • Tips: For a minimum stack, use an auxiliary stack to store minimums encountered so far.; Only push to the auxiliary minimum stack if the new element is less than or equal to its current top.
//   • Pitfalls: Forgetting to pop from the auxiliary minimum stack when the main stack's top is removed.; Incorrectly handling the transfer logic between the two stacks for a minimum queue.
//
// Notes:
// - Keep the given method signatures unchanged.
// - Use only Java standard library (`java.*`); no external dependencies.
// - Do not change input/output formats or return value semantics.
// - Conformance: single public class 'Solution'; no 'package' statement; place any extra types as static inner classes.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
    public int minimumDeletions(String word, int k) {
        int[] freq = new int[26];
        for (char c : word.toCharArray()) {
            freq[c - 'a']++;
        }

        int maxFreq = 0;
        for (int f : freq) {
            maxFreq = Math.max(maxFreq, f);
        }

        int minDeletions = Integer.MAX_VALUE;
        for (int targetFreq = 1; targetFreq <= maxFreq; targetFreq++) {
            int deletions = 0;
            for (int f : freq) {
                if (f == 0) continue;
                if (Math.abs(f - targetFreq) > k) {
                    if (f > targetFreq) {
                        deletions += f - (targetFreq + k);
                    } else {
                        deletions += f;
                    }
                }
            }
            minDeletions = Math.min(minDeletions, deletions);
        }

        return minDeletions == Integer.MAX_VALUE ? 0 : minDeletions;            
    }
}
