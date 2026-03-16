// Source: https://leetcode.com/problems/number-of-arithmetic-triplets/   |   Difficulty: Easy
//
// Problem Description:
// You are given a 0-indexed, strictly increasing integer array nums and a positive integer diff. A triplet (i, j, k) is an arithmetic triplet if the following conditions are met:
//
//
// 	i < j < k,
// 	nums[j] - nums[i] == diff, and
// 	nums[k] - nums[j] == diff.
//
//
// Return the number of unique arithmetic triplets.
//
// Example:
// Input: nums = [0,1,4,6,7,10], diff = 3
// Output: 2
// Explanation:
// (1, 2, 4) is an arithmetic triplet because both 7 - 4 == 3 and 4 - 1 == 3.
// (2, 4, 5) is an arithmetic triplet because both 10 - 7 == 3 and 7 - 4 == 3.
//
// Constraints:
// 3 <= nums.length <= 200
// 	0 <= nums[i] <= 200
// 	1 <= diff <= 50
// 	nums is strictly increasing.
//
// Helpful references (internal KB):
// - Non-negative Integers without Consecutive Ones (number, enumeration, simulation)
//   • When to use: Use when counting numbers up to a given limit that satisfy a specific bit pattern constraint, particularly when the limit is small enough for direct iteration and checking.
//   • Idea: This approach iterates through every non-negative integer from 0 up to the given limit num. For each integer, it simulates checking its binary representation to determine if it contains any two consecutive '1's.
//   • Invariants: count stores the number of integers k (where 0 <= k < i) that do not have consecutive ones.; All integers j such that 0 <= j < i have been processed.
//   • Tips: Use bitwise operations like (i & (i >> 1)) to efficiently detect consecutive ones.; Remember to include 0 in the count as it satisfies the condition (no consecutive ones).
//   • Pitfalls: Performance degradation for large num due to linear scan and per-number bit check.; Incorrectly handling the upper bound of the iteration (e.g., i < num instead of i <= num).
// - Sqrt Decomposition (array, enumeration, difference-array)
//   • When to use: Efficiently calculate sums or properties over various ranges in a static array. Useful for many range queries or when combining range updates with point queries.
//   • Idea: Prefix sums allow O(1) range sum queries after O(N) preprocessing. Difference arrays enable O(1) range updates and O(N) point queries after O(N) reconstruction.
//   • Invariants: The prefix sum array P[i] stores the sum of elements from A[0] to A[i-1].; The difference array D[i] stores A[i] - A[i-1] (for i > 0).
//   • Tips: Precompute prefix sums to answer range sum queries in constant time.; Use a difference array to apply range updates efficiently.
//   • Pitfalls: Off-by-one errors in range boundaries for prefix sums.; Forgetting to initialize the difference array correctly (e.g., diff[0] = arr[0] for 0-indexed).
// - Linear Diophantine Equation (number, enumeration)
//   • When to use: Use when you need to find all integer solutions (x, y) for a linear equation of the form ax + by = c, or to determine if such solutions exist. It is also applicable for enumerating solutions within specified bounds.
//   • Idea: This method finds all integer solutions (x, y) to the linear equation ax + by = c. It utilizes the Extended Euclidean Algorithm to find a particular solution, then generates the general solution set using properties of the greatest common divisor in O(log(min(a,b))) time.
//   • Invariants: The equation a * x + b * y = c holds true for any generated integer solution (x, y).; For integer solutions to exist, c must be perfectly divisible by gcd(a, b).
//   • Tips: Always check if c is divisible by gcd(a, b); if not, no integer solutions exist.; Use the Extended Euclidean Algorithm to find a particular solution (x0, y0) for ax + by = gcd(a, b).
//   • Pitfalls: Forgetting to verify that c is a multiple of gcd(a, b) before proceeding.; Incorrectly scaling the particular solution obtained from the Extended Euclidean Algorithm.
//
// Notes:
// - Keep the given function signature unchanged.
// - Do not add custom input parsing or console I/O unless the template explicitly requires it; rely on parameters/return value only.
// - Use standard ECMAScript features supported by LeetCode (Node.js runtime); no external packages.
// - Be careful with number precision: JavaScript Number is double; use BigInt only when necessary and keep return type consistent with the problem requirements.
// - If you introduce helper functions, define them in the same file and avoid relying on global mutable state across test cases.

/**
 * @param {number[]} nums
 * @param {number} diff
 * @return {number}
 */
var arithmeticTriplets = function(nums, diff) {
    const numSet = new Set(nums);
    let tripletCount = 0;
    for (const num of nums) {
        if (numSet.has(num + diff) && numSet.has(num + 2 * diff)) {
            tripletCount++;
        }
    }
    return tripletCount;
};