// Source: https://leetcode.com/problems/number-of-squareful-arrays/   |   Difficulty: Hard
//
// Problem Description:
// An array is squareful if the sum of every pair of adjacent elements is a perfect square.
//
// Given an integer array nums, return the number of permutations of nums that are squareful.
//
// Two permutations perm1 and perm2 are different if there is some index i such that perm1[i] != perm2[i].
//
// Example:
// Input: nums = [1,17,8]
// Output: 2
// Explanation: [1,8,17] and [17,8,1] are the valid permutations.
//
// Constraints:
// 1 <= nums.length <= 12
// 	0 <= nums[i] <= 109
//
// Helpful references (internal KB):
// - Placing Bishops on a Chessboard (array, counting, dp-2d)
//   • When to use: Use when counting non-attacking piece placements on a grid, especially when the problem can be decomposed into independent subproblems based on board properties like diagonals.
//   • Idea: This algorithm employs 2D dynamic programming to count the total number of ways to place non-attacking bishops on a chessboard. It leverages the independence of placements on black and white squares/diagonals, achieving a polynomial time complexity.
//   • Invariants: For any diagonal `i`, `D[i][j]` represents the number of ways to place `j` bishops on diagonal `i`.; Bishops placed on black diagonals do not attack bishops placed on white diagonals.
//   • Tips: Decompose the problem into independent subproblems for black and white squares/diagonals.; Identify the state for DP, typically `dp[diagonal_index][bishops_placed]`.
//   • Pitfalls: Incorrectly calculating the number of squares on each diagonal.; Overlapping bishops if diagonal definitions are not precise.
// - Burnside's lemma / Pólya enumeration theorem (array, number, enumeration, simulation)
//   • When to use: Use when counting the number of distinct configurations or arrangements of objects under a set of symmetry operations, where configurations are considered identical if one can be transformed into another by a group action.
//   • Idea: Burnside's Lemma and Pólya Enumeration Theorem are combinatorial tools used to count the number of distinct objects under a group of symmetries. Both typically involve iterating through group elements and analyzing permutation cycle structures, often resulting in polynomial time complexity depending on group size and element analysis.
//   • Invariants: The set of group elements considered remains consistent throughout the summation.; Each group element's cycle decomposition is correctly identified.
//   • Tips: Identify the group of symmetry operations acting on the objects.; For each group element, determine its permutation cycle structure.
//   • Pitfalls: Incorrectly identifying the full set of distinct group operations.; Errors in determining the cycle structure of permutations.
// - Euler's totient function
//  (array, number, enumeration)
//   • When to use: Use when needing to count positive integers up to n that are relatively prime to n. It is also efficient for computing totient values for all numbers in a given range.
//   • Idea: Euler's totient function, φ(n), counts positive integers less than or equal to n that are relatively prime to n. It can be computed for a single n in O(sqrt(n)) using prime factorization, or for all numbers up to N in O(N log log N) using a sieve-like algorithm.
//   • Invariants: phi[i] stores the current totient value for i, which is i initially, then updated by (1 - 1/p) for each prime p dividing i.; After iterating through all primes p up to sqrt(N), phi[i] holds the correct totient value for all i <= N.
//   • Tips: For a single n, compute φ(n) using its prime factorization.; For all φ(i) up to N, use a sieve approach similar to Sieve of Eratosthenes.
//   • Pitfalls: Confusing 'relatively prime' with 'prime number'.; Applying the multiplicative property incorrectly when numbers share common factors.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use the C standard library only; no external packages.
// - Do not change input/output formats or return value semantics.
// - Conformance: ISO C (C89/C99/C11). Do NOT use GNU C extensions (nested functions, statement expressions, typeof, __auto_type, etc.). Avoid VLAs and non-standard builtins.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

int numSquarefulPerms(int* nums, int numsSize) {
    // This problem can be solved using backtracking to generate all permutations of the input array and checking if each permutation is squareful. To optimize the solution, we can use a hash set to avoid generating duplicate permutations when there are duplicate numbers in the input array.

    // Helper function to check if a number is a perfect square
    int isPerfectSquare(int n) {
        int root = (int)sqrt(n);
        return root * root == n;
    }

    // Backtracking function to generate permutations and count squareful ones
    void backtrack(int* nums, int numsSize, int* used, int* perm, int depth, int* count) {
        if (depth == numsSize) {
            (*count)++;
            return;
        }
        for (int i = 0; i < numsSize; i++) {
            if (used[i]) continue;
            // Skip duplicates
            if (i > 0 && nums[i] == nums[i - 1] && !used[i - 1]) continue;
            // Check if the current number can be placed next to the previous one
            if (depth > 0 && !isPerfectSquare(perm[depth - 1] + nums[i])) continue;

            used[i] = 1;
            perm[depth] = nums[i];
            backtrack(nums, numsSize, used, perm, depth + 1, count);
            used[i] = 0;
        }
    }

    // Sort the input array to handle duplicates easily
    qsort(nums, numsSize, sizeof(int), (int (*)(const void *, const void *))strcmp);

    int count = 0;
    int* used = (int*)calloc(numsSize, sizeof(int));
    int* perm = (int*)malloc(numsSize * sizeof(int));

    backtrack(nums, numsSize, used, perm, 0, &count);

    free(used);
    free(perm);

    return count;       
}
