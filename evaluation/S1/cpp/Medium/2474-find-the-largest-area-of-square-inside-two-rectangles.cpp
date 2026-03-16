// Source: https://leetcode.com/problems/find-the-largest-area-of-square-inside-two-rectangles/   |   Difficulty: Medium
//
// Problem Description:
// There exist n rectangles in a 2D plane with edges parallel to the x and y axis. You are given two 2D integer arrays bottomLeft and topRight where bottomLeft[i] = [a_i, b_i] and topRight[i] = [c_i, d_i] represent the bottom-left and top-right coordinates of the ith rectangle, respectively.
//
// You need to find the maximum area of a square that can fit inside the intersecting region of at least two rectangles. Return 0 if such a square does not exist.
//
// Example:
// Input: bottomLeft = [[1,1],[2,2],[3,1]], topRight = [[3,3],[4,4],[6,6]]
//
// Output: 1
//
// Explanation:
//
// A square with side length 1 can fit inside either the intersecting region of rectangles 0 and 1 or the intersecting region of rectangles 1 and 2. Hence the maximum area is 1. It can be shown that a square with a greater side length can not fit inside any intersecting region of two rectangles.
//
// Constraints:
// n == bottomLeft.length == topRight.length
// 	2 <= n <= 103
// 	bottomLeft[i].length == topRight[i].length == 2
// 	1 <= bottomLeft[i][0], bottomLeft[i][1] <= 107
// 	1 <= topRight[i][0], topRight[i][1] <= 107
// 	bottomLeft[i][0] < topRight[i][0]
// 	bottomLeft[i][1] < topRight[i][1]
//
// Helpful references (internal KB):
// - Half-plane intersection (geometry, simulation)
//   • When to use: When you need to find the common region defined by a set of half-planes, or determine if such a region exists. It's particularly useful for checking if the intersection is empty.
//   • Idea: This method finds the intersection of N half-planes by checking all O(N^2) pairwise line intersections. Each intersection point is then verified against all N half-planes, resulting in an O(N^3) time complexity.
//   • Invariants: Each candidate vertex is an intersection of two half-plane boundary lines.; Any point included in the final intersection region satisfies all given half-plane constraints.
//   • Tips: The vertices of the resulting convex polygon are always intersection points of the boundary lines.; Can be used to check if the intersection region is empty.
//   • Pitfalls: High time complexity of O(N^3) makes it inefficient for large N.; Numerical precision issues when calculating intersection points and checking containment.
// - Primality tests (number, enumeration, simulation)
//   • When to use: When you need to determine if a single number is prime, especially for numbers where trial division up to its square root is computationally feasible.
//   • Idea: A number is prime if it has no divisors other than 1 and itself. This method checks for primality by attempting to find a non-trivial divisor up to the square root of the given number, running in O(sqrt(N)) time.
//   • Invariants: No integer k in the range [2, current_divisor - 1] has been found to divide n.; The current value current_divisor is a candidate divisor being tested against n.
//   • Tips: Only check numbers between 2 and sqrt(n).; Handle 2 as a special case before iterating.
//   • Pitfalls: O(sqrt(N)) complexity can be too slow for very large numbers.; Incorrectly handling edge cases like 0, 1, or 2.
// - Search the subarray with the maximum/minimum sum (array, greedy, dp-1d)
//   • When to use: When you need to find the contiguous subarray within a one-dimensional array of numbers that has the largest or smallest sum, typically in linear time.
//   • Idea: This algorithm efficiently finds the maximum (or minimum) sum of a contiguous subarray by iterating through the array and maintaining a current sum, resetting it if it becomes detrimental. It operates in O(N) time complexity with O(1) space complexity.
//   • Invariants: `global_max` holds the maximum sum of any contiguous subarray encountered up to the current element.; `current_max` holds the maximum sum of a contiguous subarray ending at the current element.
//   • Tips: Initialize current and global maximums appropriately (e.g., to negative infinity or first element).; Adapt for minimum sum by resetting current sum if it becomes positive.
//   • Pitfalls: Failing to correctly initialize maximum/minimum sum variables.; Not handling arrays where all elements are negative (for max sum) or positive (for min sum).
//
// Notes:
// - Keep the given function signature unchanged.
// - Use standard C++ only; do NOT rely on non-standard extensions or platform-specific APIs.
// - Do not change input/output formats or return value semantics.
// - Conformance: Prefer modern standard C++ (C++11/14/17) features that are portable; avoid compiler-specific extensions (e.g., __int128 unless necessary and supported).
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
public:
    long long largestSquareArea(vector<vector<int>>& bottomLeft, vector<vector<int>>& topRight) {
        int n = bottomLeft.size();
        long long maxArea = 0;
        for (int i = 0; i < n; ++i) {
            for (int j = i + 1; j < n; ++j) {
                int x1 = max(bottomLeft[i][0], bottomLeft[j][0]);
                int y1 = max(bottomLeft[i][1], bottomLeft[j][1]);
                int x2 = min(topRight[i][0], topRight[j][0]);
                int y2 = min(topRight[i][1], topRight[j][1]);
                
                if (x1 < x2 && y1 < y2) {
                    int sideLength = min(x2 - x1, y2 - y1);
                    long long area = (long long)sideLength * sideLength;
                    if (area > maxArea) {
                        maxArea = area;
                    }
                }
            }
        }
        return maxArea;         
    }
};
