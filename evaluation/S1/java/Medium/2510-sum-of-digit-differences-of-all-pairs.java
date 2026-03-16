// Source: https://leetcode.com/problems/sum-of-digit-differences-of-all-pairs/   |   Difficulty: Medium
//
// Problem Description:
// You are given an array nums consisting of positive integers where all integers have the same number of digits.
//
// The digit difference between two integers is the count of different digits that are in the same position in the two integers.
//
// Return the sum of the digit differences between all pairs of integers in nums.
//
// Example:
// Input: nums = [13,23,12]
//
// Output: 4
//
// Explanation:
// We have the following:
// - The digit difference between 13 and 23 is 1.
// - The digit difference between 13 and 12 is 1.
// - The digit difference between 23 and 12 is 2.
// So the total sum of digit differences between all pairs of integers is 1 + 1 + 2 = 4.
//
// Constraints:
// 2 <= nums.length <= 105
// 	1 <= nums[i] < 109
// 	All integers in nums have the same number of digits.
//
// Helpful references (internal KB):
// - Digit DP (array, number, digit-dp, recursion)
//   • When to use: Used for counting numbers or summing properties of numbers within a given range [A, B] that satisfy certain digit-based conditions.
//   • Idea: Digit DP is a dynamic programming technique to count numbers or calculate sums of properties for numbers in a given range [A, B] by building them digit by digit. It typically operates in O(D * S) time, where D is the number of digits and S is the maximum sum/property value.
//   • Invariants: The `tight` parameter correctly reflects if the current digit choice is restricted by the original number's digit at the current position.; The `sum` parameter accurately accumulates the sum of digits chosen for the prefix constructed so far.
//   • Tips: Convert the upper bound number into a digit array for easier processing.; Define the DP state to include current index, tight constraint, and any relevant accumulated property (e.g., sum, count).
//   • Pitfalls: Incorrectly handling the `tight` constraint, leading to overcounting or undercounting.; Forgetting to memoize or using an insufficient DP table size for state parameters.
// - String Sorts (array, string, number, radix-sort, counting-sort)
//   • When to use: Use when sorting a large collection of fixed-length strings or integers, especially when the key range (alphabet size) is small. It is efficient for data with uniform key lengths.
//   • Idea: LSD Radix Sort sorts elements by processing digits or characters from the least significant to the most significant, using a stable counting sort for each position. It achieves a time complexity of O(W * (N + R)), where W is the key length, N is the number of items, and R is the radix.
//   • Invariants: After each pass 'd' (from 'w-1' down to '0'), the array 'a' is stably sorted based on characters from position 'd' to 'w-1'.; The 'count' array accurately reflects the frequency of each character at the current digit 'd' before cumulation.
//   • Tips: Utilize counting sort as the stable inner sorting algorithm for each digit pass.; Process characters or digits from right to left (least significant to most significant).
//   • Pitfalls: Inefficient for variable-length strings without proper padding or specialized handling.; Can be slower than comparison sorts for small input sizes or very large radix (R).
// - Finding repetitions (string, array, z-function, enumeration)
//   • When to use: This algorithm efficiently finds all repetitions (periodic substrings) within a given string by combining divide-and-conquer with the Z-function. It is particularly useful for identifying overlapping or crossing periodic patterns.
//   • Idea: The Main-Lorentz algorithm finds all repetitions in a string by recursively splitting it into halves and identifying 'crossing repetitions' using the Z-function. This approach achieves an optimal O(N log N) time complexity.
//   • Invariants: For any fixed `cntr` position, all identified crossing repetitions have a total length of $2 	imes (|u| - cntr)$.; The segment $u[cntr - k_1 	ext{ to } cntr - 1]$ is identical to $u[|u| - k_1 	ext{ to } |u| - 1]$.
//   • Tips: Employ divide-and-conquer to break the problem into subproblems for repetitions within halves and crossing repetitions.; Utilize the Z-function to compute $k_1$ and $k_2$ values in O(1) for each `cntr` position, speeding up crossing repetition detection.
//   • Pitfalls: Correctly identifying and defining 'crossing repetitions' is the most intricate part of the algorithm.; Careful implementation of the Z-function for both the original and reversed string segments is crucial.
//
// Notes:
// - Keep the given method signatures unchanged.
// - Use only Java standard library (`java.*`); no external dependencies.
// - Do not change input/output formats or return value semantics.
// - Conformance: single public class 'Solution'; no 'package' statement; place any extra types as static inner classes.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
    public long sumDigitDifferences(int[] nums) {
        int n = nums.length;
        int d = String.valueOf(nums[0]).length(); // number of digits

        // count[digit_position][digit_value] = frequency of digit_value at digit_position
        int[][] count = new int[d][10];

        // Fill the count array
        for (int num : nums) {
            String s = String.valueOf(num);
            for (int i = 0; i < d; i++) {
                int digit = s.charAt(i) - '0';
                count[i][digit]++;
            }
        }

        long totalDifference = 0;

        // Calculate the total digit differences
        for (int i = 0; i < d; i++) {
            for (int digit1 = 0; digit1 <= 9; digit1++) {
                for (int digit2 = 0; digit2 <= 9; digit2++) {
                    if (digit1 != digit2) {
                        totalDifference += (long) count[i][digit1] * count[i][digit2];
                    }
                }
            }
        }

        // Each pair is counted twice, so divide by 2
        return totalDifference / 2;         
    }
}
