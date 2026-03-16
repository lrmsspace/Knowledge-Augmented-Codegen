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

class Solution {
public:
    int countPrimes(int n) {
        if (n < 3) return 0;

        vector<bool> isPrime(n, true);
        isPrime[0] = isPrime[1] = false;

        for (int i = 2; i * i < n; ++i) {
            if (isPrime[i]) {
                for (int j = i * i; j < n; j += i) {
                    isPrime[j] = false;
                }
            }
        }

        return count(isPrime.begin(), isPrime.end(), true);         
    }
};
