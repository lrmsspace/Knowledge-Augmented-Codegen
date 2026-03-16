// Source: https://leetcode.com/problems/destroy-sequential-targets/   |   Difficulty: Medium
//
// Problem Description:
// You are given a 0-indexed array nums consisting of positive integers, representing targets on a number line. You are also given an integer space.
//
// You have a machine which can destroy targets. Seeding the machine with some nums[i] allows it to destroy all targets with values that can be represented as nums[i] + c * space, where c is any non-negative integer. You want to destroy the maximum number of targets in nums.
//
// Return the minimum value of nums[i] you can seed the machine with to destroy the maximum number of targets.
//
// Example:
// Input: nums = [3,7,8,1,1,5], space = 2
// Output: 1
// Explanation: If we seed the machine with nums[3], then we destroy all targets equal to 1,3,5,7,9,... 
// In this case, we would destroy 5 total targets (all except for nums[2]). 
// It is impossible to destroy more than 5 targets, so we return nums[3].
//
// Constraints:
// 1 <= nums.length <= 105
// 	1 <= nums[i] <= 109
// 	1 <= space <= 109
//
// Helpful references (internal KB):
// - MEX (minimal excluded) of a sequence (array, enumeration)
//   • When to use: Use when you need to find the smallest non-negative integer that is not present in a given collection of numbers. It's often applied in problems involving game theory or combinatorial analysis.
//   • Idea: This algorithm finds the smallest non-negative integer not present in a given sequence or set. It typically involves marking present numbers and then iterating from zero to find the first unmarked number, achieving O(N) or O(N log N) complexity.
//   • Invariants: All non-negative integers less than the current candidate MEX value have been found in the input sequence.; The data structure used for presence tracking accurately reflects which non-negative integers up to a certain bound are present.
//   • Tips: Use a boolean array or hash set for efficient presence checking.; The MEX value is at most N (for N elements) if all numbers are distinct and within [0, N-1].
//   • Pitfalls: Forgetting to handle the case where all numbers from 0 to N-1 are present, meaning MEX is N.; Using an inefficient method for presence checking, leading to higher time complexity.
// - Knapsack Problem (array, deque, knapsack, dp-1d, monotonic-queue)
//   • When to use: When optimizing the knapsack problem where multiple identical items are available, reducing the DP transition from O(max_count) to O(1) using a sliding window maximum technique.
//   • Idea: The Knapsack problem involves selecting items with weights and values to maximize total value within a capacity constraint. This specific variant, often for multiple identical items, uses dynamic programming optimized with a monotonic queue to achieve an O(NW) time complexity.
//   • Invariants: `dp[c]` represents the maximum value achievable for capacity `c` considering all items processed up to the current iteration.; For each remainder `y`, the deque stores indices `k` such that `G_{k, y}` values are monotonically decreasing from front to back.
//   • Tips: Carefully define DP states, often `dp[c]` for the maximum value at capacity `c`.; For multiple items, iterate through items and then capacities, or vice-versa, considering `w_i` remainder groups.
//   • Pitfalls: Incorrectly handling item counts or capacity limits in DP transitions.; Off-by-one errors in monotonic queue window management, leading to incorrect maximums.
// - Modular Multiplicative Inverse (number, mod-exp, gcd)
//   • When to use: When you need to perform division in modular arithmetic, or find an integer `x` such that `a * x` is congruent to `1` modulo `m`, provided `a` and `m` are coprime.
//   • Idea: Calculates the modular multiplicative inverse of `a` modulo `m`, which is an integer `x` such that `(a * x) % m == 1`. It can be found using the Extended Euclidean Algorithm or binary exponentiation (Fermat's Little Theorem for prime `m`, Euler's Totient Theorem for general coprime `m`).
//   • Invariants: The greatest common divisor of `a` and `m` must be 1 for the inverse to exist.; The final computed inverse `x` satisfies the congruence `(a * x) % m == 1`.
//   • Tips: Ensure `a` and `m` are coprime (gcd(a, m) = 1) for the inverse to exist.; For prime modulus `m`, `a^(m-2) % m` is a simpler formula using Fermat's Little Theorem.
//   • Pitfalls: Forgetting to handle negative results from the Extended Euclidean Algorithm by adding `m`.; Applying Fermat's Little Theorem when `m` is not a prime number.
//
// Notes:
// - Keep the given function signature unchanged.
// - Do not add custom input parsing or console I/O unless the template explicitly requires it; rely on parameters/return value only.
// - Use standard ECMAScript features supported by LeetCode (Node.js runtime); no external packages.
// - Be careful with number precision: JavaScript Number is double; use BigInt only when necessary and keep return type consistent with the problem requirements.
// - If you introduce helper functions, define them in the same file and avoid relying on global mutable state across test cases.

/**
 * @param {number[]} nums
 * @param {number} space
 * @return {number}
 */
var destroyTargets = function(nums, space) {
    const countMap = new Map();
    let maxCount = 0;
    for (const num of nums) {
        const remainder = num % space;
        const count = (countMap.get(remainder) || 0) + 1;
        countMap.set(remainder, count);
        maxCount = Math.max(maxCount, count);
    }
    let minSeed = Infinity;
    for (const [remainder, count] of countMap.entries()) {
        if (count === maxCount) {
            minSeed = Math.min(minSeed, remainder);
        }
    }
    return minSeed;
};
