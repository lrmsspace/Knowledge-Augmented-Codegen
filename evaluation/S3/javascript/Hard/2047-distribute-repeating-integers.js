// Source: https://leetcode.com/problems/distribute-repeating-integers/   |   Difficulty: Hard
//
// Problem Description:
// You are given an array of n integers, nums, where there are at most 50 unique values in the array. You are also given an array of m customer order quantities, quantity, where quantity[i] is the amount of integers the ith customer ordered. Determine if it is possible to distribute nums such that:
//
//
// 	The ith customer gets exactly quantity[i] integers,
// 	The integers the ith customer gets are all equal, and
// 	Every customer is satisfied.
//
//
// Return true if it is possible to distribute nums according to the above conditions.
//
// Example:
// Input: nums = [1,2,3,4], quantity = [2]
// Output: false
// Explanation: The 0th customer cannot be given two different integers.
//
// Constraints:
// n == nums.length
// 	1 <= n <= 105
// 	1 <= nums[i] <= 1000
// 	m == quantity.length
// 	1 <= m <= 10
// 	1 <= quantity[i] <= 105
// 	There are at most 50 unique values in nums.
//
// Helpful references (internal KB):
// - MEX (minimal excluded) of a sequence (array, enumeration)
//   • When to use: Use when you need to find the smallest non-negative integer that is not present in a given collection of numbers. It's often applied in problems involving game theory or combinatorial analysis.
//   • Idea: This algorithm finds the smallest non-negative integer not present in a given sequence or set. It typically involves marking present numbers and then iterating from zero to find the first unmarked number, achieving O(N) or O(N log N) complexity.
//   • Invariants: All non-negative integers less than the current candidate MEX value have been found in the input sequence.; The data structure used for presence tracking accurately reflects which non-negative integers up to a certain bound are present.
//   • Tips: Use a boolean array or hash set for efficient presence checking.; The MEX value is at most N (for N elements) if all numbers are distinct and within [0, N-1].
//   • Pitfalls: Forgetting to handle the case where all numbers from 0 to N-1 are present, meaning MEX is N.; Using an inefficient method for presence checking, leading to higher time complexity.
// - The Inclusion-Exclusion Principle (string, counting)
//   • When to use: Use when you need to determine the frequency of characters or substrings within a string. It is essential for tasks like anagram detection or checking character distribution.
//   • Idea: This technique involves iterating through a string to tally the occurrences of its constituent elements, typically characters or words. It generally operates in O(N) time complexity, where N is the string's length.
//   • Invariants: The count for each character reflects its total occurrences processed so far.; All characters encountered up to the current position have been tallied.
//   • Tips: Use a hash map (dictionary) for arbitrary character sets.; Use an array for fixed-size character sets (e.g., ASCII, lowercase English).
//   • Pitfalls: Forgetting to handle case sensitivity or ignore non-alphanumeric characters.; Incorrectly handling Unicode characters with fixed-size arrays.
// - bucket-sort (array, bucket-sort)
//   • When to use: When the input elements are uniformly distributed across a specific range, allowing for efficient partitioning and sorting.
//   • Idea: Bucket sort distributes elements into a fixed number of buckets, sorts each bucket, then concatenates them. It achieves O(N+K) average time complexity, where N is elements and K is buckets, assuming uniform distribution.
//   • Invariants: All elements from the input are initially present in the unsorted collection.; After distribution, each element resides in exactly one bucket, corresponding to its value range.
//   • Tips: Choose the number of buckets carefully based on data range and distribution.; Use an efficient sorting algorithm for individual buckets (e.g., insertion sort for small buckets).
//   • Pitfalls: Poor performance with non-uniform data distribution, leading to elements clustering in few buckets.; Requires knowing the range of input values beforehand to define bucket boundaries.
//
// Notes:
// - Keep the given function signature unchanged.
// - Do not add custom input parsing or console I/O unless the template explicitly requires it; rely on parameters/return value only.
// - Use standard ECMAScript features supported by LeetCode (Node.js runtime); no external packages.
// - Be careful with number precision: JavaScript Number is double; use BigInt only when necessary and keep return type consistent with the problem requirements.
// - If you introduce helper functions, define them in the same file and avoid relying on global mutable state across test cases.

/**
 * @param {number[]} nums
 * @param {number[]} quantity
 * @return {boolean}
 */
var canDistribute = function(nums, quantity) {
    
    // Count the frequency of each unique integer in nums
    const freqMap = new Map();
    for (const num of nums) {
        freqMap.set(num, (freqMap.get(num) || 0) + 1);
    }
    const frequencies = Array.from(freqMap.values());
    // Sort the frequencies in descending order
    frequencies.sort((a, b) => b - a);
    // Sort the quantity array in descending order
    quantity.sort((a, b) => b - a);
    // Backtracking function to try to satisfy each customer's quantity
    const backtrack = (index) => {
        if (index === quantity.length) return true; // All customers satisfied
        for (let i = 0; i < frequencies.length; i++) {
            if (frequencies[i] >= quantity[index]) {
                frequencies[i] -= quantity[index]; // Use this frequency for the current customer
                if (backtrack(index + 1)) return true; // Move to the next customer
                frequencies[i] += quantity[index]; // Backtrack
            }
        }
        return false; // No valid distribution found for this customer
    };

    return backtrack(0);
        
};
