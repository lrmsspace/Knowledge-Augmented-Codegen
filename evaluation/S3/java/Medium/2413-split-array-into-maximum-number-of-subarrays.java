// Source: https://leetcode.com/problems/split-array-into-maximum-number-of-subarrays/   |   Difficulty: Medium
//
// Problem Description:
// You are given an array nums consisting of non-negative integers.
//
// We define the score of subarray nums[l..r] such that l <= r as nums[l] AND nums[l + 1] AND ... AND nums[r] where AND is the bitwise AND operation.
//
// Consider splitting the array into one or more subarrays such that the following conditions are satisfied:
//
//
// 	Each element of the array belongs to exactly one subarray.
// 	The sum of scores of the subarrays is the minimum possible.
//
//
// Return the maximum number of subarrays in a split that satisfies the conditions above.
//
// A subarray is a contiguous part of an array.
//
// Example:
// Input: nums = [1,0,2,0,1,2]
// Output: 3
// Explanation: We can split the array into the following subarrays:
// - [1,0]. The score of this subarray is 1 AND 0 = 0.
// - [2,0]. The score of this subarray is 2 AND 0 = 0.
// - [1,2]. The score of this subarray is 1 AND 2 = 0.
// The sum of scores is 0 + 0 + 0 = 0, which is the minimum possible score that we can obtain.
// It can be shown that we cannot split the array into more than 3 subarrays with a total score of 0. So we return 3.
//
// Constraints:
// 1 <= nums.length <= 105
// 	0 <= nums[i] <= 106
//
// Helpful references (internal KB):
// - Submask Enumeration
//  (number, bitset, enumeration, bitmask-dp)
//   • When to use: When a problem requires iterating through all possible submasks for each given mask. This is common in bitmask dynamic programming problems where relationships between a set and its subsets are crucial.
//   • Idea: This algorithm efficiently iterates through all submasks for every mask from 0 to 2^N - 1. It has a total time complexity of O(3^N) for all masks and their submasks.
//   • Invariants: For a given `mask`, `submask` always represents a subset of `mask`.; Each `submask` is visited exactly once for its corresponding `mask`.
//   • Tips: The `submask = (submask - 1) & mask` trick is crucial for efficient iteration.; Ensure the outer loop iterates through all masks from 0 to 2^N - 1.
//   • Pitfalls: Forgetting the `& mask` part in the inner loop can lead to incorrect submasks or infinite loops.; Misunderstanding the O(3^N) total complexity, leading to Time Limit Exceeded for large N.
// - Bit manipulation (number, enumeration, simulation)
//   • When to use: When problems involve manipulating individual bits of numbers, representing sets as bitmasks, or optimizing operations on powers of two. It is also useful for certain combinatorics and dynamic programming problems.
//   • Idea: Bit manipulation involves directly operating on the binary representation of numbers using bitwise operators. This technique is often used to optimize computations, manage boolean flags efficiently, or represent subsets, typically achieving O(1) complexity for fixed-size integers.
//   • Invariants: Each bit in the mask accurately reflects the inclusion or exclusion status of its corresponding element.; Bitwise operations maintain the integrity of unaffected bits.
//   • Tips: Use (1 << k) to create a mask with the k-th bit set.; n & (n-1) clears the least significant set bit.
//   • Pitfalls: Incorrect operator precedence can lead to subtle bugs.; Mixing signed and unsigned integers in bitwise operations can yield unexpected results.
// - MEX (minimal excluded) of a sequence (array, enumeration)
//   • When to use: Use when you need to find the smallest non-negative integer that is not present in a given collection of numbers. It's often applied in problems involving game theory or combinatorial analysis.
//   • Idea: This algorithm finds the smallest non-negative integer not present in a given sequence or set. It typically involves marking present numbers and then iterating from zero to find the first unmarked number, achieving O(N) or O(N log N) complexity.
//   • Invariants: All non-negative integers less than the current candidate MEX value have been found in the input sequence.; The data structure used for presence tracking accurately reflects which non-negative integers up to a certain bound are present.
//   • Tips: Use a boolean array or hash set for efficient presence checking.; The MEX value is at most N (for N elements) if all numbers are distinct and within [0, N-1].
//   • Pitfalls: Forgetting to handle the case where all numbers from 0 to N-1 are present, meaning MEX is N.; Using an inefficient method for presence checking, leading to higher time complexity.
//
// Notes:
// - Keep the given method signatures unchanged.
// - Use only Java standard library (`java.*`); no external dependencies.
// - Do not change input/output formats or return value semantics.
// - Conformance: single public class 'Solution'; no 'package' statement; place any extra types as static inner classes.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
    public int maxSubarrays(int[] nums) {
        int count = 0;
        int currentAnd = ~0; // Start with all bits set to 1

        for (int num : nums) {
            currentAnd &= num; // Update the current AND with the next number
            if (currentAnd == 0) { // If the AND becomes 0, we can split here
                count++;
                currentAnd = ~0; // Reset for the next subarray
            }
        }

        return count;           
    }
}
