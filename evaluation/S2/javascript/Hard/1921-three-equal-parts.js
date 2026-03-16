// Source: https://leetcode.com/problems/three-equal-parts/   |   Difficulty: Hard
//
// Problem Description:
// You are given an array arr which consists of only zeros and ones, divide the array into three non-empty parts such that all of these parts represent the same binary value.
//
// If it is possible, return any [i, j] with i + 1 < j, such that:
//
//
// 	arr[0], arr[1], ..., arr[i] is the first part,
// 	arr[i + 1], arr[i + 2], ..., arr[j - 1] is the second part, and
// 	arr[j], arr[j + 1], ..., arr[arr.length - 1] is the third part.
// 	All three parts have equal binary values.
//
//
// If it is not possible, return [-1, -1].
//
// Note that the entire part is used when considering what binary value it represents. For example, [1,1,0] represents 6 in decimal, not 3. Also, leading zeros are allowed, so [0,1,1] and [1,1] represent the same value.
//
// Example:
// Input: arr = [1,0,1,0,1]
// Output: [0,3]
//
// Constraints:
// 3 <= arr.length <= 3 * 104
// 	arr[i] is 0 or 1
//
// Helpful references (internal KB):
// - Search the subarray with the maximum/minimum sum (array, binary-search-answer)
//   • When to use: Use when the problem asks for the minimum or maximum value that satisfies a monotonic condition.
//   • Idea: This technique finds a target value within a range by repeatedly dividing the search interval in half, based on a monotonic condition. It typically achieves O(log N) time complexity for a search space of size N.
//   • Invariants: The optimal answer always lies within the current search range [low, high].; All values less than 'low' (for min search) or greater than 'high' (for max search) are known to be non-optimal.
//   • Tips: Clearly define the search space [low, high] for the answer.; Implement a `check` function that determines if a given `mid` value is a feasible solution.
//   • Pitfalls: Incorrectly defining the search range [low, high] for the answer.; Errors in the `check` function leading to incorrect monotonicity or logic.
// - Non-negative Integers without Consecutive Ones (number, enumeration, simulation)
//   • When to use: Use when counting numbers up to a given limit that satisfy a specific bit pattern constraint, particularly when the limit is small enough for direct iteration and checking.
//   • Idea: This approach iterates through every non-negative integer from 0 up to the given limit num. For each integer, it simulates checking its binary representation to determine if it contains any two consecutive '1's.
//   • Invariants: count stores the number of integers k (where 0 <= k < i) that do not have consecutive ones.; All integers j such that 0 <= j < i have been processed.
//   • Tips: Use bitwise operations like (i & (i >> 1)) to efficiently detect consecutive ones.; Remember to include 0 in the count as it satisfies the condition (no consecutive ones).
//   • Pitfalls: Performance degradation for large num due to linear scan and per-number bit check.; Incorrectly handling the upper bound of the iteration (e.g., i < num instead of i <= num).
// - Finding intersection of two segments (geometry, array, enumeration, two-pointers)
//   • When to use: Use this to determine if two line segments intersect and, if so, find the intersection point or the overlapping segment. It is useful for collision detection and computational geometry problems.
//   • Idea: This algorithm determines the intersection of two line segments by first handling parallel or collinear cases, then calculating the intersection point if lines are not parallel. It typically involves O(1) time complexity for a fixed number of segments.
//   • Invariants: Before checking for intersection, both segments are valid (non-degenerate or single points).; For non-parallel lines, the intersection point of their infinite extensions is uniquely determined.
//   • Tips: Handle general line intersection using parametric equations or cross products.; Project segments onto X and Y axes to check for overlap in collinear cases.
//   • Pitfalls: Incorrectly handling edge cases like segments sharing an endpoint or being single points.; Failing to distinguish between parallel and collinear segments.
//
// Notes:
// - Keep the given function signature unchanged.
// - Do not add custom input parsing or console I/O unless the template explicitly requires it; rely on parameters/return value only.
// - Use standard ECMAScript features supported by LeetCode (Node.js runtime); no external packages.
// - Be careful with number precision: JavaScript Number is double; use BigInt only when necessary and keep return type consistent with the problem requirements.
// - If you introduce helper functions, define them in the same file and avoid relying on global mutable state across test cases.

/**
 * @param {number[]} arr
 * @return {number[]}
 */
var threeEqualParts = function(arr) {
    const n = arr.length;
    const totalOnes = arr.reduce((sum, val) => sum + val, 0);
    
    if (totalOnes % 3 !== 0) {
        return [-1, -1];
    }
    
    const onesPerPart = totalOnes / 3;
    if (onesPerPart === 0) {
        return [0, n - 1];
    }
    
    let first = -1, second = -1, third = -1;
    let count = 0;
    
    for (let i = 0; i < n; i++) {
        if (arr[i] === 1) {
            count++;
            if (count === onesPerPart && first === -1) {
                first = i;
            } else if (count === 2 * onesPerPart && second === -1) {
                second = i;
            } else if (count === 3 * onesPerPart && third === -1) {
                third = i;
                break;
            }
        }
    }
    
    // Check if the parts are equal
    let i = first + 1, j = second + 1, k = third + 1;
    while (k < n && arr[i] === arr[j] && arr[j] === arr[k]) {
        i++;
        j++;
        k++;
    }
    
    if (k < n) {
        return [-1, -1];
    }
    
    return [first, second + 1];
};
