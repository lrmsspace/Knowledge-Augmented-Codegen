// Source: https://leetcode.com/problems/minimum-number-of-operations-to-make-x-and-y-equal/   |   Difficulty: Medium
//
// Problem Description:
// You are given two positive integers x and y.
//
// In one operation, you can do one of the four following operations:
//
//
// 	Divide x by 11 if x is a multiple of 11.
// 	Divide x by 5 if x is a multiple of 5.
// 	Decrement x by 1.
// 	Increment x by 1.
//
//
// Return the minimum number of operations required to make  x and y equal.
//
// Example:
// Input: x = 26, y = 1
// Output: 3
// Explanation: We can make 26 equal to 1 by applying the following operations: 
// 1. Decrement x by 1
// 2. Divide x by 5
// 3. Divide x by 5
// It can be shown that 3 is the minimum number of operations required to make 26 equal to 1.
//
// Constraints:
// 1 <= x, y <= 104
//
// Helpful references (internal KB):
// - Digit DP (array, number, digit-dp)
//   • When to use: Use Digit DP to count numbers within a given range [a, b] that satisfy a property based on their digits. It's effective when the property can be checked digit by digit.
//   • Idea: Digit DP is a dynamic programming technique to count numbers within a given range [A, B] that satisfy specific properties related to their digits. It typically involves a recursive function with memoization, building numbers digit by digit, and has a complexity roughly proportional to (number of digits * state space).
//   • Invariants: The `tight` parameter accurately reflects if the current prefix matches the upper bound's prefix.; The `is_leading_zero` parameter correctly indicates if all preceding digits chosen were zero.
//   • Tips: Define the DP state carefully, including index, tight constraint, and leading zero flag.; Handle leading zeros correctly, as they can affect properties like sum or count of digits.
//   • Pitfalls: Incorrectly handling the 'tight' constraint, leading to overcounting or undercounting.; Forgetting to account for leading zeros or mismanaging their impact on the property.
// - Extended Euclidean Algorithm (number, gcd, simulation)
//   • When to use: Use this algorithm to find integer coefficients x and y that satisfy Bézout's identity (ax + by = gcd(a,b)). It is also essential for computing modular multiplicative inverses and solving linear Diophantine equations.
//   • Idea: The Extended Euclidean Algorithm computes the greatest common divisor (GCD) of two integers 'a' and 'b', and simultaneously finds integer coefficients 'x' and 'y' such that 'ax + by = gcd(a,b)'. It operates in O(log(min(a,b))) time complexity.
//   • Invariants: x * (initial a) + y * (initial b) = current_a_value; x_1 * (initial a) + y_1 * (initial b) = current_b_value
//   • Tips: Can be implemented using either a recursive or an iterative approach.; The algorithm correctly handles negative integer inputs.
//   • Pitfalls: Incorrectly defining base cases in recursive implementations can lead to errors.; Potential for integer overflow if coefficients x or y become extremely large, though uncommon.
// - Manhattan Distance (geometry, number, coordinate-compress)
//   • When to use: Use when calculating distance between two points on a grid where movement is restricted to horizontal and vertical directions. It is also useful for problems involving maximizing or minimizing sums of absolute coordinate differences, often transformable to Chebyshev distance.
//   • Idea: Manhattan distance measures the sum of absolute differences of Cartesian coordinates between two points. It can be transformed into a Chebyshev distance problem by rotating coordinates, enabling efficient O(N) max/min distance calculations.
//   • Invariants: For any two points P1=(x1, y1) and P2=(x2, y2), the Manhattan distance is always non-negative.; The transformed points P1'=(x1+y1, y1-x1) and P2'=(x2+y2, y2-x2) satisfy Chebyshev(P1', P2') == Manhattan(P1, P2).
//   • Tips: Consider transforming to Chebyshev distance for max/min distance problems.; The transformation involves rotating coordinates: (x, y) -> (x+y, y-x).
//   • Pitfalls: Confusing with Euclidean distance, which allows diagonal movement.; Incorrectly applying coordinate transformation (e.g., wrong signs).
//
// Notes:
// - Keep the given method signatures unchanged.
// - Use only Java standard library (`java.*`); no external dependencies.
// - Do not change input/output formats or return value semantics.
// - Conformance: single public class 'Solution'; no 'package' statement; place any extra types as static inner classes.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
    public int minimumOperationsToMakeEqual(int x, int y) {
        int operations = 0;
        while (x != y) {
            if (x > y) {
                if (x % 11 == 0) {
                    x /= 11;
                } else if (x % 5 == 0) {
                    x /= 5;
                } else {
                    x--;
                }
            } else {
                y--;
            }
            operations++;
        }
        return operations;          
    }
}
