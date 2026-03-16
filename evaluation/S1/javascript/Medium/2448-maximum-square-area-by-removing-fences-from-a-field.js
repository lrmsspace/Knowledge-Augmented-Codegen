// Source: https://leetcode.com/problems/maximum-square-area-by-removing-fences-from-a-field/   |   Difficulty: Medium
//
// Problem Description:
// There is a large (m - 1) x (n - 1) rectangular field with corners at (1, 1) and (m, n) containing some horizontal and vertical fences given in arrays hFences and vFences respectively.
//
// Horizontal fences are from the coordinates (hFences[i], 1) to (hFences[i], n) and vertical fences are from the coordinates (1, vFences[i]) to (m, vFences[i]).
//
// Return the maximum area of a square field that can be formed by removing some fences (possibly none) or -1 if it is impossible to make a square field.
//
// Since the answer may be large, return it modulo 109 + 7.
//
// Note: The field is surrounded by two horizontal fences from the coordinates (1, 1) to (1, n) and (m, 1) to (m, n) and two vertical fences from the coordinates (1, 1) to (m, 1) and (1, n) to (m, n). These fences cannot be removed.
//
// Example:
// Input: m = 4, n = 3, hFences = [2,3], vFences = [2]
// Output: 4
// Explanation: Removing the horizontal fence at 2 and the vertical fence at 2 will give a square field of area 4.
//
// Constraints:
// 3 <= m, n <= 109
// 	1 <= hFences.length, vFences.length <= 600
// 	1 < hFences[i] < m
// 	1 < vFences[i] < n
// 	hFences and vFences are unique.
//
// Helpful references (internal KB):
// - Convex Hull construction (geometry, array, enumeration)
//   • When to use: Use when you need to find the smallest convex polygon that encloses a given set of points in a plane. It is fundamental for various geometric algorithms and optimization problems.
//   • Idea: Convex hull construction identifies the subset of points that form the vertices of the smallest convex polygon containing all given points. Common algorithms achieve this in O(N log N) time complexity.
//   • Invariants: The sequence of points currently forming the hull maintains a convex property.; All points considered up to the current iteration are either part of the hull or lie within the polygon defined by the hull.
//   • Tips: Sort points by X-coordinate (and Y for ties) as a common preprocessing step.; Consider algorithms like Graham Scan or Monotone Chain for efficiency.
//   • Pitfalls: Floating point precision issues can lead to incorrect orientation calculations.; Incorrectly handling collinear points can result in non-minimal hulls or errors.
// - Binary Exponentiation by Factoring (number, mod-exp)
//   • When to use: When computing a number raised to a very large power modulo another number efficiently. It is also applicable when specific properties of the base or modulus allow for specialized bitwise optimizations.
//   • Idea: Binary exponentiation (also known as exponentiation by squaring) computes a^b mod m by leveraging the binary representation of the exponent b. This method significantly reduces the number of multiplications from O(b) to O(log b), achieving O(log b) time complexity.
//   • Invariants: (original_base^original_exponent) % m == (current_base^current_exponent * accumulated_result) % m; current_exponent is always non-negative and strictly decreases towards zero.
//   • Tips: Use long long for intermediate products to prevent overflow before taking modulo.; Apply the modulo operation after each multiplication to keep numbers small.
//   • Pitfalls: Integer overflow if intermediate products are not reduced modulo m frequently enough.; Incorrectly handling the exponent 0 or negative exponents (if applicable).
// - Generating all K-combinations (array, enumeration, greedy)
//   • When to use: Use this when you need to iterate through all possible subsets of a fixed size K from a larger set, especially when a specific order like lexicographical is required.
//   • Idea: This algorithm systematically generates all unique combinations of K elements from a set of N elements. It typically proceeds in lexicographical order, allowing for efficient enumeration of all C(N, K) possibilities.
//   • Invariants: The current combination C is always sorted: C[0] < C[1] < ... < C[K-1].; All elements C[i] are distinct and within the range [0, N-1] (assuming 0-indexed).
//   • Tips: Start with the smallest lexicographical combination (e.g., {1, 2, ..., K}).; To find the next combination, locate the rightmost element that can be incremented.
//   • Pitfalls: Incorrectly handling boundary conditions when incrementing elements.; Duplicating combinations if not careful with the increment logic.
//
// Notes:
// - Keep the given function signature unchanged.
// - Do not add custom input parsing or console I/O unless the template explicitly requires it; rely on parameters/return value only.
// - Use standard ECMAScript features supported by LeetCode (Node.js runtime); no external packages.
// - Be careful with number precision: JavaScript Number is double; use BigInt only when necessary and keep return type consistent with the problem requirements.
// - If you introduce helper functions, define them in the same file and avoid relying on global mutable state across test cases.

/**
 * @param {number} m
 * @param {number} n
 * @param {number[]} hFences
 * @param {number[]} vFences
 * @return {number}
 */
var maximizeSquareArea = function(m, n, hFences, vFences) {
    hFences.push(1, m); // Add the fixed horizontal fences
    vFences.push(1, n); // Add the fixed vertical fences
    hFences.sort((a, b) => a - b);
    vFences.sort((a, b) => a - b);
    
    let maxHGap = 0;
    for (let i = 1; i < hFences.length; i++) {
        maxHGap = Math.max(maxHGap, hFences[i] - hFences[i - 1]);
    }
    
    let maxVGap = 0;
    for (let i = 1; i < vFences.length; i++) {
        maxVGap = Math.max(maxVGap, vFences[i] - vFences[i - 1]);
    }
    
    const maxSquareSide = Math.min(maxHGap, maxVGap);
    return (maxSquareSide * maxSquareSide) % (1e9 + 7);
};
