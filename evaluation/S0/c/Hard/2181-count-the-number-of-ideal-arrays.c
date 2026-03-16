// Source: https://leetcode.com/problems/count-the-number-of-ideal-arrays/   |   Difficulty: Hard
//
// Problem Description:
// You are given two integers n and maxValue, which are used to describe an ideal array.
//
// A 0-indexed integer array arr of length n is considered ideal if the following conditions hold:
//
//
// 	Every arr[i] is a value from 1 to maxValue, for 0 <= i < n.
// 	Every arr[i] is divisible by arr[i - 1], for 0 < i < n.
//
//
// Return the number of distinct ideal arrays of length n. Since the answer may be very large, return it modulo 109 + 7.
//
// Example:
// Input: n = 2, maxValue = 5
// Output: 10
// Explanation: The following are the possible ideal arrays:
// - Arrays starting with the value 1 (5 arrays): [1,1], [1,2], [1,3], [1,4], [1,5]
// - Arrays starting with the value 2 (2 arrays): [2,2], [2,4]
// - Arrays starting with the value 3 (1 array): [3,3]
// - Arrays starting with the value 4 (1 array): [4,4]
// - Arrays starting with the value 5 (1 array): [5,5]
// There are a total of 5 + 2 + 1 + 1 + 1 = 10 distinct ideal arrays.
//
// Constraints:
// 2 <= n <= 104
// 	1 <= maxValue <= 104
//

int idealArrays(int n, int maxValue) {
    const int MOD = 1000000007;

    /* Precompute binomial coefficients C(n, k) for n, k <= 10000 */
    int C[10001][101] = {0};
    for (int i = 0; i <= 10000; ++i) {
        C[i][0] = 1;
        for (int j = 1; j <= (i < 100 ? i : 100); ++j) {
            C[i][j] = (C[i - 1][j - 1] + C[i - 1][j]) % MOD;
        }
    }

    /* Sieve of Eratosthenes to find primes up to maxValue */
    int isPrime[10001];
    memset(isPrime, 1, sizeof(isPrime));
    isPrime[0] = isPrime[1] = 0;
    for (int i = 2; i * i <= maxValue; ++i) {
        if (isPrime[i]) {
            for (int j = i * i; j <= maxValue; j += i) {
                isPrime[j] = 0;
            }
        }
    }

    long long result = 0;
    for (int val = 1; val <= maxValue; ++val) {
        int temp = val;
        long long ways = 1;
        for (int p = 2; p <= val; ++p) {
            if (isPrime[p]) {
                int count = 0;
                while (temp % p == 0) {
                    temp /= p;
                    count++;
                }
                if (count > 0) {
                    ways = (ways * C[n - 1 + count][count]) % MOD;
                }
            }
            if (temp == 1) break;
        }
        result = (result + ways) % MOD;
    }

    return (int)result;     
}
