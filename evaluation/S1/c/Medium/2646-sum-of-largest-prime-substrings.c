// Source: https://leetcode.com/problems/sum-of-largest-prime-substrings/   |   Difficulty: Medium
//
// Problem Description:
// Given a string s, find the sum of the 3 largest unique prime numbers that can be formed using any of its substrings.
//
// Return the sum of the three largest unique prime numbers that can be formed. If fewer than three exist, return the sum of all available primes. If no prime numbers can be formed, return 0.
//
// Note: Each prime number should be counted only once, even if it appears in multiple substrings. Additionally, when converting a substring to an integer, any leading zeros are ignored.
//
// Example:
// Input: s = "12234"
//
// Output: 1469
//
// Explanation:
//
//
// 	The unique prime numbers formed from the substrings of "12234" are 2, 3, 23, 223, and 1223.
// 	The 3 largest primes are 1223, 223, and 23. Their sum is 1469.
//
// Constraints:
// 1 <= s.length <= 10
// 	s consists of only digits.
//
// Helpful references (internal KB):
// - Sieve of Eratosthenes (array, bitset, sieve)
//   • When to use: When you need to find all prime numbers up to a certain limit N, or efficiently check primality for many numbers within that range. It is ideal for precomputing primes.
//   • Idea: The Sieve of Eratosthenes efficiently finds all prime numbers up to a specified integer N by iteratively marking multiples of each prime. It achieves O(N log log N) time complexity and O(N) space.
//   • Invariants: For any number i less than the current prime p, is_prime[i] correctly reflects its primality.; All multiples of primes smaller than the current prime p have already been marked as composite.
//   • Tips: Optimize by starting marking multiples from p*p for each prime p.; Use a bitset for memory efficiency when N is large.
//   • Pitfalls: Forgetting to explicitly handle 0 and 1 as non-prime.; Incorrectly marking multiples, e.g., starting from 2*p instead of p*p.
// - Generating all K-combinations (array, enumeration, greedy)
//   • When to use: Use this when you need to iterate through all possible subsets of a fixed size K from a larger set, especially when a specific order like lexicographical is required.
//   • Idea: This algorithm systematically generates all unique combinations of K elements from a set of N elements. It typically proceeds in lexicographical order, allowing for efficient enumeration of all C(N, K) possibilities.
//   • Invariants: The current combination C is always sorted: C[0] < C[1] < ... < C[K-1].; All elements C[i] are distinct and within the range [0, N-1] (assuming 0-indexed).
//   • Tips: Start with the smallest lexicographical combination (e.g., {1, 2, ..., K}).; To find the next combination, locate the rightmost element that can be incremented.
//   • Pitfalls: Incorrectly handling boundary conditions when incrementing elements.; Duplicating combinations if not careful with the increment logic.
// - Search the subarray with the maximum/minimum sum (array, greedy, dp-1d)
//   • When to use: When you need to find the contiguous subarray within a one-dimensional array of numbers that has the largest or smallest sum, typically in linear time.
//   • Idea: This algorithm efficiently finds the maximum (or minimum) sum of a contiguous subarray by iterating through the array and maintaining a current sum, resetting it if it becomes detrimental. It operates in O(N) time complexity with O(1) space complexity.
//   • Invariants: `global_max` holds the maximum sum of any contiguous subarray encountered up to the current element.; `current_max` holds the maximum sum of a contiguous subarray ending at the current element.
//   • Tips: Initialize current and global maximums appropriately (e.g., to negative infinity or first element).; Adapt for minimum sum by resetting current sum if it becomes positive.
//   • Pitfalls: Failing to correctly initialize maximum/minimum sum variables.; Not handling arrays where all elements are negative (for max sum) or positive (for min sum).
//
// Notes:
// - Keep the given function signature unchanged.
// - Use the C standard library only; no external packages.
// - Do not change input/output formats or return value semantics.
// - Conformance: ISO C (C89/C99/C11). Do NOT use GNU C extensions (nested functions, statement expressions, typeof, __auto_type, etc.). Avoid VLAs and non-standard builtins.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

long long sumOfLargestPrimes(char* s) {
    int maxNum = 10000000; // Maximum number based on substring length (up to 10 digits)
    char isPrime[maxNum + 1];
    for (int i = 0; i <= maxNum; i++) {
        isPrime[i] = 1; // Assume all numbers are prime initially
    }
    isPrime[0] = isPrime[1] = 0; // 0 and 1 are not prime numbers

    // Sieve of Eratosthenes to find all primes up to maxNum
    for (int i = 2; i * i <= maxNum; i++) {
        if (isPrime[i]) {
            for (int j = i * i; j <= maxNum; j += i) {
                isPrime[j] = 0; // Mark multiples of i as non-prime
            }
        }
    }

    // Use a set to store unique prime numbers found in substrings
    char foundPrimes[maxNum + 1];
    for (int i = 0; i <= maxNum; i++) {
        foundPrimes[i] = 0;
    }

    int len = strlen(s);
    // Generate all substrings and check for primality
    for (int i = 0; i < len; i++) {
        long long num = 0;
        for (int j = i; j < len; j++) {
            num = num * 10 + (s[j] - '0');
            if (num > maxNum) break; // No need to check beyond maxNum
            if (isPrime[num]) {
                foundPrimes[num] = 1; // Mark this prime as found
            }
        }
    }

    // Collect all unique primes found
    long long primesList[maxNum];
    int primesCount = 0;
    for (int i = 2; i <= maxNum; i++) {
        if (foundPrimes[i]) {
            primesList[primesCount++] = i;
        }
    }

    // Sort the primes in descending order
    for (int i = 0; i < primesCount - 1; i++) {
        for (int j = 0; j < primesCount - i - 1; j++) {
            if (primesList[j] < primesList[j + 1]) {
                long long temp = primesList[j];
                primesList[j] = primesList[j + 1];
                primesList[j + 1] = temp;
            }
        }
    }
    // Sum the three largest unique primes
    long long sum = 0;
    for (int i = 0; i < primesCount && i < 3; i++) {
        sum += primesList[i];
    }
    return sum;
}
