// Source: https://leetcode.com/problems/reaching-points/   |   Difficulty: Hard
//
// Problem Description:
// Given four integers sx, sy, tx, and ty, return true if it is possible to convert the point (sx, sy) to the point (tx, ty) through some operations, or false otherwise.
//
// The allowed operation on some point (x, y) is to convert it to either (x, x + y) or (x + y, y).
//
// Example:
// Input: sx = 1, sy = 1, tx = 3, ty = 5
// Output: true
// Explanation:
// One series of moves that transforms the starting point to the target is:
// (1, 1) -> (1, 2)
// (1, 2) -> (3, 2)
// (3, 2) -> (3, 5)
//
// Constraints:
// 1 <= sx, sy, tx, ty <= 109
//
// Helpful references (internal KB):
// - Extended Euclidean Algorithm (number, gcd, simulation)
//   • When to use: Use this algorithm to find integer coefficients x and y that satisfy Bézout's identity (ax + by = gcd(a,b)). It is also essential for computing modular multiplicative inverses and solving linear Diophantine equations.
//   • Idea: The Extended Euclidean Algorithm computes the greatest common divisor (GCD) of two integers 'a' and 'b', and simultaneously finds integer coefficients 'x' and 'y' such that 'ax + by = gcd(a,b)'. It operates in O(log(min(a,b))) time complexity.
//   • Invariants: x * (initial a) + y * (initial b) = current_a_value; x_1 * (initial a) + y_1 * (initial b) = current_b_value
//   • Tips: Can be implemented using either a recursive or an iterative approach.; The algorithm correctly handles negative integer inputs.
//   • Pitfalls: Incorrectly defining base cases in recursive implementations can lead to errors.; Potential for integer overflow if coefficients x or y become extremely large, though uncommon.
// - Finding the equation of a line for a segment (number, geometry, gcd)
//   • When to use: Use this method when you need to represent a line segment's equation using integer coefficients, especially to avoid floating-point inaccuracies in geometric computations.
//   • Idea: This method derives the general form of a line equation (Ax + By + C = 0) from two points, ensuring integer coefficients if input coordinates are integers. It then normalizes these coefficients using GCD to achieve a unique representation, typically in O(log(max(|A|,|B|,|C|))) time due to GCD.
//   • Invariants: The calculated coefficients A, B, C always satisfy A*Px + B*Py + C = 0 for point P(Px, Py).; After GCD division, the absolute values of A, B, C are coprime (unless all are zero).
//   • Tips: Always compute A, B, C using the given formulas for P(Px, Py) and Q(Qx, Qy).; Use absolute values of A, B, C when calculating their greatest common divisor.
//   • Pitfalls: Forgetting to normalize coefficients leads to non-unique representations for the same line.; Incorrectly handling signs during the final normalization step can result in inconsistent forms.
// - The Stern-Brocot tree and Farey sequences (number, tree, binary-search, simulation)
//   • When to use: Use this when representing positive rational numbers as unique paths in a binary tree or when efficiently approximating irrational numbers. It's ideal for finding a fraction's path or its position within ordered sequences.
//   • Idea: The Stern-Brocot tree uniquely maps every positive rational number to a binary path, constructed by repeatedly taking mediants. This allows for efficient search and representation of fractions with O(log(p+q)) time complexity.
//   • Invariants: The target fraction p/q always lies strictly between the current left boundary pL/qL and right boundary pR/qR.; The current left and right boundary fractions (pL/qL, pR/qR) are always adjacent terms in some Farey sequence.
//   • Tips: Initialize search boundaries with 0/1 and 1/0 (or 1/1 for positive fractions).; Calculate the mediant (pL+pR)/(qL+qR) to determine the next candidate fraction.
//   • Pitfalls: Naive O(p+q) search without run-length encoding can be too slow for large fractions.; Incorrectly handling initial boundary conditions (e.g., 0/1, 1/0, 1/1).
//
// Notes:
// - Keep the given function signature unchanged.
// - Do not add custom input parsing or console I/O unless the template explicitly requires it; rely on parameters/return value only.
// - Use standard ECMAScript features supported by LeetCode (Node.js runtime); no external packages.
// - Be careful with number precision: JavaScript Number is double; use BigInt only when necessary and keep return type consistent with the problem requirements.
// - If you introduce helper functions, define them in the same file and avoid relying on global mutable state across test cases.

/**
 * @param {number} sx
 * @param {number} sy
 * @param {number} tx
 * @param {number} ty
 * @return {boolean}
 */
var reachingPoints = function(sx, sy, tx, ty) {
    while (tx >= sx && ty >= sy) {
        if (tx === ty) {
            break;
        } else if (tx > ty) {
            if (ty > sy) {
                tx %= ty;
            } else {
                return (tx - sx) % ty === 0;
            }
        }
        else {
            if (tx > sx) {
                ty %= tx;
            } else {
                return (ty - sy) % tx === 0;
            }
        }
    }
    return tx === sx && ty === sy;
                    
};
