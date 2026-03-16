// Source: https://leetcode.com/problems/mirror-reflection/   |   Difficulty: Medium
//
// Problem Description:
// There is a special square room with mirrors on each of the four walls. Except for the southwest corner, there are receptors on each of the remaining corners, numbered 0, 1, and 2.
//
// The square room has walls of length p and a laser ray from the southwest corner first meets the east wall at a distance q from the 0th receptor.
//
// Given the two integers p and q, return the number of the receptor that the ray meets first.
//
// The test cases are guaranteed so that the ray will meet a receptor eventually.
//
// Example:
// Input: p = 2, q = 1
// Output: 2
// Explanation: The ray meets receptor 2 the first time it gets reflected back to the left wall.
//
// Constraints:
// 1 <= q <= p <= 1000
//
// Helpful references (internal KB):
// - Lattice points inside non-lattice polygon (number, recursion, counting, gcd)
//   • When to use: Use when counting pairs or elements satisfying divisibility or GCD conditions. Also applicable for summing functions over pairs using number theory properties.
//   • Idea: This approach leverages number theoretic properties like GCD, LCM, and prime factorization to efficiently count elements or pairs satisfying specific criteria. It often involves iterating through divisors or multiples, achieving complexities like O(N log N) or O(sqrt N) per query.
//   • Invariants: All numbers processed so far have their relevant number-theoretic properties (e.g., prime factors, divisors) correctly determined.; The current count or sum accurately reflects all valid combinations found up to the current iteration.
//   • Tips: Precompute primes or divisors using a sieve for efficiency.; Utilize properties of GCD and LCM, such as gcd(a,b) * lcm(a,b) = a * b.
//   • Pitfalls: Overcounting or undercounting when using inclusion-exclusion.; Integer overflow with large products or sums.
// - Finding the equation of a line for a segment (number, geometry, gcd)
//   • When to use: Use this method when you need to represent a line segment's equation using integer coefficients, especially to avoid floating-point inaccuracies in geometric computations.
//   • Idea: This method derives the general form of a line equation (Ax + By + C = 0) from two points, ensuring integer coefficients if input coordinates are integers. It then normalizes these coefficients using GCD to achieve a unique representation, typically in O(log(max(|A|,|B|,|C|))) time due to GCD.
//   • Invariants: The calculated coefficients A, B, C always satisfy A*Px + B*Py + C = 0 for point P(Px, Py).; After GCD division, the absolute values of A, B, C are coprime (unless all are zero).
//   • Tips: Always compute A, B, C using the given formulas for P(Px, Py) and Q(Qx, Qy).; Use absolute values of A, B, C when calculating their greatest common divisor.
//   • Pitfalls: Forgetting to normalize coefficients leads to non-unique representations for the same line.; Incorrectly handling signs during the final normalization step can result in inconsistent forms.
// - Euclidean algorithm for computing the greatest common divisor (number, gcd)
//   • When to use: Use this algorithm to efficiently find the greatest common divisor of two non-negative integers, or as a subroutine for calculating the least common multiple.
//   • Idea: The Euclidean algorithm is an efficient method for computing the greatest common divisor (GCD) of two integers by repeatedly applying the division algorithm. It has a logarithmic time complexity, typically O(log(min(a,b))).
//   • Invariants: The GCD of the current pair (a, b) is always equal to the GCD of the original input numbers.; If a and b are non-negative, then the current values of a and b remain non-negative.
//   • Tips: The GCD of any number and zero is the number itself (e.g., gcd(a, 0) = a).; To calculate LCM, use the formula lcm(a, b) = (a / gcd(a, b)) * b to prevent potential overflow.
//   • Pitfalls: Ensure inputs are non-negative; if negative, take absolute values first.; Be careful with `gcd(0, 0)` definition, which is often undefined or 0.
//
// Notes:
// - Keep the given method signatures unchanged.
// - Use only Java standard library (`java.*`); no external dependencies.
// - Do not change input/output formats or return value semantics.
// - Conformance: single public class 'Solution'; no 'package' statement; place any extra types as static inner classes.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
    public int mirrorReflection(int p, int q) {
        int lcm = lcm(p, q);
        int m = lcm / p;
        int n = lcm / q;

        if (m % 2 == 0 && n % 2 == 1) {
            return 0;
        } else if (m % 2 == 1 && n % 2 == 1) {
            return 1;
        } else if (m % 2 == 1 && n % 2 == 0) {
            return 2;
        }

        return -1; // This line should never be reached due to problem constraints.         
    }
}
