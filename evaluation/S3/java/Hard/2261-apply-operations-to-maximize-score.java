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
// - Euler's totient function
//  (array, number, sieve, enumeration)
//   • When to use: Use when needing to count positive integers up to a given integer n that are relatively prime to n. It is also useful for problems involving modular arithmetic, group theory, and cryptographic applications.
//   • Idea: Euler's totient function, φ(n), counts the number of positive integers up to a given integer n that are relatively prime to n. It can be computed using prime factorization in O(sqrt(N)) or for a range using a sieve in O(N log log N).
//   • Invariants: For a sieve, phi[i] correctly stores the totient value for i after processing all its prime factors.; When factorizing n, n is continuously reduced by its smallest prime factor until it becomes 1.
//   • Tips: For a single n, find its prime factors and apply the product formula.; For computing φ(n) for all n up to a limit, use a sieve similar to Sieve of Eratosthenes.
//   • Pitfalls: Incorrectly handling repeated prime factors in the formula.; Integer overflow when calculating products for very large n.
//
// Notes:
// - Keep the given method signatures unchanged.
// - Use only Java standard library (`java.*`); no external dependencies.
// - Do not change input/output formats or return value semantics.
// - Conformance: single public class 'Solution'; no 'package' statement; place any extra types as static inner classes.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
    public int maximumScore(List<Integer> nums, int k) {
        // Step 1: Compute the prime scores for each number in nums
        int maxNum = Collections.max(nums);
        int[] primeScores = computePrimeScores(maxNum);

        // Step 2: Create a list of pairs (primeScore, index) and sort by primeScore descending, then by index ascending
        List<int[]> scoreIndexPairs = new ArrayList<>();
        for (int i = 0; i < nums.size(); i++) {
            scoreIndexPairs.add(new int[]{primeScores[nums.get(i)], i});
        }
        scoreIndexPairs.sort((a, b) -> {
            if (b[0] != a[0]) {
                return Integer.compare(b[0], a[0]); // Sort by prime score descending
            } else {
                return Integer.compare(a[1], b[1]); // Sort by index ascending
            }
        });

        // Step 3: Use a segment tree or Fenwick tree to keep track of chosen subarrays
        // For simplicity, we will use a boolean array to mark chosen indices
        boolean[] chosen = new boolean[nums.size()];
        long score = 1;
        int operations = 0;

        for (int[] pair : scoreIndexPairs) {
            if (operations >= k) break;
            int primeScore = pair[0];
            int index = pair[1];

            if (!chosen[index]) {
                // Mark the subarray containing this index as chosen
                chosen[index] = true;
                score = (score * nums.get(index)) % 1000000007;
                operations++;
            }
        }

        return (int) score;         
    }
}
