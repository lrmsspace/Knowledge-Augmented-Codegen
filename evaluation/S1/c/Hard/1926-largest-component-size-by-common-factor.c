// Source: https://leetcode.com/problems/largest-component-size-by-common-factor/   |   Difficulty: Hard
//
// Problem Description:
// You are given an integer array of unique positive integers nums. Consider the following graph:
//
//
// 	There are nums.length nodes, labeled nums[0] to nums[nums.length - 1],
// 	There is an undirected edge between nums[i] and nums[j] if nums[i] and nums[j] share a common factor greater than 1.
//
//
// Return the size of the largest connected component in the graph.
//
// Example:
// Input: nums = [4,6,15,35]
// Output: 4
//
// Constraints:
// 1 <= nums.length <= 2 * 104
// 	1 <= nums[i] <= 105
// 	All the values of nums are unique.
//
// Helpful references (internal KB):
// - Sieve of Eratosthenes (array, sieve, enumeration)
//   • When to use: Use when you need to find all prime numbers up to a certain limit or precompute primality for a range. It is efficient for generating primes within a reasonable upper bound.
//   • Idea: The Sieve of Eratosthenes efficiently finds all prime numbers up to a specified integer by iteratively marking multiples of primes as composite. It achieves a time complexity of O(N log log N).
//   • Invariants: All numbers less than the current prime 'p' have already been processed.; If 'i' is marked as prime, then all its multiples less than 'i*i' have been marked composite by smaller primes.
//   • Tips: Optimize by starting inner loop from p*p, as smaller multiples would have been marked.; Use a boolean array for primality, or an integer array to store smallest prime factor (SPF).
//   • Pitfalls: Incorrectly handling 0 and 1, which are neither prime nor composite.; Off-by-one errors when setting array bounds or loop conditions.
// - Finding Bridges Online (graph, tree, union-find, counting)
//   • When to use: Use when you need to dynamically track bridges and 2-edge-connected components in a graph as edges are added. It efficiently updates the graph structure and bridge count in an online fashion.
//   • Idea: This algorithm maintains 2-edge-connected components and bridges in a graph as edges are added, using a Union-Find structure to manage components and a forest to represent the relationships between them. It typically achieves near-amortized constant time per edge addition.
//   • Invariants: Each 2-edge-connected component is represented by a single root in the Union-Find structure.; The set of bridges forms a forest where each node is a 2-edge-connected component.
//   • Tips: Represent 2-edge-connected components using Union-Find for efficient merging.; Maintain a forest where nodes are 2-edge-connected components and edges are bridges.
//   • Pitfalls: Incorrectly identifying when an edge forms a cycle with existing bridges.; Failing to update the bridge count accurately when bridges are removed.
// - Non-negative Integers without Consecutive Ones (number, enumeration, simulation)
//   • When to use: Use when counting numbers up to a given limit that satisfy a specific bit pattern constraint, particularly when the limit is small enough for direct iteration and checking.
//   • Idea: This approach iterates through every non-negative integer from 0 up to the given limit num. For each integer, it simulates checking its binary representation to determine if it contains any two consecutive '1's.
//   • Invariants: count stores the number of integers k (where 0 <= k < i) that do not have consecutive ones.; All integers j such that 0 <= j < i have been processed.
//   • Tips: Use bitwise operations like (i & (i >> 1)) to efficiently detect consecutive ones.; Remember to include 0 in the count as it satisfies the condition (no consecutive ones).
//   • Pitfalls: Performance degradation for large num due to linear scan and per-number bit check.; Incorrectly handling the upper bound of the iteration (e.g., i < num instead of i <= num).
//
// Notes:
// - Keep the given function signature unchanged.
// - Use the C standard library only; no external packages.
// - Do not change input/output formats or return value semantics.
// - Conformance: ISO C (C89/C99/C11). Do NOT use GNU C extensions (nested functions, statement expressions, typeof, __auto_type, etc.). Avoid VLAs and non-standard builtins.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

int largestComponentSize(int* nums, int numsSize) {
    int maxNum = 0;
    for (int i = 0; i < numsSize; ++i) {
        if (nums[i] > maxNum) maxNum = nums[i];
    }

    /* Sieve of Eratosthenes to get smallest prime factor (SPF) for each number */
    int *spf = (int*)malloc((maxNum + 1) * sizeof(int));
    for (int i = 0; i <= maxNum; ++i) spf[i] = i;
    for (int i = 2; i * i <= maxNum; ++i) {
        if (spf[i] == i) { /* i is prime */
            for (int j = i * i; j <= maxNum; j += i) {
                if (spf[j] == j) spf[j] = i;
            }
        }
    }

    /* Union-Find structure */
    int *parent = (int*)malloc((maxNum + 1) * sizeof(int));
    int *rank = (int*)calloc((maxNum + 1), sizeof(int));
    for (int i = 0; i <= maxNum; ++i) parent[i] = i;

    int find(int x) {
        if (parent[x] != x) parent[x] = find(parent[x]);
        return parent[x];
    }

    void unionSet(int x, int y) {
        int rootX = find(x);
        int rootY = find(y);
        if (rootX != rootY) {
            if (rank[rootX] > rank[rootY]) {
                parent[rootY] = rootX;
            } else if (rank[rootX] < rank[rootY]) {
                parent[rootX] = rootY;
            } else {
                parent[rootY] = rootX;
                rank[rootX]++;
            }
        }
    }

    /* Union numbers by their prime factors */
    for (int i = 0; i < numsSize; ++i) {
        int x = nums[i];
        while (x > 1) {
            int primeFactor = spf[x];
            unionSet(nums[i], primeFactor);
            while (x % primeFactor == 0) {
                x /= primeFactor;
            }
        }
    }

    /* Count sizes of connected components */
    int *componentSize = (int*)calloc((maxNum + 1), sizeof(int));
    int maxSize = 0;
    for (int i = 0; i < numsSize; ++i) {
        int root = find(nums[i]);
        componentSize[root]++;
        if (componentSize[root] > maxSize) {
            maxSize = componentSize[root];
        }
    }

    free(spf);
    free(parent);
    free(rank);
    free(componentSize);

    return maxSize;
}