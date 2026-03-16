// Source: https://leetcode.com/problems/number-of-different-subsequences-gcds/   |   Difficulty: Hard
//
// Problem Description:
// You are given an array nums that consists of positive integers.
//
// The GCD of a sequence of numbers is defined as the greatest integer that divides all the numbers in the sequence evenly.
//
//
// 	For example, the GCD of the sequence [4,6,16] is 2.
//
//
// A subsequence of an array is a sequence that can be formed by removing some elements (possibly none) of the array.
//
//
// 	For example, [2,5,10] is a subsequence of [1,2,1,2,4,1,5,10].
//
//
// Return the number of different GCDs among all non-empty subsequences of nums.
//
// Example:
// Input: nums = [6,10,3]
// Output: 5
// Explanation: The figure shows all the non-empty subsequences and their GCDs.
// The different GCDs are 6, 10, 3, 2, and 1.
//
// Constraints:
// 1 <= nums.length <= 105
// 	1 <= nums[i] <= 2 * 105
//
// Helpful references (internal KB):
// - Euler's totient function
//  (array, number, enumeration)
//   • When to use: Use when needing to count positive integers up to n that are relatively prime to n. It is also efficient for computing totient values for all numbers in a given range.
//   • Idea: Euler's totient function, φ(n), counts positive integers less than or equal to n that are relatively prime to n. It can be computed for a single n in O(sqrt(n)) using prime factorization, or for all numbers up to N in O(N log log N) using a sieve-like algorithm.
//   • Invariants: phi[i] stores the current totient value for i, which is i initially, then updated by (1 - 1/p) for each prime p dividing i.; After iterating through all primes p up to sqrt(N), phi[i] holds the correct totient value for all i <= N.
//   • Tips: For a single n, compute φ(n) using its prime factorization.; For all φ(i) up to N, use a sieve approach similar to Sieve of Eratosthenes.
//   • Pitfalls: Confusing 'relatively prime' with 'prime number'.; Applying the multiplicative property incorrectly when numbers share common factors.
// - Longest Increasing Subsequence (array, coordinate-compress, segment-tree, dp-1d)
//   • When to use: Use when finding the maximum length of a subsequence where elements must be strictly increasing. It is applicable for problems requiring optimal substructure on sequences with an increasing property.
//   • Idea: The Longest Increasing Subsequence (LIS) problem finds the longest subsequence of a given sequence such that all elements of the subsequence are in increasing order. It can be solved in O(N log N) time using dynamic programming with binary search or a segment tree with coordinate compression.
//   • Invariants: The `dp` array (or segment tree) stores information about the smallest ending element for increasing subsequences of various lengths.; The `dp` array, if used, remains sorted in strictly increasing order.
//   • Tips: The O(N log N) solution uses a `dp` array storing the smallest ending element for all increasing subsequences of a given length.; Binary search (`lower_bound`) efficiently finds the correct position to update in the `dp` array.
//   • Pitfalls: Confusing subsequence with subarray, which requires contiguous elements.; Incorrectly handling duplicates; LIS typically requires strictly increasing elements.
// - Lattice points inside non-lattice polygon (number, recursion, counting, gcd)
//   • When to use: Use when counting pairs or elements satisfying divisibility or GCD conditions. Also applicable for summing functions over pairs using number theory properties.
//   • Idea: This approach leverages number theoretic properties like GCD, LCM, and prime factorization to efficiently count elements or pairs satisfying specific criteria. It often involves iterating through divisors or multiples, achieving complexities like O(N log N) or O(sqrt N) per query.
//   • Invariants: All numbers processed so far have their relevant number-theoretic properties (e.g., prime factors, divisors) correctly determined.; The current count or sum accurately reflects all valid combinations found up to the current iteration.
//   • Tips: Precompute primes or divisors using a sieve for efficiency.; Utilize properties of GCD and LCM, such as gcd(a,b) * lcm(a,b) = a * b.
//   • Pitfalls: Overcounting or undercounting when using inclusion-exclusion.; Integer overflow with large products or sums.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use the C standard library only; no external packages.
// - Do not change input/output formats or return value semantics.
// - Conformance: ISO C (C89/C99/C11). Do NOT use GNU C extensions (nested functions, statement expressions, typeof, __auto_type, etc.). Avoid VLAs and non-standard builtins.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

int countDifferentSubsequenceGCDs(int* nums, int numsSize) {
    int maxNum = 0;
    for (int i = 0; i < numsSize; ++i) {
        if (nums[i] > maxNum) {
            maxNum = nums[i];
        }
    }

    int count = 0;
    for (int i = 1; i <= maxNum; ++i) {
        int gcd = 0;
        for (int j = i; j <= maxNum; j += i) {
            for (int k = 0; k < numsSize; ++k) {
                if (nums[k] == j) {
                    if (gcd == 0) {
                        gcd = j;
                    } else {
                        // Compute GCD using Euclid's algorithm
                        int a = gcd, b = j;
                        while (b != 0) {
                            int temp = b;
                            b = a % b;
                            a = temp;
                        }
                        gcd = a;
                    }
                    break; // No need to check further for this multiple
                }
            }
        }
        if (gcd == i) {
            count++;
        }
    }

    return count;       
}
