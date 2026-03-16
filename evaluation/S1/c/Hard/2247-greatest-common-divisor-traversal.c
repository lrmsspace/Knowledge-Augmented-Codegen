// Source: https://leetcode.com/problems/greatest-common-divisor-traversal/   |   Difficulty: Hard
//
// Problem Description:
// You are given a 0-indexed integer array nums, and you are allowed to traverse between its indices. You can traverse between index i and index j, i != j, if and only if gcd(nums[i], nums[j]) > 1, where gcd is the greatest common divisor.
//
// Your task is to determine if for every pair of indices i and j in nums, where i < j, there exists a sequence of traversals that can take us from i to j.
//
// Return true if it is possible to traverse between all such pairs of indices, or false otherwise.
//
// Example:
// Input: nums = [2,3,6]
// Output: true
// Explanation: In this example, there are 3 possible pairs of indices: (0, 1), (0, 2), and (1, 2).
// To go from index 0 to index 1, we can use the sequence of traversals 0 -> 2 -> 1, where we move from index 0 to index 2 because gcd(nums[0], nums[2]) = gcd(2, 6) = 2 > 1, and then move from index 2 to index 1 because gcd(nums[2], nums[1]) = gcd(6, 3) = 3 > 1.
// To go from index 0 to index 2, we can just go directly because gcd(nums[0], nums[2]) = gcd(2, 6) = 2 > 1. Likewise, to go from index 1 to index 2, we can just go directly because gcd(nums[1], nums[2]) = gcd(3, 6) = 3 > 1.
//
// Constraints:
// 1 <= nums.length <= 105
// 	1 <= nums[i] <= 105
//
// Helpful references (internal KB):
// - Sieve of Eratosthenes (array, sieve, enumeration)
//   • When to use: Use when you need to find all prime numbers up to a certain limit or precompute primality for a range. It is efficient for generating primes within a reasonable upper bound.
//   • Idea: The Sieve of Eratosthenes efficiently finds all prime numbers up to a specified integer by iteratively marking multiples of primes as composite. It achieves a time complexity of O(N log log N).
//   • Invariants: All numbers less than the current prime 'p' have already been processed.; If 'i' is marked as prime, then all its multiples less than 'i*i' have been marked composite by smaller primes.
//   • Tips: Optimize by starting inner loop from p*p, as smaller multiples would have been marked.; Use a boolean array for primality, or an integer array to store smallest prime factor (SPF).
//   • Pitfalls: Incorrectly handling 0 and 1, which are neither prime nor composite.; Off-by-one errors when setting array bounds or loop conditions.
// - Disjoint Set Union (ds, linked-list, union-find, dfs)
//   • When to use: Use when you need to maintain a collection of disjoint sets and perform union operations to merge sets or find the representative of an element's set efficiently. It's suitable for problems involving dynamic connectivity or grouping elements.
//   • Idea: Disjoint Set Union (DSU) is a data structure that stores a collection of disjoint sets and supports two primary operations: finding the representative of an element's set and merging two sets. It achieves nearly constant time complexity for these operations with path compression and union by rank/size optimizations.
//   • Invariants: Every element `i` belongs to exactly one set, represented by `find(i)`.; If `parent[i] == i`, then `i` is the representative (root) of its set.
//   • Tips: Implement path compression in `find` for optimal performance.; Use union by size or rank to maintain balanced trees.
//   • Pitfalls: Omitting path compression or union by rank/size can degrade performance to O(N).; Failing to correctly update auxiliary data stored at representatives during a union operation.
// - interval-dp (array, interval-dp, prefix-sum)
//   • When to use: Use when finding an optimal value (min/max) for operations on contiguous subarrays or segments, especially when subproblems are defined by intervals and can be combined from smaller adjacent intervals. Useful for problems involving circular arrangements by duplicating the array.
//   • Idea: Interval DP is a dynamic programming technique that solves problems by breaking them into subproblems defined over contiguous intervals. It typically computes solutions for smaller intervals first, then uses these to build solutions for larger intervals, often with an O(N^3) time complexity.
//   • Invariants: For any `len`, `dp[l][r]` for `r - l + 1 < len` are already computed.; `dp[l][r]` represents the optimal cost for the operation on the range `[l, r]`.
//   • Tips: Define dp[i][j] as the optimal solution for the interval [i, j].; Iterate by interval length first, then by start index.
//   • Pitfalls: Incorrectly defining base cases for intervals of length 1.; Off-by-one errors in interval boundaries or split points.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use the C standard library only; no external packages.
// - Do not change input/output formats or return value semantics.
// - Conformance: ISO C (C89/C99/C11). Do NOT use GNU C extensions (nested functions, statement expressions, typeof, __auto_type, etc.). Avoid VLAs and non-standard builtins.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

