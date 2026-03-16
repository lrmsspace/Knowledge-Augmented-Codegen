// Source: https://leetcode.com/problems/transform-array-by-parity/   |   Difficulty: Easy
//
// Problem Description:
// You are given an integer array nums. Transform nums by performing the following operations in the exact order specified:
//
//
// 	Replace each even number with 0.
// 	Replace each odd numbers with 1.
// 	Sort the modified array in non-decreasing order.
//
//
// Return the resulting array after performing these operations.
//
// Example:
// Input: nums = [4,3,2,1]
//
// Output: [0,0,1,1]
//
// Explanation:
//
//
// 	Replace the even numbers (4 and 2) with 0 and the odd numbers (3 and 1) with 1. Now, nums = [0, 1, 0, 1].
// 	After sorting nums in non-descending order, nums = [0, 0, 1, 1].
//
// Constraints:
// 1 <= nums.length <= 100
// 	1 <= nums[i] <= 1000
//
// Helpful references (internal KB):
// - Non-negative Integers without Consecutive Ones (number, enumeration, simulation)
//   • When to use: Use when counting numbers up to a given limit that satisfy a specific bit pattern constraint, particularly when the limit is small enough for direct iteration and checking.
//   • Idea: This approach iterates through every non-negative integer from 0 up to the given limit num. For each integer, it simulates checking its binary representation to determine if it contains any two consecutive '1's.
//   • Invariants: count stores the number of integers k (where 0 <= k < i) that do not have consecutive ones.; All integers j such that 0 <= j < i have been processed.
//   • Tips: Use bitwise operations like (i & (i >> 1)) to efficiently detect consecutive ones.; Remember to include 0 in the count as it satisfies the condition (no consecutive ones).
//   • Pitfalls: Performance degradation for large num due to linear scan and per-number bit check.; Incorrectly handling the upper bound of the iteration (e.g., i < num instead of i <= num).
// - String Sorts (array, string, number, radix-sort, counting-sort)
//   • When to use: Use when sorting a large collection of fixed-length strings or integers, especially when the key range (alphabet size) is small. It is efficient for data with uniform key lengths.
//   • Idea: LSD Radix Sort sorts elements by processing digits or characters from the least significant to the most significant, using a stable counting sort for each position. It achieves a time complexity of O(W * (N + R)), where W is the key length, N is the number of items, and R is the radix.
//   • Invariants: After each pass 'd' (from 'w-1' down to '0'), the array 'a' is stably sorted based on characters from position 'd' to 'w-1'.; The 'count' array accurately reflects the frequency of each character at the current digit 'd' before cumulation.
//   • Tips: Utilize counting sort as the stable inner sorting algorithm for each digit pass.; Process characters or digits from right to left (least significant to most significant).
//   • Pitfalls: Inefficient for variable-length strings without proper padding or specialized handling.; Can be slower than comparison sorts for small input sizes or very large radix (R).
// - Elementary Sorts (array, enumeration)
//   • When to use: Selection sort is simple but inefficient. It's suitable for very small datasets or educational purposes where simplicity of implementation is prioritized over performance.
//   • Idea: Selection sort repeatedly finds the minimum element from the unsorted portion of the array and places it at the beginning of the sorted portion. It has a time complexity of O(N^2) and a space complexity of O(1).
//   • Invariants: The elements in the prefix of the array are sorted.; All elements in the sorted prefix are less than or equal to all elements in the unsorted suffix.
//   • Tips: Easy to understand and implement.; Performs a minimal number of swaps (exactly N-1 swaps).
//   • Pitfalls: Inefficient for large datasets due to O(N^2) time complexity.; Performance is not affected by the initial order of elements.
//
// Notes:
// - Keep the given method signatures unchanged.
// - Use only Java standard library (`java.*`); no external dependencies.
// - Do not change input/output formats or return value semantics.
// - Conformance: single public class 'Solution'; no 'package' statement; place any extra types as static inner classes.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
    public int[] transformArray(int[] nums) {
        int n = nums.length;
        int[] result = new int[n];
        int index = 0;

        // First, replace even numbers with 0 and odd numbers with 1
        for (int num : nums) {
            if (num % 2 == 0) {
                result[index++] = 0;
            } else {
                result[index++] = 1;
            }
        }

        // Since the array only contains 0s and 1s, we can count them
        int countZero = 0;
        for (int value : result) {
            if (value == 0) {
                countZero++;
            }
        }

        // Fill the result array with sorted values: all 0s followed by all 1s
        for (int i = 0; i < n; i++) {
            if (i < countZero) {
                result[i] = 0;
            } else {
                result[i] = 1;
            }
        }

        return result;          
    }
}
