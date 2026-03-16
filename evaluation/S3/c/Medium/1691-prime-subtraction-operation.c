// Source: https://leetcode.com/problems/prime-subtraction-operation/   |   Difficulty: Medium
//
// Problem Description:
// You are given a 0-indexed integer array nums of length n.
//
// You can perform the following operation as many times as you want:
//
//
// 	Pick an index i that you haven’t picked before, and pick a prime p strictly less than nums[i], then subtract p from nums[i].
//
//
// Return true if you can make nums a strictly increasing array using the above operation and false otherwise.
//
// A strictly increasing array is an array whose each element is strictly greater than its preceding element.
//
// Example:
// Input: nums = [4,9,6,10]
// Output: true
// Explanation: In the first operation: Pick i = 0 and p = 3, and then subtract 3 from nums[0], so that nums becomes [1,9,6,10].
// In the second operation: i = 1, p = 7, subtract 7 from nums[1], so nums becomes equal to [1,2,6,10].
// After the second operation, nums is sorted in strictly increasing order, so the answer is true.
//
// Constraints:
// 1 <= nums.length <= 1000
// 	1 <= nums[i] <= 1000
// 	nums.length == n
//
// Helpful references (internal KB):
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
// - Linear Sieve (array, sieve)
//   • When to use: Use when you need to find all prime numbers up to a given limit N, or compute the least prime factor for all numbers in that range, efficiently in linear time.
//   • Idea: The Linear Sieve finds all prime numbers up to N in O(N) time by ensuring each composite number is marked exactly once by its least prime factor. It also computes the least prime factor for every number up to N.
//   • Invariants: The 'primes' list always contains all prime numbers found so far in increasing order.; lpf[i] stores the least prime factor of 'i' if 'i' is composite, or 'i' itself if 'i' is prime.
//   • Tips: Store the least prime factor (LPF) for each number in an array.; Maintain a dynamically growing list of primes found so far.
//   • Pitfalls: Incorrectly marking multiples can lead to O(N log log N) or worse complexity.; Forgetting to store the least prime factor can break the linear time guarantee.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use the C standard library only; no external packages.
// - Do not change input/output formats or return value semantics.
// - Conformance: ISO C (C89/C99/C11). Do NOT use GNU C extensions (nested functions, statement expressions, typeof, __auto_type, etc.). Avoid VLAs and non-standard builtins.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

bool primeSubOperation(int* nums, int numsSize) {
    // Step 1: Generate all prime numbers less than 1000 using the Sieve of Eratosthenes
    bool isPrime[1000];
    for (int i = 0; i < 1000; i++) {
        isPrime[i] = true;
    }
    isPrime[0] = isPrime[1] = false; // 0 and 1 are not prime

    for (int i = 2; i * i < 1000; i++) {
        if (isPrime[i]) {
            for (int j = i * i; j < 1000; j += i) {
                isPrime[j] = false;
            }
        }
    }

    // Step 2: Create an array to store the prime numbers
    int primes[168]; // There are 168 prime numbers less than 1000
    int primeCount = 0;
    for (int i = 2; i < 1000; i++) {
        if (isPrime[i]) {
            primes[primeCount++] = i;
        }
    }

    // Step 3: Try to make the array strictly increasing by subtracting primes
    for (int i = numsSize - 1; i > 0; i--) {
        if (nums[i] <= nums[i - 1]) {
            bool canSubtract = false;
            for (int j = primeCount - 1; j >= 0; j--) {
                if (primes[j] < nums[i]) {
                    nums[i] -= primes[j];
                    if (nums[i] > nums[i - 1]) {
                        canSubtract = true;
                        break;
                    }
                }
            }
            if (!canSubtract) {
                return false;
            }
        }
    }

    return true;        
}
