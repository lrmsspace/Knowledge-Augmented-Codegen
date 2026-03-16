// Source: https://leetcode.com/problems/count-subarrays-with-median-k/   |   Difficulty: Hard
//
// Problem Description:
// You are given an array nums of size n consisting of distinct integers from 1 to n and a positive integer k.
//
// Return the number of non-empty subarrays in nums that have a median equal to k.
//
// Note:
//
//
// 	The median of an array is the middle element after sorting the array in ascending order. If the array is of even length, the median is the left middle element.
//
// 	
// 		For example, the median of [2,3,1,4] is 2, and the median of [8,4,3,5,1] is 4.
// 	
// 	
// 	A subarray is a contiguous part of an array.
//
// Example:
// Input: nums = [3,2,1,4,5], k = 4
// Output: 3
// Explanation: The subarrays that have a median equal to 4 are: [4], [4,5] and [1,4,5].
//
// Constraints:
// n == nums.length
// 	1 <= n <= 105
// 	1 <= nums[i], k <= n
// 	The integers in nums are distinct.
//
// Helpful references (internal KB):
// - Search the subarray with the maximum/minimum sum (array, prefix-sum, max-window)
//   • When to use: When needing to find the maximum or minimum sum of any contiguous subarray within a given array efficiently. It is particularly useful for problems requiring an O(N) solution.
//   • Idea: This algorithm finds the maximum (or minimum) sum of a contiguous subarray by iterating through the array, maintaining a running prefix sum, and tracking the minimum (or maximum) prefix sum encountered so far. It achieves an optimal O(N) time complexity with O(1) auxiliary space.
//   • Invariants: max_global_sum stores the maximum subarray sum found among all subarrays ending at or before the current element.; min_prefix_sum_value correctly tracks the minimum prefix sum encountered up to the previous element's prefix sum.
//   • Tips: Use a running sum variable instead of explicitly storing the entire prefix sum array.; Keep track of the minimum prefix sum encountered up to the current point.
//   • Pitfalls: Incorrectly initializing the minimum prefix sum (e.g., to INT_MAX instead of 0 or s[0]).; Off-by-one errors when calculating subarray sums using prefix sums (s[r] - s[l-1]).
// - Digit DP (array, number, digit-dp, recursion)
//   • When to use: Used for counting numbers or summing properties of numbers within a given range [A, B] that satisfy certain digit-based conditions.
//   • Idea: Digit DP is a dynamic programming technique to count numbers or calculate sums of properties for numbers in a given range [A, B] by building them digit by digit. It typically operates in O(D * S) time, where D is the number of digits and S is the maximum sum/property value.
//   • Invariants: The `tight` parameter correctly reflects if the current digit choice is restricted by the original number's digit at the current position.; The `sum` parameter accurately accumulates the sum of digits chosen for the prefix constructed so far.
//   • Tips: Convert the upper bound number into a digit array for easier processing.; Define the DP state to include current index, tight constraint, and any relevant accumulated property (e.g., sum, count).
//   • Pitfalls: Incorrectly handling the `tight` constraint, leading to overcounting or undercounting.; Forgetting to memoize or using an insufficient DP table size for state parameters.
// -  
// Kth order statistic in O(N) (array, enumeration)
//   • When to use: Use when you need to find the Kth smallest or largest element in an unsorted array efficiently, without sorting the entire dataset. It's ideal for problems requiring a specific order statistic in linear average time.
//   • Idea: This algorithm finds the Kth smallest (or largest) element in an unsorted array in expected linear time, O(N), by repeatedly partitioning the array around a pivot. It is a selection algorithm, conceptually similar to quicksort but only recursing on one side.
//   • Invariants: All elements to the left of the chosen pivot are less than or equal to the pivot.; All elements to the right of the chosen pivot are greater than or equal to the pivot.
//   • Tips: Choose a good pivot (e.g., random element) to minimize the chance of worst-case performance.; The algorithm can be implemented iteratively to avoid potential recursion depth limits for very large inputs.
//   • Pitfalls: Poor pivot selection can lead to a worst-case time complexity of O(N^2).; Off-by-one errors are common when translating K (1-based) to array indices (0-based).
//
// Notes:
// - Keep the given function signature unchanged.
// - Use the C standard library only; no external packages.
// - Do not change input/output formats or return value semantics.
// - Conformance: ISO C (C89/C99/C11). Do NOT use GNU C extensions (nested functions, statement expressions, typeof, __auto_type, etc.). Avoid VLAs and non-standard builtins.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

int countSubarrays(int* nums, int numsSize, int k) {
    int kIndex = -1;
    for (int i = 0; i < numsSize; ++i) {
        if (nums[i] == k) {
            kIndex = i;
            break;
        }
    }

    int count = 0;
    int balance = 0;
    int balanceCount[2 * numsSize + 1];
    memset(balanceCount, 0, sizeof(balanceCount));
    balanceCount[numsSize] = 1; // balance 0 at index kIndex

    // Count balances to the left of kIndex
    for (int i = kIndex - 1; i >= 0; --i) {
        if (nums[i] < k) {
            balance--;
        } else {
            balance++;
        }
        balanceCount[balance + numsSize]++;
    }

    // Reset balance for right side
    balance = 0;

    // Count valid subarrays including and to the right of kIndex
    for (int i = kIndex; i < numsSize; ++i) {
        if (nums[i] < k) {
            balance--;
        } else {
            balance++;
        }
        count += balanceCount[numsSize - balance];     // even length subarrays
        count += balanceCount[numsSize - balance + 1]; // odd length subarrays
    }

    return count;       
}
