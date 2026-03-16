// Source: https://leetcode.com/problems/check-if-any-element-has-prime-frequency/   |   Difficulty: Easy
//
// Problem Description:
// You are given an integer array nums.
//
// Return true if the frequency of any element of the array is prime, otherwise, return false.
//
// The frequency of an element x is the number of times it occurs in the array.
//
// A prime number is a natural number greater than 1 with only two factors, 1 and itself.
//
// Example:
// Input: nums = [1,2,3,4,5,4]
//
// Output: true
//
// Explanation:
//
// 4 has a frequency of two, which is a prime number.
//
// Constraints:
// 1 <= nums.length <= 100
// 	0 <= nums[i] <= 100
//
// Helpful references (internal KB):
// - Sieve of Eratosthenes (array, sieve, enumeration)
//   • When to use: Use when you need to find all prime numbers up to a certain limit or precompute primality for a range. It is efficient for generating primes within a reasonable upper bound.
//   • Idea: The Sieve of Eratosthenes efficiently finds all prime numbers up to a specified integer by iteratively marking multiples of primes as composite. It achieves a time complexity of O(N log log N).
//   • Invariants: All numbers less than the current prime 'p' have already been processed.; If 'i' is marked as prime, then all its multiples less than 'i*i' have been marked composite by smaller primes.
//   • Tips: Optimize by starting inner loop from p*p, as smaller multiples would have been marked.; Use a boolean array for primality, or an integer array to store smallest prime factor (SPF).
//   • Pitfalls: Incorrectly handling 0 and 1, which are neither prime nor composite.; Off-by-one errors when setting array bounds or loop conditions.
// - Non-negative Integers without Consecutive Ones (number, enumeration, simulation)
//   • When to use: Use when counting numbers up to a given limit that satisfy a specific bit pattern constraint, particularly when the limit is small enough for direct iteration and checking.
//   • Idea: This approach iterates through every non-negative integer from 0 up to the given limit num. For each integer, it simulates checking its binary representation to determine if it contains any two consecutive '1's.
//   • Invariants: count stores the number of integers k (where 0 <= k < i) that do not have consecutive ones.; All integers j such that 0 <= j < i have been processed.
//   • Tips: Use bitwise operations like (i & (i >> 1)) to efficiently detect consecutive ones.; Remember to include 0 in the count as it satisfies the condition (no consecutive ones).
//   • Pitfalls: Performance degradation for large num due to linear scan and per-number bit check.; Incorrectly handling the upper bound of the iteration (e.g., i < num instead of i <= num).
// - bucket-sort (array, bucket-sort)
//   • When to use: Use when sorting elements with a known, uniform distribution over a specific range. It is efficient for numbers that are uniformly distributed across a range, often achieving linear time complexity.
//   • Idea: Bucket sort distributes elements into a fixed number of buckets, sorts each bucket individually, and then concatenates them. It can achieve O(N+K) average time complexity for uniformly distributed data.
//   • Invariants: After distributing elements, each element `x` is in bucket `floor(N * x)`.; After sorting buckets, every bucket `buckets[i]` contains its elements in sorted order.
//   • Tips: Choose the number of buckets appropriately based on data distribution and range.; Normalize input data to a [0, 1) range for simpler bucket indexing.
//   • Pitfalls: Poor performance with non-uniform data distribution, potentially degrading to O(N^2).; Requires extra space for the buckets, proportional to N+K.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use standard C++ only; do NOT rely on non-standard extensions or platform-specific APIs.
// - Do not change input/output formats or return value semantics.
// - Conformance: Prefer modern standard C++ (C++11/14/17) features that are portable; avoid compiler-specific extensions (e.g., __int128 unless necessary and supported).
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
public:
    bool checkPrimeFrequency(vector<int>& nums) {
        const int MAX_NUM = 100;
        const int MAX_FREQ = nums.size();

        // Step 1: Count frequencies using bucket sort
        vector<int> frequency(MAX_NUM + 1, 0);
        for (int num : nums) {
            frequency[num]++;
        }

        // Step 2: Sieve of Eratosthenes to find all primes up to MAX_FREQ
        vector<bool> isPrime(MAX_FREQ + 1, true);
        isPrime[0] = isPrime[1] = false; // 0 and 1 are not prime numbers
        for (int i = 2; i * i <= MAX_FREQ; ++i) {
            if (isPrime[i]) {
                for (int j = i * i; j <= MAX_FREQ; j += i) {
                    isPrime[j] = false;
                }
            }
        }

        // Step 3: Check if any frequency is prime
        for (int freq : frequency) {
            if (freq > 1 && isPrime[freq]) {
                return true;
            }
        }

        return false;           
    }
};
