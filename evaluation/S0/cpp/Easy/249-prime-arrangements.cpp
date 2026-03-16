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
public:
    int numPrimeArrangements(int n) {
        const int MOD = 1e9 + 7;

        // Function to count prime numbers up to n using Sieve of Eratosthenes
        auto countPrimes = [](int num) {
            vector<bool> isPrime(num + 1, true);
            isPrime[0] = isPrime[1] = false;
            for (int i = 2; i * i <= num; ++i) {
                if (isPrime[i]) {
                    for (int j = i * i; j <= num; j += i) {
                        isPrime[j] = false;
                    }
                }
            }
            return count(isPrime.begin(), isPrime.end(), true);
        };

        int primeCount = countPrimes(n);
        int nonPrimeCount = n - primeCount;

        // Function to compute factorial modulo MOD
        auto factorialMod = [&](int num) {
            long long result = 1;
            for (int i = 2; i <= num; ++i) {
                result = (result * i) % MOD;
            }
            return result;
        };

        long long primeFactorial = factorialMod(primeCount);
        long long nonPrimeFactorial = factorialMod(nonPrimeCount);

        return (primeFactorial * nonPrimeFactorial) % MOD;          
    }
};
