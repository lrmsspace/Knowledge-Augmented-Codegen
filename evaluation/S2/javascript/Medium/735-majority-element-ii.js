// Source: https://leetcode.com/problems/majority-element-ii/   |   Difficulty: Medium
//
// Problem Description:
// Given an integer array of size n, find all elements that appear more than ⌊ n/3 ⌋ times.
//
// Example:
// Input: nums = [3,2,3]
// Output: [3]
//
// Constraints:
// 1 <= nums.length <= 5 * 104
// 	-109 <= nums[i] <= 109
//
//
//  
// Follow up: Could you solve the problem in linear time and in O(1) space?
//
// Helpful references (internal KB):
// -  
// Kth order statistic in O(N) (array, enumeration)
//   • When to use: Use when you need to find the Kth smallest or largest element in an unsorted array efficiently, without sorting the entire dataset. It's ideal for problems requiring a specific order statistic in linear average time.
//   • Idea: This algorithm finds the Kth smallest (or largest) element in an unsorted array in expected linear time, O(N), by repeatedly partitioning the array around a pivot. It is a selection algorithm, conceptually similar to quicksort but only recursing on one side.
//   • Invariants: All elements to the left of the chosen pivot are less than or equal to the pivot.; All elements to the right of the chosen pivot are greater than or equal to the pivot.
//   • Tips: Choose a good pivot (e.g., random element) to minimize the chance of worst-case performance.; The algorithm can be implemented iteratively to avoid potential recursion depth limits for very large inputs.
//   • Pitfalls: Poor pivot selection can lead to a worst-case time complexity of O(N^2).; Off-by-one errors are common when translating K (1-based) to array indices (0-based).
// - Linear Sieve (array, sieve)
//   • When to use: Use when you need to find all prime numbers up to a given limit N, or compute the least prime factor for all numbers in that range, efficiently in linear time.
//   • Idea: The Linear Sieve finds all prime numbers up to N in O(N) time by ensuring each composite number is marked exactly once by its least prime factor. It also computes the least prime factor for every number up to N.
//   • Invariants: The 'primes' list always contains all prime numbers found so far in increasing order.; lpf[i] stores the least prime factor of 'i' if 'i' is composite, or 'i' itself if 'i' is prime.
//   • Tips: Store the least prime factor (LPF) for each number in an array.; Maintain a dynamically growing list of primes found so far.
//   • Pitfalls: Incorrectly marking multiples can lead to O(N log log N) or worse complexity.; Forgetting to store the least prime factor can break the linear time guarantee.
// - Search the subarray with the maximum/minimum sum (array, prefix-sum, max-window)
//   • When to use: When needing to find the maximum or minimum sum of any contiguous subarray within a given array efficiently. It is particularly useful for problems requiring an O(N) solution.
//   • Idea: This algorithm finds the maximum (or minimum) sum of a contiguous subarray by iterating through the array, maintaining a running prefix sum, and tracking the minimum (or maximum) prefix sum encountered so far. It achieves an optimal O(N) time complexity with O(1) auxiliary space.
//   • Invariants: max_global_sum stores the maximum subarray sum found among all subarrays ending at or before the current element.; min_prefix_sum_value correctly tracks the minimum prefix sum encountered up to the previous element's prefix sum.
//   • Tips: Use a running sum variable instead of explicitly storing the entire prefix sum array.; Keep track of the minimum prefix sum encountered up to the current point.
//   • Pitfalls: Incorrectly initializing the minimum prefix sum (e.g., to INT_MAX instead of 0 or s[0]).; Off-by-one errors when calculating subarray sums using prefix sums (s[r] - s[l-1]).
//
// Notes:
// - Keep the given function signature unchanged.
// - Do not add custom input parsing or console I/O unless the template explicitly requires it; rely on parameters/return value only.
// - Use standard ECMAScript features supported by LeetCode (Node.js runtime); no external packages.
// - Be careful with number precision: JavaScript Number is double; use BigInt only when necessary and keep return type consistent with the problem requirements.
// - If you introduce helper functions, define them in the same file and avoid relying on global mutable state across test cases.

/**
 * @param {number[]} nums
 * @return {number[]}
 */
var majorityElement = function(nums) {
    let candidate1 = null, candidate2 = null, count1 = 0, count2 = 0;
    
    for (const num of nums) {
        if (num === candidate1) {
            count1++;
        } else if (num === candidate2) {
            count2++;
        } else if (count1 === 0) {
            candidate1 = num;
            count1 = 1;
        } else if (count2 === 0) {
            candidate2 = num;
            count2 = 1;
        } else {
            count1--;
            count2--;
        }
    }
    
    const result = [];
    count1 = 0;
    count2 = 0;
    
    for (const num of nums) {
        if (num === candidate1) count1++;
        else if (num === candidate2) count2++;
    }
    
    if (count1 > Math.floor(nums.length / 3)) result.push(candidate1);
    if (count2 > Math.floor(nums.length / 3)) result.push(candidate2);
    
    return result;
};
