// Source: https://leetcode.com/problems/minimum-adjacent-swaps-to-alternate-parity/   |   Difficulty: Medium
//
// Problem Description:
// You are given an array nums of distinct integers.
//
// In one operation, you can swap any two adjacent elements in the array.
//
// An arrangement of the array is considered valid if the parity of adjacent elements alternates, meaning every pair of neighboring elements consists of one even and one odd number.
//
// Return the minimum number of adjacent swaps required to transform nums into any valid arrangement.
//
// If it is impossible to rearrange nums such that no two adjacent elements have the same parity, return -1.
//
// Example:
// Input: nums = [2,4,6,5,7]
//
// Output: 3
//
// Explanation:
//
// Swapping 5 and 6, the array becomes [2,4,5,6,7]
//
// Swapping 5 and 4, the array becomes [2,5,4,6,7]
//
// Swapping 6 and 7, the array becomes [2,5,4,7,6]. The array is now a valid arrangement. Thus, the answer is 3.
//
// Constraints:
// 1 <= nums.length <= 105
// 	1 <= nums[i] <= 109
// 	All elements in nums are distinct.
//
// Helpful references (internal KB):
// - Non-negative Integers without Consecutive Ones (number, enumeration, simulation)
//   • When to use: Use when counting numbers up to a given limit that satisfy a specific bit pattern constraint, particularly when the limit is small enough for direct iteration and checking.
//   • Idea: This approach iterates through every non-negative integer from 0 up to the given limit num. For each integer, it simulates checking its binary representation to determine if it contains any two consecutive '1's.
//   • Invariants: count stores the number of integers k (where 0 <= k < i) that do not have consecutive ones.; All integers j such that 0 <= j < i have been processed.
//   • Tips: Use bitwise operations like (i & (i >> 1)) to efficiently detect consecutive ones.; Remember to include 0 in the count as it satisfies the condition (no consecutive ones).
//   • Pitfalls: Performance degradation for large num due to linear scan and per-number bit check.; Incorrectly handling the upper bound of the iteration (e.g., i < num instead of i <= num).
// - Scheduling jobs on two machines (array, greedy)
//   • When to use: Use when optimizing the order of a sequence of tasks on two machines to minimize total idle time or makespan. It is typically applied when a greedy exchange argument can prove optimality.
//   • Idea: This algorithm determines an optimal sequence for jobs on two machines by iteratively applying a greedy choice, often proven optimal via an exchange argument. It typically achieves an optimal solution in polynomial time, commonly O(N log N) or O(N^2).
//   • Invariants: The relative order of jobs already placed in the schedule is optimal.; The total idle time for the current prefix of scheduled jobs is correctly calculated.
//   • Tips: Focus on the local effect of swapping adjacent elements to derive the greedy criterion.; Identify a metric (e.g., total idle time or makespan) that changes predictably with swaps.
//   • Pitfalls: The greedy choice might not be globally optimal for problems with more than two machines.; Incorrectly defining the cost function for idle time or makespan can lead to suboptimal solutions.
// - Fenwick Tree (array, bit-fenwick, difference-array)
//   • When to use: Use when an array requires frequent point updates and efficient retrieval of prefix sums or range sums. It offers logarithmic time complexity for both operations.
//   • Idea: A Fenwick Tree, or Binary Indexed Tree (BIT), is a data structure that efficiently supports point updates and prefix sum queries on an array in O(log N) time.
//   • Invariants: Each `bit[i]` stores the sum of a contiguous range of elements from the original array.; The range length represented by `bit[i]` is determined by `i & -i` (the least significant bit).
//   • Tips: Use 1-based indexing for simpler bitwise operations (`i & -i`).; Initialize with an existing array in O(N) time using a linear construction method.
//   • Pitfalls: Directly finding range minimum/maximum is not efficient or generally supported.; Operations must be associative and preferably invertible for general range queries.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use the C standard library only; no external packages.
// - Do not change input/output formats or return value semantics.
// - Conformance: ISO C (C89/C99/C11). Do NOT use GNU C extensions (nested functions, statement expressions, typeof, __auto_type, etc.). Avoid VLAs and non-standard builtins.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

int minSwaps(int* nums, int numsSize) {
    int evenCount = 0, oddCount = 0;
    for (int i = 0; i < numsSize; i++) {
        if (nums[i] % 2 == 0) {
            evenCount++;
        } else {
            oddCount++;
        }
    }

    if (abs(evenCount - oddCount) > 1) {
        return -1;
    }

    int swapCount1 = 0, swapCount2 = 0;
    int evenIndex = 0, oddIndex = 0;

    for (int i = 0; i < numsSize; i++) {
        if (i % 2 == 0) {
            if (nums[i] % 2 != 0) {
                while (evenIndex < numsSize && nums[evenIndex] % 2 != 0) {
                    evenIndex++;
                }
                swapCount1 += evenIndex - i;
                evenIndex++;
            }
        } else {
            if (nums[i] % 2 == 0) {
                while (oddIndex < numsSize && nums[oddIndex] % 2 != 1) {
                    oddIndex++;
                }
                swapCount1 += oddIndex - i;
                oddIndex++;
            }
        }
    }

    evenIndex = 0;
    oddIndex = 0;

    for (int i = 0; i < numsSize; i++) {
        if (i % 2 == 1) {
            if (nums[i] % 2 != 0) {
                while (evenIndex < numsSize && nums[evenIndex] % 2 != 0) {
                    evenIndex++;
                }
                swapCount2 += evenIndex - i;
                evenIndex++;
            }
        } else {
            if (nums[i] % 2 == 0) {
                while (oddIndex < numsSize && nums[oddIndex] % 2 != 1) {
                    oddIndex++;
                }
                swapCount2 += oddIndex - i;
                oddIndex++;
            }
        }
    }

    if (evenCount > oddCount) {
        return swapCount1;
    } else if (oddCount > evenCount) {
        return swapCount2;
    } else {
        return swapCount1 < swapCount2 ? swapCount1 : swapCount2;
    }       
}
