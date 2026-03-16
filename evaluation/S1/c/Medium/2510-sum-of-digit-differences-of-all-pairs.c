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
// - Keep the given function signature unchanged.
// - Use the C standard library only; no external packages.
// - Do not change input/output formats or return value semantics.
// - Conformance: ISO C (C89/C99/C11). Do NOT use GNU C extensions (nested functions, statement expressions, typeof, __auto_type, etc.). Avoid VLAs and non-standard builtins.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

long long sumDigitDifferences(int* nums, int numsSize) {
    int count[10] = {0};
    long long result = 0;

    // Count occurrences of each digit in the least significant position
    for (int i = 0; i < numsSize; i++) {
        int digit = nums[i] % 10;
        count[digit]++;
    }

    // Calculate the sum of digit differences for the least significant position
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            if (i != j) {
                result += (long long)count[i] * count[j];
            }
        }
    }

    // Process each digit position
    int divisor = 10;
    while (divisor <= 1000000000) {
        // Reset count array for the current digit position
        for (int i = 0; i < 10; i++) {
            count[i] = 0;
        }

        // Count occurrences of each digit in the current position
        for (int i = 0; i < numsSize; i++) {
            int digit = (nums[i] / divisor) % 10;
            count[digit]++;
        }

        // Calculate the sum of digit differences for the current position
        for (int i = 0; i < 10; i++) {
            for (int j = 0; j < 10; j++) {
                if (i != j) {
                    result += (long long)count[i] * count[j];
                }
            }
        }

        divisor *= 10;
    }

    return result;      
}
