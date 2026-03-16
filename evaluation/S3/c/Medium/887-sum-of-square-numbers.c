// Source: https://leetcode.com/problems/sum-of-square-numbers/   |   Difficulty: Medium
//
// Problem Description:
// Given a non-negative integer c, decide whether there're two integers a and b such that a2 + b2 = c.
//
// Example:
// Input: c = 5
// Output: true
// Explanation: 1 * 1 + 2 * 2 = 5
//
// Constraints:
// 0 <= c <= 231 - 1
//
// Helpful references (internal KB):
// - Sqrt Decomposition (array, ds, sliding-window, two-pointers)
//   • When to use: Use when performing frequent range queries and point updates on an array, especially when a segment tree is too complex or memory-intensive, or when query types are diverse. It offers a balanced time complexity for both operations.
//   • Idea: Sqrt decomposition divides an array into blocks of size approximately sqrt(N) to optimize range queries and point updates. It achieves O(sqrt(N)) time complexity for both operations.
//   • Invariants: Each element `arr[i]` belongs to exactly one block `block[i / block_size]`.; The summary for each block `block_summary[j]` accurately reflects the state of elements within block `j`.
//   • Tips: Choose block size carefully, typically sqrt(N) for balanced performance.; Precompute block summaries (e.g., sum, min, max) for efficient queries.
//   • Pitfalls: Off-by-one errors when calculating block indices or boundaries.; Forgetting to update the block's summary after a point update.
// - Circle-Line Intersection (geometry, number, enumeration, simulation)
//   • When to use: Use this algorithm to find the intersection points between a circle and a line, especially when numerical stability is a concern. It efficiently determines zero, one, or two intersection points.
//   • Idea: This algorithm finds the intersection points of a circle and a line by using geometric properties like distances and vectors, avoiding direct algebraic system solving. It determines zero, one, or two intersection points in constant time, O(1).
//   • Invariants: The distance from the origin to the line, d0, is always correctly calculated as |C| / sqrt(A^2 + B^2).; The point (x0, y0) is always the closest point on the line Ax+By+C=0 to the origin (0,0).
//   • Tips: Translate the circle to the origin for simplified calculations, adjusting the line equation accordingly.; Use the distance from the origin to the line to quickly determine the number of intersection points.
//   • Pitfalls: Floating point precision errors can accumulate, especially with very small or large coordinates.; Incorrectly handling edge cases where the line is tangent to the circle or passes through the origin.
// - Integer factorization (number, randomized, gcd, two-pointers)
//   • When to use: Used to find non-trivial factors of a large composite number, especially when trial division is too slow. It's effective for numbers with relatively small prime factors or factors whose predecessors are powersmooth.
//   • Idea: Integer factorization algorithms like Pollard's p-1 and Pollard's Rho probabilistically find factors of composite numbers. Pollard's p-1 leverages modular exponentiation and GCD, while Pollard's Rho uses cycle detection on a pseudo-random sequence.
//   • Invariants: For Pollard's p-1, a^M mod p remains 1 for any prime factor p where p-1 divides M.; For Pollard's p-1, M is always a multiple of lcm(1, 2, ..., B) for the current B.
//   • Tips: Pollard's p-1 is effective when p-1 is B-powersmooth for a factor p.; Pollard's Rho is generally more robust for arbitrary composite numbers.
//   • Pitfalls: Algorithms are probabilistic; no guarantee of finding a factor.; May return n (the number itself) or 1, requiring retry with different parameters.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use the C standard library only; no external packages.
// - Do not change input/output formats or return value semantics.
// - Conformance: ISO C (C89/C99/C11). Do NOT use GNU C extensions (nested functions, statement expressions, typeof, __auto_type, etc.). Avoid VLAs and non-standard builtins.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

bool judgeSquareSum(int c) {
    for (long long a = 0; a * a <= c; a++) {
        long long b_squared = c - a * a;
        long long b = (long long)sqrt(b_squared);
        if (b * b == b_squared) {
            return true;
        }
    }
    return false;       
}
