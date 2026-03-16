// Source: https://leetcode.com/problems/divide-array-in-sets-of-k-consecutive-numbers/   |   Difficulty: Medium
//
// Problem Description:
// Given an array of integers nums and a positive integer k, check whether it is possible to divide this array into sets of k consecutive numbers.
//
// Return true if it is possible. Otherwise, return false.
//
// Example:
// Input: nums = [1,2,3,3,4,4,5,6], k = 4
// Output: true
// Explanation: Array can be divided into [1,2,3,4] and [3,4,5,6].
//
// Constraints:
// 1 <= k <= nums.length <= 105
// 	1 <= nums[i] <= 109
//
//
//  
// Note: This question is the same as 846: https://leetcode.com/problems/hand-of-straights/
//
// Helpful references (internal KB):
// - MEX (minimal excluded) of a sequence (array, enumeration)
//   • When to use: Use when you need to find the smallest non-negative integer that is not present in a given collection of numbers. It's often applied in problems involving game theory or combinatorial analysis.
//   • Idea: This algorithm finds the smallest non-negative integer not present in a given sequence or set. It typically involves marking present numbers and then iterating from zero to find the first unmarked number, achieving O(N) or O(N log N) complexity.
//   • Invariants: All non-negative integers less than the current candidate MEX value have been found in the input sequence.; The data structure used for presence tracking accurately reflects which non-negative integers up to a certain bound are present.
//   • Tips: Use a boolean array or hash set for efficient presence checking.; The MEX value is at most N (for N elements) if all numbers are distinct and within [0, N-1].
//   • Pitfalls: Forgetting to handle the case where all numbers from 0 to N-1 are present, meaning MEX is N.; Using an inefficient method for presence checking, leading to higher time complexity.
// - Reservoir Sampling (array, randomized, simulation)
//   • When to use: When you need to randomly select a fixed number of items (k) from a stream or a very large dataset of unknown size, ensuring each item has an equal probability of selection in a single pass.
//   • Idea: Reservoir sampling is a randomized algorithm that selects k items from a list containing n items, where n is either a very large or unknown number, ensuring each item has an equal probability of being selected. It processes the input in a single pass with O(N) time complexity and O(k) space complexity.
//   • Invariants: The reservoir always contains exactly k elements.; Any element processed up to the current index `i` has a k/(i+1) probability of being in the reservoir.
//   • Tips: Initialize the reservoir with the first k elements from the stream.; For each subsequent element, generate a random index from 0 to current_stream_index.
//   • Pitfalls: Failing to correctly initialize the reservoir with the first k elements.; Generating random indices outside the valid range [0, current_stream_index] or [0, k-1].
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

bool isPossibleDivide(int* nums, int numsSize, int k) {
    if (numsSize % k != 0) {
        return false; // If total number of elements is not divisible by k, return false
    }

    // Count the frequency of each number
    int count[1000000001] = {0}; // Assuming nums[i] <= 10^9
    for (int i = 0; i < numsSize; i++) {
        count[nums[i]]++;
    }

    // Try to form sets of k consecutive numbers
    for (int i = 0; i < 1000000001; i++) {
        while (count[i] > 0) { // While there are occurrences of the current number
            for (int j = 0; j < k; j++) {
                if (count[i + j] <= 0) {
                    return false; // If any number in the consecutive sequence is missing, return false
                }
                count[i + j]--; // Decrease the count for each number in the sequence
            }
        }
    }

    return true; // All numbers can be grouped into sets of k consecutive numbers       
}
