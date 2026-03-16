// Source: https://leetcode.com/problems/n-repeated-element-in-size-2n-array/   |   Difficulty: Easy
//
// Problem Description:
// You are given an integer array nums with the following properties:
//
//
// 	nums.length == 2 * n.
// 	nums contains n + 1 unique elements.
// 	Exactly one element of nums is repeated n times.
//
//
// Return the element that is repeated n times.
//
// Example:
// Input: nums = [1,2,3,3]
// Output: 3
//
// Constraints:
// 2 <= n <= 5000
// 	nums.length == 2 * n
// 	0 <= nums[i] <= 104
// 	nums contains n + 1 unique elements and one of them is repeated exactly n times.
//
// Helpful references (internal KB):
// - Non-negative Integers without Consecutive Ones (number, enumeration, simulation)
//   • When to use: Use when counting numbers up to a given limit that satisfy a specific bit pattern constraint, particularly when the limit is small enough for direct iteration and checking.
//   • Idea: This approach iterates through every non-negative integer from 0 up to the given limit num. For each integer, it simulates checking its binary representation to determine if it contains any two consecutive '1's.
//   • Invariants: count stores the number of integers k (where 0 <= k < i) that do not have consecutive ones.; All integers j such that 0 <= j < i have been processed.
//   • Tips: Use bitwise operations like (i & (i >> 1)) to efficiently detect consecutive ones.; Remember to include 0 in the count as it satisfies the condition (no consecutive ones).
//   • Pitfalls: Performance degradation for large num due to linear scan and per-number bit check.; Incorrectly handling the upper bound of the iteration (e.g., i < num instead of i <= num).
// - Finding repetitions (string, array, z-function, enumeration)
//   • When to use: This algorithm efficiently finds all repetitions (periodic substrings) within a given string by combining divide-and-conquer with the Z-function. It is particularly useful for identifying overlapping or crossing periodic patterns.
//   • Idea: The Main-Lorentz algorithm finds all repetitions in a string by recursively splitting it into halves and identifying 'crossing repetitions' using the Z-function. This approach achieves an optimal O(N log N) time complexity.
//   • Invariants: For any fixed `cntr` position, all identified crossing repetitions have a total length of $2 	imes (|u| - cntr)$.; The segment $u[cntr - k_1 	ext{ to } cntr - 1]$ is identical to $u[|u| - k_1 	ext{ to } |u| - 1]$.
//   • Tips: Employ divide-and-conquer to break the problem into subproblems for repetitions within halves and crossing repetitions.; Utilize the Z-function to compute $k_1$ and $k_2$ values in O(1) for each `cntr` position, speeding up crossing repetition detection.
//   • Pitfalls: Correctly identifying and defining 'crossing repetitions' is the most intricate part of the algorithm.; Careful implementation of the Z-function for both the original and reversed string segments is crucial.
// - Linear Diophantine Equation (number, enumeration)
//   • When to use: Use when you need to find all integer solutions (x, y) for a linear equation of the form ax + by = c, or to determine if such solutions exist. It is also applicable for enumerating solutions within specified bounds.
//   • Idea: This method finds all integer solutions (x, y) to the linear equation ax + by = c. It utilizes the Extended Euclidean Algorithm to find a particular solution, then generates the general solution set using properties of the greatest common divisor in O(log(min(a,b))) time.
//   • Invariants: The equation a * x + b * y = c holds true for any generated integer solution (x, y).; For integer solutions to exist, c must be perfectly divisible by gcd(a, b).
//   • Tips: Always check if c is divisible by gcd(a, b); if not, no integer solutions exist.; Use the Extended Euclidean Algorithm to find a particular solution (x0, y0) for ax + by = gcd(a, b).
//   • Pitfalls: Forgetting to verify that c is a multiple of gcd(a, b) before proceeding.; Incorrectly scaling the particular solution obtained from the Extended Euclidean Algorithm.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use the C standard library only; no external packages.
// - Do not change input/output formats or return value semantics.
// - Conformance: ISO C (C89/C99/C11). Do NOT use GNU C extensions (nested functions, statement expressions, typeof, __auto_type, etc.). Avoid VLAs and non-standard builtins.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

int repeatedNTimes(int* nums, int numsSize) {
    int counts[10001] = {0}; // Since 0 <= nums[i] <= 10^4
    for (int i = 0; i < numsSize; i++) {
        counts[nums[i]]++;
        if (counts[nums[i]] > 1) {
            return nums[i];
        }
    }
    return -1; // This line should never be reached given the problem constraints       
}
