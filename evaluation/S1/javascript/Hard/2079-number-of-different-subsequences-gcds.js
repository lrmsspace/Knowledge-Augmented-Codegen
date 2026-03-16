// Source: https://leetcode.com/problems/number-of-different-subsequences-gcds/   |   Difficulty: Hard
//
// Problem Description:
// You are given an array nums that consists of positive integers.
//
// The GCD of a sequence of numbers is defined as the greatest integer that divides all the numbers in the sequence evenly.
//
//
// 	For example, the GCD of the sequence [4,6,16] is 2.
//
//
// A subsequence of an array is a sequence that can be formed by removing some elements (possibly none) of the array.
//
//
// 	For example, [2,5,10] is a subsequence of [1,2,1,2,4,1,5,10].
//
//
// Return the number of different GCDs among all non-empty subsequences of nums.
//
// Example:
// Input: nums = [6,10,3]
// Output: 5
// Explanation: The figure shows all the non-empty subsequences and their GCDs.
// The different GCDs are 6, 10, 3, 2, and 1.
//
// Constraints:
// 1 <= nums.length <= 105
// 	1 <= nums[i] <= 2 * 105
//
// Helpful references (internal KB):
// - Non-negative Integers without Consecutive Ones (number, enumeration, simulation)
//   • When to use: Use when counting numbers up to a given limit that satisfy a specific bit pattern constraint, particularly when the limit is small enough for direct iteration and checking.
//   • Idea: This approach iterates through every non-negative integer from 0 up to the given limit num. For each integer, it simulates checking its binary representation to determine if it contains any two consecutive '1's.
//   • Invariants: count stores the number of integers k (where 0 <= k < i) that do not have consecutive ones.; All integers j such that 0 <= j < i have been processed.
//   • Tips: Use bitwise operations like (i & (i >> 1)) to efficiently detect consecutive ones.; Remember to include 0 in the count as it satisfies the condition (no consecutive ones).
//   • Pitfalls: Performance degradation for large num due to linear scan and per-number bit check.; Incorrectly handling the upper bound of the iteration (e.g., i < num instead of i <= num).
// - Generating all K-combinations (bitset, enumeration)
//   • When to use: When all subsets of a fixed size K need to be generated, either in lexicographical order or such that successive combinations differ by exactly one element.
//   • Idea: This algorithm enumerates all K-combinations from a set, either in lexicographical order or using a Gray code approach where adjacent combinations differ by a single element. It typically runs in O(N choose K) time, generating each combination in O(K) or O(1) amortized time.
//   • Invariants: Each generated combination contains exactly K distinct elements.; All elements within a combination are unique and from the original set.
//   • Tips: For lexicographical generation, find the rightmost element that can be incremented without exceeding its maximum possible value.; After incrementing an element, set all subsequent elements to their minimum valid values.
//   • Pitfalls: Incorrectly handling boundary conditions for the rightmost element or its maximum value.; Off-by-one errors when assigning subsequent elements after an increment.
// - Extended Euclidean Algorithm (number, gcd, simulation)
//   • When to use: Use this algorithm to find integer coefficients x and y that satisfy Bézout's identity (ax + by = gcd(a,b)). It is also essential for computing modular multiplicative inverses and solving linear Diophantine equations.
//   • Idea: The Extended Euclidean Algorithm computes the greatest common divisor (GCD) of two integers 'a' and 'b', and simultaneously finds integer coefficients 'x' and 'y' such that 'ax + by = gcd(a,b)'. It operates in O(log(min(a,b))) time complexity.
//   • Invariants: x * (initial a) + y * (initial b) = current_a_value; x_1 * (initial a) + y_1 * (initial b) = current_b_value
//   • Tips: Can be implemented using either a recursive or an iterative approach.; The algorithm correctly handles negative integer inputs.
//   • Pitfalls: Incorrectly defining base cases in recursive implementations can lead to errors.; Potential for integer overflow if coefficients x or y become extremely large, though uncommon.
//
// Notes:
// - Keep the given function signature unchanged.
// - Do not add custom input parsing or console I/O unless the template explicitly requires it; rely on parameters/return value only.
// - Use standard ECMAScript features supported by LeetCode (Node.js runtime); no external packages.
// - Be careful with number precision: JavaScript Number is double; use BigInt only when necessary and keep return type consistent with the problem requirements.
// - If you introduce helper functions, define them in the same file and avoid relying on global mutable state across test cases.

/**
 * @param {number[]} nums
 * @return {number}
 */
var countDifferentSubsequenceGCDs = function(nums) {
    const maxNum = Math.max(...nums);
    const numSet = new Set(nums);
    let count = 0;

    for (let gcdCandidate = 1; gcdCandidate <= maxNum; gcdCandidate++) {
        let currentGCD = 0;
        for (let multiple = gcdCandidate; multiple <= maxNum; multiple += gcdCandidate) {
            if (numSet.has(multiple)) {
                currentGCD = gcd(currentGCD, multiple);
            }
        }
        if (currentGCD === gcdCandidate) {
            count++;
        }
    }

    return count;
};
