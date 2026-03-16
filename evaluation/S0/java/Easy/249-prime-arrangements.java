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

class Solution {
    public int numPrimeArrangements(int n) {
        int mod = 1_000_000_007;

        // Sieve of Eratosthenes to count primes up to n
        boolean[] isPrime = new boolean[n + 1];
        for (int i = 2; i <= n; i++) {
            isPrime[i] = true;
        }
        for (int i = 2; i * i <= n; i++) {
            if (isPrime[i]) {
                for (int j = i * i; j <= n; j += i) {
                    isPrime[j] = false;
                }
            }
        }

        int primeCount = 0;
        for (int i = 2; i <= n; i++) {
            if (isPrime[i]) {
                primeCount++;
            }
        }
        int nonPrimeCount = n - primeCount;

        long result = 1;
        for (int i = 1; i <= primeCount; i++) {
            result = (result * i) % mod;
        }
        for (int i = 1; i <= nonPrimeCount; i++) {
            result = (result * i) % mod;
        }

        return (int) result;            
    }
}
