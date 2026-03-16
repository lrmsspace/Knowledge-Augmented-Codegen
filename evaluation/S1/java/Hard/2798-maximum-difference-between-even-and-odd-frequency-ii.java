// Source: https://leetcode.com/problems/maximum-difference-between-even-and-odd-frequency-ii/   |   Difficulty: Hard
//
// Problem Description:
// You are given a string s and an integer k. Your task is to find the maximum difference between the frequency of two characters, freq[a] - freq[b], in a substring subs of s, such that:
//
//
// 	subs has a size of at least k.
// 	Character a has an odd frequency in subs.
// 	Character b has a non-zero even frequency in subs.
//
//
// Return the maximum difference.
//
// Note that subs can contain more than 2 distinct characters.
//
// Example:
// Input: s = "12233", k = 4
//
// Output: -1
//
// Explanation:
//
// For the substring "12233", the frequency of '1' is 1 and the frequency of '3' is 2. The difference is 1 - 2 = -1.
//
// Constraints:
// 3 <= s.length <= 3 * 104
// 	s consists only of digits '0' to '4'.
// 	The input is generated that at least one substring has a character with an even frequency and a character with an odd frequency.
// 	1 <= k <= s.length
//
// Helpful references (internal KB):
// - String Sorts (array, string, number, radix-sort, counting-sort)
//   • When to use: Use when sorting a large collection of fixed-length strings or integers, especially when the key range (alphabet size) is small. It is efficient for data with uniform key lengths.
//   • Idea: LSD Radix Sort sorts elements by processing digits or characters from the least significant to the most significant, using a stable counting sort for each position. It achieves a time complexity of O(W * (N + R)), where W is the key length, N is the number of items, and R is the radix.
//   • Invariants: After each pass 'd' (from 'w-1' down to '0'), the array 'a' is stably sorted based on characters from position 'd' to 'w-1'.; The 'count' array accurately reflects the frequency of each character at the current digit 'd' before cumulation.
//   • Tips: Utilize counting sort as the stable inner sorting algorithm for each digit pass.; Process characters or digits from right to left (least significant to most significant).
//   • Pitfalls: Inefficient for variable-length strings without proper padding or specialized handling.; Can be slower than comparison sorts for small input sizes or very large radix (R).
// - Search the subarray with the maximum/minimum sum (array, greedy, dp-1d)
//   • When to use: When you need to find the contiguous subarray within a one-dimensional array of numbers that has the largest or smallest sum, typically in linear time.
//   • Idea: This algorithm efficiently finds the maximum (or minimum) sum of a contiguous subarray by iterating through the array and maintaining a current sum, resetting it if it becomes detrimental. It operates in O(N) time complexity with O(1) space complexity.
//   • Invariants: `global_max` holds the maximum sum of any contiguous subarray encountered up to the current element.; `current_max` holds the maximum sum of a contiguous subarray ending at the current element.
//   • Tips: Initialize current and global maximums appropriately (e.g., to negative infinity or first element).; Adapt for minimum sum by resetting current sum if it becomes positive.
//   • Pitfalls: Failing to correctly initialize maximum/minimum sum variables.; Not handling arrays where all elements are negative (for max sum) or positive (for min sum).
// - The Inclusion-Exclusion Principle (string, counting)
//   • When to use: Use when you need to determine the frequency of characters or substrings within a string. It is essential for tasks like anagram detection or checking character distribution.
//   • Idea: This technique involves iterating through a string to tally the occurrences of its constituent elements, typically characters or words. It generally operates in O(N) time complexity, where N is the string's length.
//   • Invariants: The count for each character reflects its total occurrences processed so far.; All characters encountered up to the current position have been tallied.
//   • Tips: Use a hash map (dictionary) for arbitrary character sets.; Use an array for fixed-size character sets (e.g., ASCII, lowercase English).
//   • Pitfalls: Forgetting to handle case sensitivity or ignore non-alphanumeric characters.; Incorrectly handling Unicode characters with fixed-size arrays.
//
// Notes:
// - Keep the given method signatures unchanged.
// - Use only Java standard library (`java.*`); no external dependencies.
// - Do not change input/output formats or return value semantics.
// - Conformance: single public class 'Solution'; no 'package' statement; place any extra types as static inner classes.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
    public int maxDifference(String s, int k) {
        int n = s.length();
        int[][] freq = new int[n + 1][5];

        for (int i = 0; i < n; i++) {
            int digit = s.charAt(i) - '0';
            for (int d = 0; d < 5; d++) {
                freq[i + 1][d] = freq[i][d];
            }
            freq[i + 1][digit]++;
        }

        int maxDiff = -1;

        for (int a = 0; a < 5; a++) {
            for (int b = 0; b < 5; b++) {
                if (a == b) continue;

                int currentMax = Integer.MIN_VALUE;
                int currentSum = Integer.MIN_VALUE;

                for (int end = k - 1; end < n; end++) {
                    int start = end - k + 1;

                    int freqA = freq[end + 1][a] - freq[start][a];
                    int freqB = freq[end + 1][b] - freq[start][b];

                    int value = (freqA % 2 == 1 ? 1 : -1) + (freqB % 2 == 0 && freqB > 0 ? -1 : 1);

                    if (currentSum < 0) {
                        currentSum = value;
                    } else {
                        currentSum += value;
                    }

                    currentMax = Math.max(currentMax, currentSum);
                }

                if (currentMax > 0) {
                    maxDiff = Math.max(maxDiff, currentMax);
                }
            }
        }

        return maxDiff;         
    }
}
