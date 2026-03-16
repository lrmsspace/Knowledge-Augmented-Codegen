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

int numPrimeArrangements(int n) {
    const int MOD = 1e9 + 7;

    // Function to count prime numbers up to n using Sieve of Eratosthenes
    int countPrimes(int n) {
        if (n < 2) return 0;
        bool isPrime[n + 1];
        for (int i = 0; i <= n; i++) isPrime[i] = true;
        isPrime[0] = isPrime[1] = false;

        for (int i = 2; i * i <= n; i++) {
            if (isPrime[i]) {
                for (int j = i * i; j <= n; j += i) {
                    isPrime[j] = false;
                }
            }
        }

        int count = 0;
        for (int i = 2; i <= n; i++) {
            if (isPrime[i]) count++;
        }
        return count;
    }

    // Function to compute factorial modulo MOD
    long long factorial(int x) {
        long long result = 1;
        for (int i = 2; i <= x; i++) {
            result = (result * i) % MOD;
        }
        return result;
    }

    int primeCount = countPrimes(n);
    int nonPrimeCount = n - primeCount;

    long long primeFactorial = factorial(primeCount);
    long long nonPrimeFactorial = factorial(nonPrimeCount);

    return (primeFactorial * nonPrimeFactorial) % MOD;      
}
