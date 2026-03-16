// Source: https://leetcode.com/problems/type-of-triangle/   |   Difficulty: Easy
//
// Problem Description:
// You are given a 0-indexed integer array nums of size 3 which can form the sides of a triangle.
//
//
// 	A triangle is called equilateral if it has all sides of equal length.
// 	A triangle is called isosceles if it has exactly two sides of equal length.
// 	A triangle is called scalene if all its sides are of different lengths.
//
//
// Return a string representing the type of triangle that can be formed or "none" if it cannot form a triangle.
//
// Example:
// Input: nums = [3,3,3]
// Output: "equilateral"
// Explanation: Since all the sides are of equal length, therefore, it will form an equilateral triangle.
//
// Constraints:
// nums.length == 3
// 	1 <= nums[i] <= 100
//
// Helpful references (internal KB):
// - Non-negative Integers without Consecutive Ones (number, enumeration, simulation)
//   • When to use: Use when counting numbers up to a given limit that satisfy a specific bit pattern constraint, particularly when the limit is small enough for direct iteration and checking.
//   • Idea: This approach iterates through every non-negative integer from 0 up to the given limit num. For each integer, it simulates checking its binary representation to determine if it contains any two consecutive '1's.
//   • Invariants: count stores the number of integers k (where 0 <= k < i) that do not have consecutive ones.; All integers j such that 0 <= j < i have been processed.
//   • Tips: Use bitwise operations like (i & (i >> 1)) to efficiently detect consecutive ones.; Remember to include 0 in the count as it satisfies the condition (no consecutive ones).
//   • Pitfalls: Performance degradation for large num due to linear scan and per-number bit check.; Incorrectly handling the upper bound of the iteration (e.g., i < num instead of i <= num).
// - Binomial Coefficients (number, enumeration)
//   • When to use: Use when needing to calculate multiple binomial coefficients or when a single coefficient is required and N and K are not excessively large, allowing for table precomputation.
//   • Idea: This method computes binomial coefficients C(n, k) using Pascal's recurrence relation C(n, k) = C(n-1, k-1) + C(n-1, k), typically building a table. It has a time complexity of O(N*K) or O(N^2) for building the full triangle up to N.
//   • Invariants: C[i][0] is always 1 for any row i.; C[i][i] is always 1 for any row i.
//   • Tips: Intermediate results for Pascal's Triangle never exceed the final answer, simplifying overflow checks if not using modular arithmetic.; Each new table element requires only one addition, making it computationally efficient per element.
//   • Pitfalls: Building the entire Pascal's Triangle for a single C(N, K) can be slow for large N and K, as it computes many unnecessary values.; Directly computing C(N, K) using factorials can lead to overflow issues for large N, even if the final result fits.
// - Basic Geometry (geometry, matrix, number, simulation)
//   • When to use: Use when solving problems involving fundamental geometric entities like points, lines, and planes, or when performing basic vector operations to determine relationships or intersections.
//   • Idea: This card covers foundational concepts in 2D and 3D geometry, including vector products and their applications in defining lines, planes, and calculating orientations or intersections. It primarily involves algebraic manipulation of vector equations, typically with O(1) complexity for basic operations on fixed-dimension vectors.
//   • Invariants: Vector operations (cross, triple products) maintain their geometric and algebraic properties.; A line defined by two points or a point and direction vector remains consistent.
//   • Tips: Understand the geometric interpretation of vector products.; Use vector equations to define lines and planes concisely.
//   • Pitfalls: Confusing pseudo-scalar product with dot product.; Incorrectly applying cross product in 2D contexts.
//
// Notes:
// - Keep the given method signatures unchanged.
// - Use only Java standard library (`java.*`); no external dependencies.
// - Do not change input/output formats or return value semantics.
// - Conformance: single public class 'Solution'; no 'package' statement; place any extra types as static inner classes.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
    public String triangleType(int[] nums) {
        int a = nums[0], b = nums[1], c = nums[2];
        if (a + b <= c || a + c <= b || b + c <= a) {
            return "none";
        } else if (a == b && b == c) {
            return "equilateral";
        } else if (a == b || b == c || a == c) {
            return "isosceles";
        } else {
            return "scalene";
        }           
    }
}
