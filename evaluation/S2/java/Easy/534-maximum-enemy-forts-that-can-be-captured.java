// Source: https://leetcode.com/problems/maximum-enemy-forts-that-can-be-captured/   |   Difficulty: Easy
//
// Problem Description:
// You are given a 0-indexed integer array forts of length n representing the positions of several forts. forts[i] can be -1, 0, or 1 where:
//
//
// 	-1 represents there is no fort at the ith position.
// 	0 indicates there is an enemy fort at the ith position.
// 	1 indicates the fort at the ith the position is under your command.
//
//
// Now you have decided to move your army from one of your forts at position i to an empty position j such that:
//
//
// 	0 <= i, j <= n - 1
// 	The army travels over enemy forts only. Formally, for all k where min(i,j) < k < max(i,j), forts[k] == 0.
//
//
// While moving the army, all the enemy forts that come in the way are captured.
//
// Return the maximum number of enemy forts that can be captured. In case it is impossible to move your army, or you do not have any fort under your command, return 0.
//
// Example:
// Input: forts = [1,0,0,-1,0,0,0,0,1]
// Output: 4
// Explanation:
// - Moving the army from position 0 to position 3 captures 2 enemy forts, at 1 and 2.
// - Moving the army from position 8 to position 3 captures 4 enemy forts.
// Since 4 is the maximum number of enemy forts that can be captured, we return 4.
//
// Constraints:
// 1 <= forts.length <= 1000
// 	-1 <= forts[i] <= 1
//
// Helpful references (internal KB):
// - Finding the largest zero submatrix (array, stack, monotonic-stack, max-window)
//   • When to use: This algorithm is used to find the largest rectangular submatrix composed entirely of zeros within a binary matrix. It efficiently reduces the 2D problem to a series of 1D largest rectangle in histogram problems.
//   • Idea: The algorithm transforms a 2D matrix problem into a series of 1D 'largest rectangle in histogram' problems, one for each row. It uses a monotonic stack to find the nearest smaller elements for each bar in O(N) time, leading to an overall O(N*M) complexity for the 2D problem.
//   • Invariants: The stack always stores indices of elements in strictly increasing order of their corresponding heights.; When an element is popped from the stack, the element below it is its nearest smaller element to the left.
//   • Tips: Precompute heights for each column, representing consecutive zeros upwards from the current row.; The 2D problem is effectively reduced to finding the largest rectangle in a histogram for each row.
//   • Pitfalls: Incorrectly handling boundary conditions when using the stack (e.g., empty stack, end of array).; Off-by-one errors when calculating the width of the rectangle (k2 - k1 - 1).
// - Non-negative Integers without Consecutive Ones (number, enumeration, simulation)
//   • When to use: Use when counting numbers up to a given limit that satisfy a specific bit pattern constraint, particularly when the limit is small enough for direct iteration and checking.
//   • Idea: This approach iterates through every non-negative integer from 0 up to the given limit num. For each integer, it simulates checking its binary representation to determine if it contains any two consecutive '1's.
//   • Invariants: count stores the number of integers k (where 0 <= k < i) that do not have consecutive ones.; All integers j such that 0 <= j < i have been processed.
//   • Tips: Use bitwise operations like (i & (i >> 1)) to efficiently detect consecutive ones.; Remember to include 0 in the count as it satisfies the condition (no consecutive ones).
//   • Pitfalls: Performance degradation for large num due to linear scan and per-number bit check.; Incorrectly handling the upper bound of the iteration (e.g., i < num instead of i <= num).
// - Manhattan Distance (array, number, enumeration, max-window)
//   • When to use: When calculating distances on a grid where movement is restricted to cardinal directions, or when optimizing expressions involving sums of absolute differences of coordinates.
//   • Idea: Manhattan distance, or L1 distance, measures the distance between two points as the sum of the absolute differences of their Cartesian coordinates. It is commonly used to find optimal paths on a grid or to transform coordinate systems for specific optimizations, often with O(N) or O(N log N) complexity for common problems like farthest pair.
//   • Invariants: For any two points P1(x1, y1) and P2(x2, y2), the Manhattan distance is |x1-x2| + |y1-y2|.; The maximum Manhattan distance between any two points is found by considering the maximum of (max(x+y) - min(x+y)) and (max(x-y) - min(x-y)) over all points.
//   • Tips: For 2D points (x, y), Manhattan distance can be transformed by rotating coordinates: (x', y') = (x+y, x-y).; After coordinate rotation, the Manhattan distance problem often simplifies to finding min/max values of the transformed coordinates.
//   • Pitfalls: Confusing Manhattan distance with Euclidean distance (L2 distance) or Chebyshev distance (L-infinity).; Incorrectly applying coordinate rotation for problems not involving sums of absolute differences.
//
// Notes:
// - Keep the given method signatures unchanged.
// - Use only Java standard library (`java.*`); no external dependencies.
// - Do not change input/output formats or return value semantics.
// - Conformance: single public class 'Solution'; no 'package' statement; place any extra types as static inner classes.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
    public int captureForts(int[] forts) {
        int maxCaptured = 0;
        for (int i = 0; i < forts.length; i++) {
            if (forts[i] == 1) {
                // Move to the right
                int capturedRight = 0;
                for (int j = i + 1; j < forts.length; j++) {
                    if (forts[j] == -1) break; // Can't move past an empty fort
                    if (forts[j] == 0) capturedRight++; // Capture enemy fort
                    if (forts[j] == 1) { // Reached another friendly fort
                        maxCaptured = Math.max(maxCaptured, capturedRight);
                        break;
                    }
                }
                // Move to the left
                int capturedLeft = 0;
                for (int j = i - 1; j >= 0; j--) {
                    if (forts[j] == -1) break; // Can't move past an empty fort
                    if (forts[j] == 0) capturedLeft++; // Capture enemy fort
                    if (forts[j] == 1) { // Reached another friendly fort
                        maxCaptured = Math.max(maxCaptured, capturedLeft);
                        break;
                    }
                }
            }
        }
        return maxCaptured;         
    }
}
