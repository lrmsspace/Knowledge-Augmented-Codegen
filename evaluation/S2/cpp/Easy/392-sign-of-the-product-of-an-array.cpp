// Source: https://leetcode.com/problems/sign-of-the-product-of-an-array/   |   Difficulty: Easy
//
// Problem Description:
// Implement a function signFunc(x) that returns:
//
//
// 	1 if x is positive.
// 	-1 if x is negative.
// 	0 if x is equal to 0.
//
//
// You are given an integer array nums. Let product be the product of all values in the array nums.
//
// Return signFunc(product).
//
// Example:
// Input: nums = [-1,-2,-3,-4,3,2,1]
// Output: 1
// Explanation: The product of all values in the array is 144, and signFunc(144) = 1
//
// Constraints:
// 1 <= nums.length <= 1000
// 	-100 <= nums[i] <= 100
//
// Helpful references (internal KB):
// - MEX (minimal excluded) of a sequence (array, enumeration)
//   • When to use: Use when you need to find the smallest non-negative integer that is not present in a given collection of numbers. It's often applied in problems involving game theory or combinatorial analysis.
//   • Idea: This algorithm finds the smallest non-negative integer not present in a given sequence or set. It typically involves marking present numbers and then iterating from zero to find the first unmarked number, achieving O(N) or O(N log N) complexity.
//   • Invariants: All non-negative integers less than the current candidate MEX value have been found in the input sequence.; The data structure used for presence tracking accurately reflects which non-negative integers up to a certain bound are present.
//   • Tips: Use a boolean array or hash set for efficient presence checking.; The MEX value is at most N (for N elements) if all numbers are distinct and within [0, N-1].
//   • Pitfalls: Forgetting to handle the case where all numbers from 0 to N-1 are present, meaning MEX is N.; Using an inefficient method for presence checking, leading to higher time complexity.
// - Search the subarray with the maximum/minimum sum (array, binary-search-answer)
//   • When to use: Use when the problem asks for the minimum or maximum value that satisfies a monotonic condition.
//   • Idea: This technique finds a target value within a range by repeatedly dividing the search interval in half, based on a monotonic condition. It typically achieves O(log N) time complexity for a search space of size N.
//   • Invariants: The optimal answer always lies within the current search range [low, high].; All values less than 'low' (for min search) or greater than 'high' (for max search) are known to be non-optimal.
//   • Tips: Clearly define the search space [low, high] for the answer.; Implement a `check` function that determines if a given `mid` value is a feasible solution.
//   • Pitfalls: Incorrectly defining the search range [low, high] for the answer.; Errors in the `check` function leading to incorrect monotonicity or logic.
// - Oriented area of a triangle (geometry, number, simulation)
//   • When to use: Use when determining the orientation of three 2D points (clockwise, counterclockwise, or collinear) or calculating the signed area of a triangle formed by them. It's crucial for geometric algorithms like convex hull construction and point-in-polygon tests.
//   • Idea: Calculates the signed area of a triangle defined by three 2D points, indicating their orientation relative to each other. A positive sign typically means counterclockwise, negative means clockwise, and zero indicates collinearity.
//   • Invariants: The sign of the result correctly indicates the orientation of p1, p2, p3 (e.g., positive for counter-clockwise).; If the points are collinear, the calculated oriented area is exactly zero.
//   • Tips: The sign of the result directly indicates the orientation of the points.; The absolute value of the result gives the standard unsigned area of the triangle.
//   • Pitfalls: Floating-point precision issues can lead to incorrect collinearity checks or orientation.; Inconsistent definitions of 'clockwise' vs. 'counterclockwise' can flip the sign interpretation.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use standard C++ only; do NOT rely on non-standard extensions or platform-specific APIs.
// - Do not change input/output formats or return value semantics.
// - Conformance: Prefer modern standard C++ (C++11/14/17) features that are portable; avoid compiler-specific extensions (e.g., __int128 unless necessary and supported).
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
public:
    int arraySign(vector<int>& nums) {
        int sign = 1;
        for (int num : nums) {
            if (num == 0) {
                return 0; // Product will be zero if any element is zero
            } else if (num < 0) {
                sign *= -1; // Flip the sign for negative numbers
            }
        }
        return sign; // Return the final sign of the product            
    }
};
