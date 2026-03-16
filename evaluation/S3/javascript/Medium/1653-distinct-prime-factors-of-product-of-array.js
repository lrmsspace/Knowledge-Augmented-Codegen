// Source: https://leetcode.com/problems/distinct-prime-factors-of-product-of-array/   |   Difficulty: Medium
//
// Problem Description:
// Given an array of positive integers nums, return the number of distinct prime factors in the product of the elements of nums.
//
// Note that:
//
//
// 	A number greater than 1 is called prime if it is divisible by only 1 and itself.
// 	An integer val1 is a factor of another integer val2 if val2 / val1 is an integer.
//
// Example:
// Input: nums = [2,4,3,7,10,6]
// Output: 4
// Explanation:
// The product of all the elements in nums is: 2 * 4 * 3 * 7 * 10 * 6 = 10080 = 25 * 32 * 5 * 7.
// There are 4 distinct prime factors so we return 4.
//
// Constraints:
// 1 <= nums.length <= 104
// 	2 <= nums[i] <= 1000
//
// Helpful references (internal KB):
// - Euler's totient function
//  (array, number, enumeration)
//   • When to use: Use when needing to count positive integers up to n that are relatively prime to n. It is also efficient for computing totient values for all numbers in a given range.
//   • Idea: Euler's totient function, φ(n), counts positive integers less than or equal to n that are relatively prime to n. It can be computed for a single n in O(sqrt(n)) using prime factorization, or for all numbers up to N in O(N log log N) using a sieve-like algorithm.
//   • Invariants: phi[i] stores the current totient value for i, which is i initially, then updated by (1 - 1/p) for each prime p dividing i.; After iterating through all primes p up to sqrt(N), phi[i] holds the correct totient value for all i <= N.
//   • Tips: For a single n, compute φ(n) using its prime factorization.; For all φ(i) up to N, use a sieve approach similar to Sieve of Eratosthenes.
//   • Pitfalls: Confusing 'relatively prime' with 'prime number'.; Applying the multiplicative property incorrectly when numbers share common factors.
// - Sieve of Eratosthenes (array, bitset, sieve)
//   • When to use: When you need to find all prime numbers up to a certain limit N, or efficiently check primality for many numbers within that range. It is ideal for precomputing primes.
//   • Idea: The Sieve of Eratosthenes efficiently finds all prime numbers up to a specified integer N by iteratively marking multiples of each prime. It achieves O(N log log N) time complexity and O(N) space.
//   • Invariants: For any number i less than the current prime p, is_prime[i] correctly reflects its primality.; All multiples of primes smaller than the current prime p have already been marked as composite.
//   • Tips: Optimize by starting marking multiples from p*p for each prime p.; Use a bitset for memory efficiency when N is large.
//   • Pitfalls: Forgetting to explicitly handle 0 and 1 as non-prime.; Incorrectly marking multiples, e.g., starting from 2*p instead of p*p.
// - Integer factorization (number, array, enumeration, sieve, counting)
//   • When to use: Use when needing to find the prime factors of a composite number, especially for relatively small numbers or as a base case for more advanced algorithms.
//   • Idea: This algorithm finds the prime factorization of an integer by iteratively dividing it by its smallest prime factors. It typically checks divisors up to the square root of the number, achieving an O(sqrt(N)) time complexity.
//   • Invariants: The product of all found prime factors multiplied by the current remaining number equals the original input number.; All prime factors found so far are less than or equal to the current divisor being tested.
//   • Tips: Perform a primality test first to avoid unnecessary factorization attempts.; Only check divisors up to the square root of the number.
//   • Pitfalls: Trial division is pseudo-polynomial time, making it inefficient for very large numbers.; Forgetting to handle the case where the remaining number after division is itself a prime greater than its original square root.
//
// Notes:
// - Keep the given function signature unchanged.
// - Do not add custom input parsing or console I/O unless the template explicitly requires it; rely on parameters/return value only.
// - Use standard ECMAScript features supported by LeetCode (Node.js runtime); no external packages.
// - Be careful with number precision: JavaScript Number is double; use BigInt only when necessary and keep return type consistent with the problem requirements.
// - If you introduce helper functions, define them in the same file and avoid relying on global mutable state across test cases.

/**
 * @param {number[]} nums
 * @return {number}
 */
var distinctPrimeFactors = function(nums) {
    const maxNum = Math.max(...nums);
    const isPrime = new Array(maxNum + 1).fill(true);
    isPrime[0] = false;
    isPrime[1] = false;
    
    for (let i = 2; i * i <= maxNum; i++) {
        if (isPrime[i]) {
            for (let j = i * i; j <= maxNum; j += i) {
                isPrime[j] = false;
            }
        }
    }
    
    const primeFactors = new Set();
    
    for (const num of nums) {
        let temp = num;
        for (let i = 2; i * i <= temp; i++) {
            if (temp % i === 0) {
                if (isPrime[i]) {
                    primeFactors.add(i);
                }
                while (temp % i === 0) {
                    temp /= i;
                }
            }
        }
        if (temp > 1 && isPrime[temp]) {
            primeFactors.add(temp);
        }
    }
    
    return primeFactors.size;
};
