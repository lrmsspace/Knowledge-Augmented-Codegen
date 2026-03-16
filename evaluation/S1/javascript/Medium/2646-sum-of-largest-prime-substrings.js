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
// - Do not add custom input parsing or console I/O unless the template explicitly requires it; rely on parameters/return value only.
// - Use standard ECMAScript features supported by LeetCode (Node.js runtime); no external packages.
// - Be careful with number precision: JavaScript Number is double; use BigInt only when necessary and keep return type consistent with the problem requirements.
// - If you introduce helper functions, define them in the same file and avoid relying on global mutable state across test cases.

/**
 * @param {string} s
 * @return {number}
 */
var sumOfLargestPrimes = function(s) {
    const MAX = 10 ** 6; // Maximum possible prime from substrings of length <= 6
    const isPrime = new Array(MAX + 1).fill(true);
    isPrime[0] = isPrime[1] = false;
    
    // Sieve of Eratosthenes to find all primes up to MAX
    for (let i = 2; i * i <= MAX; i++) {
        if (isPrime[i]) {
            for (let j = i * i; j <= MAX; j += i) {
                isPrime[j] = false;
            }
        }
    }

    const primesSet = new Set();
    
    // Generate all unique substrings and check for primality
    for (let start = 0; start < s.length; start++) {
        for (let end = start + 1; end <= s.length; end++) {
            const numStr = s.substring(start, end).replace(/^0+/, ''); // Remove leading zeros
            if (numStr.length === 0) continue; // Skip empty substring after removing zeros
            const num = parseInt(numStr, 10);
            if (num <= MAX && isPrime[num]) {
                primesSet.add(num);
            }
        }
    }

    const primesArray = Array.from(primesSet).sort((a, b) => b - a); // Sort in descending order
    return primesArray.slice(0, 3).reduce((sum, val) => sum + val, 0); // Sum the top 3 primes
};
