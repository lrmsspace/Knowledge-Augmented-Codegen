// Source: https://leetcode.com/problems/sqrtx/   |   Difficulty: Easy
//
// Problem Description:
// Given a non-negative integer x, return the square root of x rounded down to the nearest integer. The returned integer should be non-negative as well.
//
// You must not use any built-in exponent function or operator.
//
//
// 	For example, do not use pow(x, 0.5) in c++ or x ** 0.5 in python.
//
// Example:
// Input: x = 4
// Output: 2
// Explanation: The square root of 4 is 2, so we return 2.
//
// Constraints:
// 0 <= x <= 231 - 1
//
// Helpful references (internal KB):
// - Binary search (interval, number, binary-search-answer, recursion)
//   • When to use: Use when optimizing a unimodal function (finding its maximum or minimum) over a continuous interval, where direct differentiation is hard or impossible.
//   • Idea: This algorithm finds the extremum (maximum or minimum) of a unimodal function over a given interval by repeatedly narrowing the search space. It evaluates the function at two internal points to achieve logarithmic convergence.
//   • Invariants: The extremum of the unimodal function f(x) is always within the current interval [l, r].; The function f(x) remains unimodal within the current interval [l, r].
//   • Tips: Use a fixed number of iterations as a stopping criterion instead of an epsilon value for robustness against floating point errors.; For golden section search, reuse one function evaluation from the previous step to minimize expensive computations.
//   • Pitfalls: Applying this algorithm to a non-unimodal function will yield an incorrect result.; Floating point precision issues can lead to incorrect comparisons or infinite loops if `eps` is too small.
// - Discrete Root
//  (number, mod-exp)
//   • When to use: Use this algorithm to find all solutions x for the modular equation x^k = a (mod n) when n is a prime number. It is applicable when solving for an unknown base in a modular power.
//   • Idea: This algorithm solves the discrete root problem by transforming it into a discrete logarithm problem using a primitive root modulo n. The overall time complexity is dominated by the discrete logarithm step, typically O(sqrt(n) log n) using Baby-step Giant-step.
//   • Invariants: All calculations are performed within the finite field modulo n.; The primitive root g generates all non-zero residues modulo n.
//   • Tips: Handle the special case where a = 0 separately, as x = 0 is the only solution.; Ensure the modulus n is prime, as primitive roots are guaranteed to exist.
//   • Pitfalls: Assuming n is prime when it is not, which invalidates the primitive root approach.; Forgetting to check for the existence of solutions for the discrete logarithm.
// - Sqrt Tree (array, number, bitmask-dp, enumeration)
//   • When to use: Used for answering range queries on a static array by recursively decomposing it into square root sized blocks, achieving O(log log N) query time.
//   • Idea: A Sqrt Tree is a recursive data structure that decomposes an array into blocks of square root size, building a similar structure on each block. It allows for efficient range queries, typically achieving O(log log N) query time after an O(N log log N) precomputation.
//   • Invariants: Each node in the Sqrt Tree represents a contiguous segment of the original array.; A node representing a segment of length k has sqrt(k) children, each covering a block of sqrt(k) elements.
//   • Tips: Precompute answers for all possible block combinations within a node.; Handle queries spanning multiple blocks by combining precomputed prefix, suffix, and full block results.
//   • Pitfalls: High constant factors due to complex precomputation per node.; Memory usage can be significant, O(N log log N), for large N.
//
// Notes:
// - Keep the given method signatures unchanged.
// - Use only Java standard library (`java.*`); no external dependencies.
// - Do not change input/output formats or return value semantics.
// - Conformance: single public class 'Solution'; no 'package' statement; place any extra types as static inner classes.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
    public int mySqrt(int x) {
        if (x == 0) {
            return 0;
        }
        int left = 1, right = x;
        while (left < right) {
            int mid = left + (right - left + 1) / 2;
            if (mid <= x / mid) {
                left = mid;
            } else {
                right = mid - 1;
            }
        }
        return left;            
    }
}
