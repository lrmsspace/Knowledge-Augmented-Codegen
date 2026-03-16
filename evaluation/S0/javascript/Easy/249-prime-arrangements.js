// Source: https://leetcode.com/problems/prime-arrangements/   |   Difficulty: Easy
//
// Problem Description:
// Return the number of permutations of 1 to n so that prime numbers are at prime indices (1-indexed.)
//
// (Recall that an integer is prime if and only if it is greater than 1, and cannot be written as a product of two positive integers both smaller than it.)
//
// Since the answer may be large, return the answer modulo 10^9 + 7.
//
// Example:
// Input: n = 5
// Output: 12
// Explanation: For example [1,2,5,4,3] is a valid permutation, but [5,2,3,4,1] is not because the prime number 5 is at index 1.
//
// Constraints:
// 1 <= n <= 100
//

/**
 * @param {number} n
 * @return {number}
 */
var numPrimeArrangements = function(n) {
    const MOD = 1e9 + 7;

    // Helper function to count primes up to n using Sieve of Eratosthenes
    const countPrimes = (num) => {
        const isPrime = new Array(num + 1).fill(true);
        isPrime[0] = false;
        isPrime[1] = false;
        for (let i = 2; i * i <= num; i++) {
            if (isPrime[i]) {
                for (let j = i * i; j <= num; j += i) {
                    isPrime[j] = false;
                }
            }
        }
        let primeCount = 0;
        for (let i = 2; i <= num; i++) {
            if (isPrime[i]) primeCount++;
        }
        return primeCount;
    };

    // Helper function to calculate factorial modulo MOD
    const factorialMod = (num) => {
        let result = 1;
        for (let i = 1; i <= num; i++) {
            result = (result * i) % MOD;
        }
        return result;
    };

    const primeCount = countPrimes(n);
    const nonPrimeCount = n - primeCount;

    return (factorialMod(primeCount) * factorialMod(nonPrimeCount)) % MOD;
};