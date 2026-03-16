// Source: https://leetcode.com/problems/maximum-element-sum-of-a-complete-subset-of-indices/   |   Difficulty: Hard
//
// Problem Description:
// You are given a 1-indexed array nums. Your task is to select a complete subset from nums where every pair of selected indices multiplied is a perfect square,. i. e. if you select ai and aj, i * j must be a perfect square.
//
// Return the sum of the complete subset with the maximum sum.
//
// Example:
// Input: nums = [8,7,3,5,7,2,4,9]
//
// Output: 16
//
// Explanation:
//
// We select elements at indices 2 and 8 and 2 * 8 is a perfect square.
//
// Constraints:
// 1 <= n == nums.length <= 104
// 	1 <= nums[i] <= 109
//
// Helpful references (internal KB):
// - Euler's totient function
//  (array, number, enumeration)
//   • When to use: Use when needing to count positive integers up to n that are relatively prime to n. It is also efficient for computing totient values for all numbers in a given range.
//   • Idea: Euler's totient function, φ(n), counts positive integers less than or equal to n that are relatively prime to n. It can be computed for a single n in O(sqrt(n)) using prime factorization, or for all numbers up to N in O(N log log N) using a sieve-like algorithm.
//   • Invariants: phi[i] stores the current totient value for i, which is i initially, then updated by (1 - 1/p) for each prime p dividing i.; After iterating through all primes p up to sqrt(N), phi[i] holds the correct totient value for all i <= N.
//   • Tips: For a single n, compute φ(n) using its prime factorization.; For all φ(i) up to N, use a sieve approach similar to Sieve of Eratosthenes.
//   • Pitfalls: Confusing 'relatively prime' with 'prime number'.; Applying the multiplicative property incorrectly when numbers share common factors.
// - Sieve of Eratosthenes (array, sieve, enumeration)
//   • When to use: Use when you need to find all prime numbers up to a certain limit or precompute primality for a range. It is efficient for generating primes within a reasonable upper bound.
//   • Idea: The Sieve of Eratosthenes efficiently finds all prime numbers up to a specified integer by iteratively marking multiples of primes as composite. It achieves a time complexity of O(N log log N).
//   • Invariants: All numbers less than the current prime 'p' have already been processed.; If 'i' is marked as prime, then all its multiples less than 'i*i' have been marked composite by smaller primes.
//   • Tips: Optimize by starting inner loop from p*p, as smaller multiples would have been marked.; Use a boolean array for primality, or an integer array to store smallest prime factor (SPF).
//   • Pitfalls: Incorrectly handling 0 and 1, which are neither prime nor composite.; Off-by-one errors when setting array bounds or loop conditions.
// - Linear Sieve (array, sieve)
//   • When to use: Use when you need to find the smallest prime factor or full prime factorization for all numbers up to a given limit N in linear time. It's particularly useful for tasks requiring precomputed factorizations.
//   • Idea: The Linear Sieve computes the smallest prime factor for every number up to N, ensuring each composite number is marked exactly once by its smallest prime factor. It achieves this in O(N) time complexity.
//   • Invariants: Every number `i` from 2 to N has its `lp[i]` correctly set to its smallest prime factor.; The `primes` array contains all prime numbers less than or equal to the current iteration `i`.
//   • Tips: Stores the smallest prime factor (lp) for each number.; Efficiently generates all prime numbers up to N.
//   • Pitfalls: Higher memory usage compared to the classic Sieve of Eratosthenes due to storing lp array.; Can be slower in practice than optimized Sieve of Eratosthenes for merely generating primes.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use the C standard library only; no external packages.
// - Do not change input/output formats or return value semantics.
// - Conformance: ISO C (C89/C99/C11). Do NOT use GNU C extensions (nested functions, statement expressions, typeof, __auto_type, etc.). Avoid VLAs and non-standard builtins.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

long long maximumSum(int* nums, int numsSize) {
    // Step 1: Create an array to store the sum of elements at indices that are perfect squares
    long long *squareSums = (long long *)calloc(numsSize + 1, sizeof(long long));
    
    // Step 2: Calculate the sums for perfect square indices
    for (int i = 1; i <= numsSize; i++) {
        int squareIndex = i * i;
        if (squareIndex <= numsSize) {
            squareSums[squareIndex] += nums[i - 1];
        } else {
            break; // No need to continue if the square index exceeds the array size
        }
    }
    
    // Step 3: Find the maximum sum among the perfect square indices
    long long maxSum = 0;
    for (int i = 1; i <= numsSize; i++) {
        if (squareSums[i] > maxSum) {
            maxSum = squareSums[i];
        }
    }
    
    // Clean up allocated memory
    free(squareSums);
    
    return maxSum;      
}
