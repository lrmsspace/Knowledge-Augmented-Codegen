// Source: https://leetcode.com/problems/count-primes/   |   Difficulty: Medium
//
// Problem Description:
// Given an integer n, return the number of prime numbers that are strictly less than n.
//
// Example:
// Input: n = 10
// Output: 4
// Explanation: There are 4 prime numbers less than 10, they are 2, 3, 5, 7.
//
// Constraints:
// 0 <= n <= 5 * 106
//

int countPrimes(int n) {
    if (n <= 2) {
        return 0;
    }

    // Initialize a boolean array to track prime numbers
    bool is_prime[n];
    for (int i = 0; i < n; i++) {
        is_prime[i] = true;
    }
    is_prime[0] = is_prime[1] = false; // 0 and 1 are not prime numbers

    // Sieve of Eratosthenes algorithm
    for (int i = 2; i * i < n; i++) {
        if (is_prime[i]) {
            for (int j = i * i; j < n; j += i) {
                is_prime[j] = false;
            }
        }
    }

    // Count the number of prime numbers
    int count = 0;
    for (int i = 2; i < n; i++) {
        if (is_prime[i]) {
            count++;
        }
    }

    return count;       
}
