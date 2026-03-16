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
// -  
// Kth order statistic in O(N) (array, enumeration)
//   • When to use: Use when you need to find the Kth smallest or largest element in an unsorted array efficiently, without sorting the entire dataset. It's ideal for problems requiring a specific order statistic in linear average time.
//   • Idea: This algorithm finds the Kth smallest (or largest) element in an unsorted array in expected linear time, O(N), by repeatedly partitioning the array around a pivot. It is a selection algorithm, conceptually similar to quicksort but only recursing on one side.
//   • Invariants: All elements to the left of the chosen pivot are less than or equal to the pivot.; All elements to the right of the chosen pivot are greater than or equal to the pivot.
//   • Tips: Choose a good pivot (e.g., random element) to minimize the chance of worst-case performance.; The algorithm can be implemented iteratively to avoid potential recursion depth limits for very large inputs.
//   • Pitfalls: Poor pivot selection can lead to a worst-case time complexity of O(N^2).; Off-by-one errors are common when translating K (1-based) to array indices (0-based).
// - MEX (minimal excluded) of a sequence (tree, binary-search)
//   • When to use: Use when you need to efficiently find the MEX of a sequence after multiple point updates, where the sequence elements are non-negative integers.
//   • Idea: This approach uses a segment tree or similar data structure to maintain counts of elements, allowing efficient O(log N) updates and O(log N) queries for the minimal excluded number (MEX). The core idea is to find the smallest non-negative integer not present in the sequence.
//   • Invariants: Each node in the segment tree correctly stores the count of distinct numbers within its represented range.; The MEX query always explores the leftmost child first if its range is not 'full' (i.e., missing elements).
//   • Tips: Build the tree over the range of possible non-negative integer values, typically up to N or a maximum constraint.; Each tree node should store the count of distinct numbers present within its represented range.
//   • Pitfalls: Forgetting to handle numbers larger than the maximum range covered by the segment tree.; Incorrectly updating counts for elements, leading to stale or erroneous MEX values.
// - Non-negative Integers without Consecutive Ones (number, recursion, backtracking)
//   • When to use: Use when counting numbers within a range that satisfy a specific digit-based or bit-based pattern constraint, especially when the constraint involves adjacent digits or bits.
//   • Idea: This algorithm recursively generates binary numbers bit by bit, ensuring no two consecutive ones are formed. It prunes branches that exceed a given upper limit or violate the consecutive one constraint, effectively counting valid numbers up to N in O(log N) time.
//   • Invariants: The `sum` generated so far never exceeds the target `num`.; The `prev` boolean accurately reflects whether the last bit added was a '1'.
//   • Tips: Generate numbers bit by bit, typically from LSB or MSB, to build up valid sequences.; Maintain state about the previously placed bit to enforce the 'no consecutive ones' rule.
//   • Pitfalls: Failing to correctly handle the base cases for the recursive function.; Incorrectly managing the 'previous bit' state, leading to invalid sequences.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use the C standard library only; no external packages.
// - Do not change input/output formats or return value semantics.
// - Conformance: ISO C (C89/C99/C11). Do NOT use GNU C extensions (nested functions, statement expressions, typeof, __auto_type, etc.). Avoid VLAs and non-standard builtins.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

int countSubarrays(int* nums, int numsSize, int k) {
    int count = 0;
    int left = 0, right = 0;
    int lessCount = 0, greaterCount = 0;

    while (right < numsSize) {
        if (nums[right] < k) {
            lessCount++;
        } else if (nums[right] > k) {
            greaterCount++;
        }

        while (lessCount > greaterCount) {
            if (nums[left] < k) {
                lessCount--;
            } else if (nums[left] > k) {
                greaterCount--;
            }
            left++;
        }

        if (lessCount == greaterCount) {
            count += right - left + 1;
        }
        right++;
    }

    return count;       
}
