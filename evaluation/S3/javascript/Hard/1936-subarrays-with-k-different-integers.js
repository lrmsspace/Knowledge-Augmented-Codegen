// Source: https://leetcode.com/problems/subarrays-with-k-different-integers/   |   Difficulty: Hard
//
// Problem Description:
// Given an integer array nums and an integer k, return the number of good subarrays of nums.
//
// A good array is an array where the number of different integers in that array is exactly k.
//
//
// 	For example, [1,2,3,1,2] has 3 different integers: 1, 2, and 3.
//
//
// A subarray is a contiguous part of an array.
//
// Example:
// Input: nums = [1,2,1,2,3], k = 2
// Output: 7
// Explanation: Subarrays formed with exactly 2 different integers: [1,2], [2,1], [1,2], [2,3], [1,2,1], [2,1,2], [1,2,1,2]
//
// Constraints:
// 1 <= nums.length <= 2 * 104
// 	1 <= nums[i], k <= nums.length
//
// Helpful references (internal KB):
// - The Inclusion-Exclusion Principle (array, number, counting, sieve)
//   • When to use: Use when direct counting of elements satisfying specific conditions is difficult due to overlaps, and you need to find the count of elements satisfying at least one, exactly k, or none of several properties.
//   • Idea: The Inclusion-Exclusion Principle counts the size of a union of sets by alternately adding and subtracting the sizes of intersections of increasing numbers of sets. Its complexity is often exponential in the number of properties.
//   • Invariants: At the start of processing subsets of size k, the running total correctly accounts for all intersections of size less than k.; For every element x, its contribution to the total sum is 1 if it satisfies the target condition, and 0 otherwise.
//   • Tips: Clearly define the properties (P1, P2, ..., Pn) for which elements are counted.; Systematically calculate the sizes of all relevant intersections of properties.
//   • Pitfalls: Incorrectly defining the properties or the universe of elements being counted.; Errors in calculating the sizes of specific intersections of properties.
// - The Inclusion-Exclusion Principle (matrix, array, dp-2d, counting)
//   • When to use: Use when needing to count elements satisfying "at least one" of several properties, especially when direct counting is complicated by overlapping sets. It's also applicable for counting elements satisfying "none" of the properties by subtracting from the total.
//   • Idea: The Inclusion-Exclusion Principle is a combinatorial method to determine the size of the union of multiple finite sets. It works by summing the sizes of individual sets, subtracting the sizes of all pairwise intersections, adding back the sizes of all three-way intersections, and so on, with alternating signs.
//   • Invariants: The count for any element satisfying `k` properties is adjusted to be exactly 1 in the final sum.; Each term in the sum corresponds to the size of an intersection of a distinct subset of properties.
//   • Tips: Clearly define the universe and the properties (sets) you are interested in.; Systematically list all combinations of properties for intersection terms.
//   • Pitfalls: Incorrectly identifying or defining the properties or sets.; Missing certain intersection terms or double-counting them.
// - The Inclusion-Exclusion Principle (string, counting)
//   • When to use: Use when you need to determine the frequency of characters or substrings within a string. It is essential for tasks like anagram detection or checking character distribution.
//   • Idea: This technique involves iterating through a string to tally the occurrences of its constituent elements, typically characters or words. It generally operates in O(N) time complexity, where N is the string's length.
//   • Invariants: The count for each character reflects its total occurrences processed so far.; All characters encountered up to the current position have been tallied.
//   • Tips: Use a hash map (dictionary) for arbitrary character sets.; Use an array for fixed-size character sets (e.g., ASCII, lowercase English).
//   • Pitfalls: Forgetting to handle case sensitivity or ignore non-alphanumeric characters.; Incorrectly handling Unicode characters with fixed-size arrays.
//
// Notes:
// - Keep the given function signature unchanged.
// - Do not add custom input parsing or console I/O unless the template explicitly requires it; rely on parameters/return value only.
// - Use standard ECMAScript features supported by LeetCode (Node.js runtime); no external packages.
// - Be careful with number precision: JavaScript Number is double; use BigInt only when necessary and keep return type consistent with the problem requirements.
// - If you introduce helper functions, define them in the same file and avoid relying on global mutable state across test cases.

/**
 * @param {number[]} nums
 * @param {number} k
 * @return {number}
 */
var subarraysWithKDistinct = function(nums, k) {
    // The number of subarrays with exactly k distinct integers can be calculated as:
    // count of subarrays with at most k distinct integers - count of subarrays with at most (k - 1) distinct integers
    const atMostK = (k) => {
        let count = 0;
        const freq = new Map();
        let left = 0;
        for (let right = 0; right < nums.length; right++) {
            freq.set(nums[right], (freq.get(nums[right]) || 0) + 1);
            while (freq.size > k) {
                freq.set(nums[left], freq.get(nums[left]) - 1);
                if (freq.get(nums[left]) === 0) {
                    freq.delete(nums[left]);
                }
                left++;
            }
            count += right - left + 1; // All subarrays ending at right with at most k distinct integers
        }
        return count;
    };

    return atMostK(k) - atMostK(k - 1);
            
};
