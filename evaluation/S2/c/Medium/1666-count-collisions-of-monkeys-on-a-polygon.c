// Source: https://leetcode.com/problems/count-collisions-of-monkeys-on-a-polygon/   |   Difficulty: Medium
//
// Problem Description:
// There is a regular convex polygon with n vertices. The vertices are labeled from 0 to n - 1 in a clockwise direction, and each vertex has exactly one monkey. The following figure shows a convex polygon of 6 vertices.
//
// Simultaneously, each monkey moves to a neighboring vertex. A collision happens if at least two monkeys reside on the same vertex after the movement or intersect on an edge.
//
// Return the number of ways the monkeys can move so that at least one collision happens. Since the answer may be very large, return it modulo 109 + 7.
//
// Example:
// Input: n = 3
//
// Output: 6
//
// Explanation:
//
// There are 8 total possible movements.
// Two ways such that they collide at some point are:
//
//
// 	Monkey 1 moves in a clockwise direction; monkey 2 moves in an anticlockwise direction; monkey 3 moves in a clockwise direction. Monkeys 1 and 2 collide.
// 	Monkey 1 moves in an anticlockwise direction; monkey 2 moves in an anticlockwise direction; monkey 3 moves in a clockwise direction. Monkeys 1 and 3 collide.
//
// Constraints:
// 3 <= n <= 109
//
// Helpful references (internal KB):
// - Factorial modulo 
// p (number, counting, recursion)
//   • When to use: Use when the problem asks for the total count of possibilities or arrangements that can be naturally broken down into smaller, self-similar subproblems. It's effective for exploring decision trees or state spaces.
//   • Idea: Counting determines the number of elements or event occurrences. It uses combinatorial or iterative/recursive methods, often with O(N) or O(log N) complexity.
//   • Invariants: Each recursive call processes a smaller, well-defined subproblem.; The base cases correctly return the count for the simplest scenarios.
//   • Tips: Identify the smallest subproblem and its base cases to stop recursion.; Define the recursive relation clearly, showing how larger problems depend on smaller ones.
//   • Pitfalls: Incorrectly defining base cases can lead to infinite recursion or incorrect results.; Overlapping subproblems without memoization can lead to exponential time complexity.
// - Discrete Logarithm (array, number, binary-search, mod-exp)
//   • When to use: Use when solving for the exponent 'x' in the modular equation a^x = b (mod m), especially when 'm' is large and a and m are coprime. It's suitable for finding a solution within O(sqrt(m) log m) time.
//   • Idea: This algorithm, also known as Baby-step Giant-step, finds the smallest non-negative integer 'x' satisfying a^x = b (mod m) using a meet-in-the-middle approach. It achieves a time complexity of O(sqrt(m) log m).
//   • Invariants: The map stores (a^q mod m, q) for all baby steps q in [0, n-1].; For each giant step p, a^(np) mod m is correctly computed.
//   • Tips: Choose 'n' as ceil(sqrt(m)) for balanced steps.; Use a hash map to store baby steps for O(1) average lookup.
//   • Pitfalls: Incorrect choice of 'n' can lead to suboptimal time complexity.; Failure to check if 'a' and 'm' are coprime may yield no solution or incorrect results.
// - Josephus Problem (number, dp-1d, recursion)
//   • When to use: Used to determine the position of the last remaining person in a circle where every k-th person is eliminated until only one remains. It models sequential removal processes in a circular arrangement.
//   • Idea: The Josephus Problem determines the position of the survivor in a circle of N people, where every K-th person is eliminated. The standard solution uses a recursive relation or dynamic programming, typically achieving O(N) time complexity.
//   • Invariants: The result J(n, k) represents the survivor's original 0-indexed position among n people.; Each recursive step J(n, k) correctly transforms the result from J(n-1, k) based on the k-th elimination.
//   • Tips: Use 0-indexing for a simpler and more elegant recursive formula.; Establish the base case for N=1 (the survivor is always 0 or 1).
//   • Pitfalls: Off-by-one errors when switching between 0-indexing and 1-indexing.; Incorrectly applying the modulo operator, especially with negative results in some languages.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use the C standard library only; no external packages.
// - Do not change input/output formats or return value semantics.
// - Conformance: ISO C (C89/C99/C11). Do NOT use GNU C extensions (nested functions, statement expressions, typeof, __auto_type, etc.). Avoid VLAs and non-standard builtins.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

int monkeyMove(int n) {
    long long mod = 1000000007;
    long long totalWays = 1;
    for (int i = 0; i < n; i++) {
        totalWays = (totalWays * 2) % mod; // Each monkey has 2 choices: move clockwise or anticlockwise
    }
    long long noCollisionWays = 2; // All monkeys move in the same direction (either all clockwise or all anticlockwise)
    
    return (totalWays - noCollisionWays + mod) % mod; // Total ways minus no collision ways, ensuring non-negative result       
}