bool canTraverseAllPairs(int* nums, int numsSize) {
    /* Disjoint Set Union (Union-Find) structure */
    typedef struct DSU {
        int *parent;
        int *size;
    } DSU;

    DSU* dsuCreate(int n) {
        DSU *dsu = (DSU*)malloc(sizeof(DSU));
        dsu->parent = (int*)malloc(n * sizeof(int));
        dsu->size = (int*)malloc(n * sizeof(int));
        for (int i = 0; i < n; ++i) {
            dsu->parent[i] = i;
            dsu->size[i] = 1;
        }
        return dsu;
    }

    int dsuFind(DSU *dsu, int x) {
        if (dsu->parent[x] != x) {
            dsu->parent[x] = dsuFind(dsu, dsu->parent[x]);
        }
        return dsu->parent[x];
    }

    void dsuUnion(DSU *dsu, int x, int y) {
        int rootX = dsuFind(dsu, x);
        int rootY = dsuFind(dsu, y);
        if (rootX != rootY) {
            if (dsu->size[rootX] < dsu->size[rootY]) {
                dsu->parent[rootX] = rootY;
                dsu->size[rootY] += dsu->size[rootX];
            } else {
                dsu->parent[rootY] = rootX;
                dsu->size[rootX] += dsu->size[rootY];
            }
        }
    }

    void dsuFree(DSU *dsu) {
        free(dsu->parent);
        free(dsu->size);
        free(dsu);
    }

    /* Sieve of Eratosthenes to get smallest prime factors */
    int maxNum = 100000;
    int *spf = (int*)malloc((maxNum + 1) * sizeof(int)); /* smallest prime factor */
    for (int i = 0; i <= maxNum; ++i) spf[i] = i;
    for (int i = 2; i * i <= maxNum; ++i) {
        if (spf[i] == i) {
            for (int j = i * i; j <= maxNum; j += i) {
                if (spf[j] == j) {
                    spf[j] = i;
                }
            }
        }
    }
    /* Map from prime factor to first index */
    #define MAX_PRIME 100000    
    int *primeToIndex = (int*)malloc((MAX_PRIME + 1) * sizeof(int));
    for (int i = 0; i <= MAX_PRIME; ++i) primeToIndex[i] = -1;
    DSU *dsu = dsuCreate(numsSize);
    for (int i = 0; i < numsSize; ++i) {
        int num = nums[i];
        /* Factorize num using spf */
        while (num > 1) {
            int primeFactor = spf[num];
            if (primeToIndex[primeFactor] == -1) {
                primeToIndex[primeFactor] = i;
            } else {
                dsuUnion(dsu, i, primeToIndex[primeFactor]);
            }
            while (num % primeFactor == 0) {
                num /= primeFactor;
            }
        }
    }
    /* Check if all indices are connected */
    int root = dsuFind(dsu, 0);
    for (int i = 1; i < numsSize; ++i) {
        if (dsuFind(dsu, i) != root) {
            dsuFree(dsu);
            free(spf);
            free(primeToIndex);
            return false;
        }
    }
    dsuFree(dsu);
    free(spf);
    free(primeToIndex);
    return true;  
}
