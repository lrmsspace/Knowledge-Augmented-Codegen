// Source: https://leetcode.com/problems/count-connected-components-in-lcm-graph/   |   Difficulty: Hard
//
// Problem Description:
// You are given an array of integers nums of size n and a positive integer threshold.
//
// There is a graph consisting of n nodes with the ith node having a value of nums[i]. Two nodes i and j in the graph are connected via an undirected edge if lcm(nums[i], nums[j]) <= threshold.
//
// Return the number of connected components in this graph.
//
// A connected component is a subgraph of a graph in which there exists a path between any two vertices, and no vertex of the subgraph shares an edge with a vertex outside of the subgraph.
//
// The term lcm(a, b) denotes the least common multiple of a and b.
//
// Example:
// Input: nums = [2,4,8,3,9], threshold = 5
//
// Output: 4
//
// Explanation: 
//
//
//
//  
//
// The four connected components are (2, 4), (3), (8), (9).
//
// Constraints:
// 1 <= nums.length <= 105
// 	1 <= nums[i] <= 109
// 	All elements of nums are unique.
// 	1 <= threshold <= 2 * 105
//
// Helpful references (internal KB):
// - Euler's totient function
//  (array, number, enumeration)
//   • When to use: Use when needing to count positive integers up to n that are relatively prime to n. It is also efficient for computing totient values for all numbers in a given range.
//   • Idea: Euler's totient function, φ(n), counts positive integers less than or equal to n that are relatively prime to n. It can be computed for a single n in O(sqrt(n)) using prime factorization, or for all numbers up to N in O(N log log N) using a sieve-like algorithm.
//   • Invariants: phi[i] stores the current totient value for i, which is i initially, then updated by (1 - 1/p) for each prime p dividing i.; After iterating through all primes p up to sqrt(N), phi[i] holds the correct totient value for all i <= N.
//   • Tips: For a single n, compute φ(n) using its prime factorization.; For all φ(i) up to N, use a sieve approach similar to Sieve of Eratosthenes.
//   • Pitfalls: Confusing 'relatively prime' with 'prime number'.; Applying the multiplicative property incorrectly when numbers share common factors.
// - Counting labeled graphs (number, dp-2d, counting, recursion)
//   • When to use: When counting the total number of labeled graphs with a specific number of vertices and connected components. Useful for problems requiring enumeration of graph structures based on their connectivity properties.
//   • Idea: This technique uses dynamic programming to count labeled graphs with a given number of vertices and connected components by building up solutions from smaller subproblems. It leverages a recurrence relation that considers the component containing a specific vertex, leading to an O(N^2 * K) time complexity for N vertices and K components.
//   • Invariants: D[i][j] correctly stores the number of labeled graphs with i vertices and j components.; All C_s values for s < n are correctly precomputed before calculating D[n][k].
//   • Tips: Precompute binomial coefficients for efficiency.; Precompute the number of connected graphs (C_s) for all relevant s.
//   • Pitfalls: Incorrectly defining base cases for the dynamic programming table.; Off-by-one errors in binomial coefficient calculations or array indexing.
// - Sqrt Tree (array, number, bitmask-dp, enumeration)
//   • When to use: Used for answering range queries on a static array by recursively decomposing it into square root sized blocks, achieving O(log log N) query time.
//   • Idea: A Sqrt Tree is a recursive data structure that decomposes an array into blocks of square root size, building a similar structure on each block. It allows for efficient range queries, typically achieving O(log log N) query time after an O(N log log N) precomputation.
//   • Invariants: Each node in the Sqrt Tree represents a contiguous segment of the original array.; A node representing a segment of length k has sqrt(k) children, each covering a block of sqrt(k) elements.
//   • Tips: Precompute answers for all possible block combinations within a node.; Handle queries spanning multiple blocks by combining precomputed prefix, suffix, and full block results.
//   • Pitfalls: High constant factors due to complex precomputation per node.; Memory usage can be significant, O(N log log N), for large N.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use the C standard library only; no external packages.
// - Do not change input/output formats or return value semantics.
// - Conformance: ISO C (C89/C99/C11). Do NOT use GNU C extensions (nested functions, statement expressions, typeof, __auto_type, etc.). Avoid VLAs and non-standard builtins.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

int countComponents(int* nums, int numsSize, int threshold) {
    int count = 0;
    for (int i = 0; i < numsSize; i++) {
        if (nums[i] > threshold) {
            count++;
        }
    }
    return count;       
}
