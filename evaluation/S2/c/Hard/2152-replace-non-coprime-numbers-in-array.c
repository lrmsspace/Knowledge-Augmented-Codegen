// Source: https://leetcode.com/problems/replace-non-coprime-numbers-in-array/   |   Difficulty: Hard
//
// Problem Description:
// You are given an array of integers nums. Perform the following steps:
//
//
// 	Find any two adjacent numbers in nums that are non-coprime.
// 	If no such numbers are found, stop the process.
// 	Otherwise, delete the two numbers and replace them with their LCM (Least Common Multiple).
// 	Repeat this process as long as you keep finding two adjacent non-coprime numbers.
//
//
// Return the final modified array. It can be shown that replacing adjacent non-coprime numbers in any arbitrary order will lead to the same result.
//
// The test cases are generated such that the values in the final array are less than or equal to 108.
//
// Two values x and y are non-coprime if GCD(x, y) > 1 where GCD(x, y) is the Greatest Common Divisor of x and y.
//
// Example:
// Input: nums = [6,4,3,2,7,6,2]
// Output: [12,7,6]
// Explanation: 
// - (6, 4) are non-coprime with LCM(6, 4) = 12. Now, nums = [12,3,2,7,6,2].
// - (12, 3) are non-coprime with LCM(12, 3) = 12. Now, nums = [12,2,7,6,2].
// - (12, 2) are non-coprime with LCM(12, 2) = 12. Now, nums = [12,7,6,2].
// - (6, 2) are non-coprime with LCM(6, 2) = 6. Now, nums = [12,7,6].
// There are no more adjacent non-coprime numbers in nums.
// Thus, the final modified array is [12,7,6].
// Note that there are other ways to obtain the same resultant array.
//
// Constraints:
// 1 <= nums.length <= 105
// 	1 <= nums[i] <= 105
// 	The test cases are generated such that the values in the final array are less than or equal to 108.
//
// Helpful references (internal KB):
// - Euler's totient function
//  (array, number, enumeration)
//   • When to use: Use when needing to count positive integers up to n that are relatively prime to n. It is also efficient for computing totient values for all numbers in a given range.
//   • Idea: Euler's totient function, φ(n), counts positive integers less than or equal to n that are relatively prime to n. It can be computed for a single n in O(sqrt(n)) using prime factorization, or for all numbers up to N in O(N log log N) using a sieve-like algorithm.
//   • Invariants: phi[i] stores the current totient value for i, which is i initially, then updated by (1 - 1/p) for each prime p dividing i.; After iterating through all primes p up to sqrt(N), phi[i] holds the correct totient value for all i <= N.
//   • Tips: For a single n, compute φ(n) using its prime factorization.; For all φ(i) up to N, use a sieve approach similar to Sieve of Eratosthenes.
//   • Pitfalls: Confusing 'relatively prime' with 'prime number'.; Applying the multiplicative property incorrectly when numbers share common factors.
// - Prüfer code (tree, heap, simulation, greedy)
//   • When to use: Use to uniquely encode a labeled tree into a sequence of numbers or reconstruct a labeled tree from such a sequence. It's valuable for counting labeled trees and problems involving tree generation.
//   • Idea: Prüfer code uniquely encodes a labeled tree into a sequence by iteratively removing the smallest-labeled leaf and recording its neighbor. This process, which can be implemented in O(N log N) or O(N) time, continues until only two nodes remain.
//   • Invariants: The generated sequence contains `k` elements after `k` leaf removals.; All nodes with degree 1 are correctly identified as leaves.
//   • Tips: Maintain an array of node degrees for O(1) degree updates.; Use a min-priority queue or a `next_leaf` pointer for efficient smallest leaf retrieval.
//   • Pitfalls: Forgetting to update neighbor degrees after removing a leaf.; Incorrectly identifying the next smallest leaf, especially when new leaves are formed.
// - Integer factorization (number, enumeration)
//   • When to use: Use when needing to decompose a composite integer into its prime factors, especially for numbers where trial division is feasible. It's suitable for problems requiring the unique prime components of a number.
//   • Idea: Integer factorization decomposes a given composite number into a product of its prime factors. The most common approach, trial division, involves testing divisibility by prime numbers up to the square root of the number, with optimizations for small primes and patterns like modulo 6.
//   • Invariants: The product of found prime factors multiplied by the current number equals the original number.; All prime factors found so far are less than or equal to the current trial divisor.
//   • Tips: Handle small prime factors (2, 3, 5) separately for efficiency.; Optimize trial division by checking only primes or numbers of form 6k +/- 1.
//   • Pitfalls: Forgetting to handle the case where the remaining number is a prime factor itself.; Inefficiently checking all numbers instead of only potential prime divisors.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use the C standard library only; no external packages.
// - Do not change input/output formats or return value semantics.
// - Conformance: ISO C (C89/C99/C11). Do NOT use GNU C extensions (nested functions, statement expressions, typeof, __auto_type, etc.). Avoid VLAs and non-standard builtins.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* replaceNonCoprimes(int* nums, int numsSize, int* returnSize) {
    int* stack = (int*)malloc(numsSize * sizeof(int));
    int sp = 0;
    int i;

    for (i = 0; i < numsSize; ++i) {
        int x = nums[i];

        while (sp > 0) {
            int y = stack[sp - 1];
            int a = x;
            int b = y;

            while (b != 0) {
                int t = a % b;
                a = b;
                b = t;
            }

            if (a == 1) {
                break;
            }

            stack[--sp] = (long long)x * y / a;
            x = stack[sp];
        }

        stack[sp++] = x;
    }

    *returnSize = sp;
    return stack;
}
