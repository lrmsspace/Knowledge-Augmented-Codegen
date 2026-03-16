// Source: https://leetcode.com/problems/apply-operations-to-maximize-score/   |   Difficulty: Hard
//
// Problem Description:
// You are given an array nums of n positive integers and an integer k.
//
// Initially, you start with a score of 1. You have to maximize your score by applying the following operation at most k times:
//
//
// 	Choose any non-empty subarray nums[l, ..., r] that you haven't chosen previously.
// 	Choose an element x of nums[l, ..., r] with the highest prime score. If multiple such elements exist, choose the one with the smallest index.
// 	Multiply your score by x.
//
//
// Here, nums[l, ..., r] denotes the subarray of nums starting at index l and ending at the index r, both ends being inclusive.
//
// The prime score of an integer x is equal to the number of distinct prime factors of x. For example, the prime score of 300 is 3 since 300 = 2 * 2 * 3 * 5 * 5.
//
// Return the maximum possible score after applying at most k operations.
//
// Since the answer may be large, return it modulo 109 + 7.
//
// Example:
// Input: nums = [8,3,9,3,8], k = 2
// Output: 81
// Explanation: To get a score of 81, we can apply the following operations:
// - Choose subarray nums[2, ..., 2]. nums[2] is the only element in this subarray. Hence, we multiply the score by nums[2]. The score becomes 1 * 9 = 9.
// - Choose subarray nums[2, ..., 3]. Both nums[2] and nums[3] have a prime score of 1, but nums[2] has the smaller index. Hence, we multiply the score by nums[2]. The score becomes 9 * 9 = 81.
// It can be proven that 81 is the highest score one can obtain.
//
// Constraints:
// 1 <= nums.length == n <= 105
// 	1 <= nums[i] <= 105
// 	1 <= k <= min(n * (n + 1) / 2, 109)
//
// Helpful references (internal KB):
// - Sieve of Eratosthenes (array, sieve, enumeration)
//   • When to use: Use when you need to find all prime numbers up to a certain limit or precompute primality for a range. It is efficient for generating primes within a reasonable upper bound.
//   • Idea: The Sieve of Eratosthenes efficiently finds all prime numbers up to a specified integer by iteratively marking multiples of primes as composite. It achieves a time complexity of O(N log log N).
//   • Invariants: All numbers less than the current prime 'p' have already been processed.; If 'i' is marked as prime, then all its multiples less than 'i*i' have been marked composite by smaller primes.
//   • Tips: Optimize by starting inner loop from p*p, as smaller multiples would have been marked.; Use a boolean array for primality, or an integer array to store smallest prime factor (SPF).
//   • Pitfalls: Incorrectly handling 0 and 1, which are neither prime nor composite.; Off-by-one errors when setting array bounds or loop conditions.
// - Search the subarray with the maximum/minimum sum (array, greedy, dp-1d)
//   • When to use: When you need to find the contiguous subarray within a one-dimensional array of numbers that has the largest or smallest sum, typically in linear time.
//   • Idea: This algorithm efficiently finds the maximum (or minimum) sum of a contiguous subarray by iterating through the array and maintaining a current sum, resetting it if it becomes detrimental. It operates in O(N) time complexity with O(1) space complexity.
//   • Invariants: `global_max` holds the maximum sum of any contiguous subarray encountered up to the current element.; `current_max` holds the maximum sum of a contiguous subarray ending at the current element.
//   • Tips: Initialize current and global maximums appropriately (e.g., to negative infinity or first element).; Adapt for minimum sum by resetting current sum if it becomes positive.
//   • Pitfalls: Failing to correctly initialize maximum/minimum sum variables.; Not handling arrays where all elements are negative (for max sum) or positive (for min sum).
// - Number of divisors / sum of divisors (number, counting, enumeration)
//   • When to use: Use this when you need to efficiently calculate the total count or sum of all positive divisors for a given integer. It is applicable in number theory problems or combinatorial tasks involving factors.
//   • Idea: This method computes the number of divisors and sum of divisors of an integer n by first finding its prime factorization. The core idea leverages properties of multiplicative functions, with a typical complexity of O(sqrt(n)) for factorization.
//   • Invariants: During prime factorization, temp_n always holds the remaining unfactored part of the original number.; The current_prime_factor iterates through potential prime divisors in increasing order.
//   • Tips: First find the prime factorization n = p1^a1 * p2^a2 * ... * pk^ak.; Number of divisors d(n) = (a1+1)(a2+1)...(ak+1).
//   • Pitfalls: Forgetting to handle the special case of n=1 (1 divisor, sum 1).; Incorrectly calculating powers or sums, especially for large exponents.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use the C standard library only; no external packages.
// - Do not change input/output formats or return value semantics.
// - Conformance: ISO C (C89/C99/C11). Do NOT use GNU C extensions (nested functions, statement expressions, typeof, __auto_type, etc.). Avoid VLAs and non-standard builtins.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

int maximumScore(int* nums, int numsSize, int k) {
    const int MOD = 1000000007;

    /* Sieve of Eratosthenes to compute prime scores */
    int maxNum = 100000;
    int spf[100001]; /* smallest prime factor */
    for (int i = 0; i <= maxNum; ++i) spf[i] = 0;
    for (int i = 2; i * i <= maxNum; ++i) {
        if (spf[i] == 0) {
            for (int j = i * i; j <= maxNum; j += i) {
                if (spf[j] == 0) spf[j] = i;
            }
        }
    }
    for (int i = 2; i <= maxNum; ++i) {
        if (spf[i] == 0) spf[i] = i;
    }

    int primeScores[100001];
    for (int i = 1; i <= maxNum; ++i) {
        int count = 0, x = i;
        int lastFactor = 0;
        while (x > 1) {
            int factor = spf[x];
            if (factor != lastFactor) {
                count++;
                lastFactor = factor;
            }
            x /= factor;
        }
        primeScores[i] = count;
    }

    /* Create an array of indices sorted by prime score desc, then by value desc */
    int indices[numsSize];
    for (int i = 0; i < numsSize; ++i) indices[i] = i;
    qsort(indices, numsSize, sizeof(int), 
          (int (*)(const void*, const void*))[](const int *a, const int *b) {
              int psA = primeScores[*(int*)a];
              int psB = primeScores[*(int*)b];
              if (psA != psB) return psB - psA;
              return (*(int*)b) - (*(int*)a);
          });

    /* Use a stack to find the next greater element on both sides */
    int left[numsSize], right[numsSize];
    int stack[numsSize], top = -1;

    for (int i = 0; i < numsSize; ++i) {
        while (top >= 0 && nums[stack[top]] < nums[i]) {
            right[stack[top--]] = i;
        }
        stack[++top] = i;
    }
    while (top >= 0) {
        right[stack[top--]] = numsSize;
    }
    for (int i = numsSize - 1; i >= 0; --i) {
        while (top >= 0 && nums[stack[top]] <= nums[i]) {
            left[stack[top--]] = i;
        }
        stack[++top] = i;
    }
    while (top >= 0) {
        left[stack[top--]] = -1;
    }
    /* Calculate the maximum score */
    long long score = 1;
    for (int i = 0; i < numsSize && k > 0; ++i) {
        int idx = indices[i];
        long long count = (long long)(idx - left[idx]) * (right[idx] - idx);
        long long use = (count < k) ? count : k;
        score = (score * modPow(nums[idx], use, MOD)) % MOD;
        k -= use;
    }
    return (int)score;
}
