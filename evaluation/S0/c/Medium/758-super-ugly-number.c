// Source: https://leetcode.com/problems/super-ugly-number/   |   Difficulty: Medium
//
// Problem Description:
// A super ugly number is a positive integer whose prime factors are in the array primes.
//
// Given an integer n and an array of integers primes, return the nth super ugly number.
//
// The nth super ugly number is guaranteed to fit in a 32-bit signed integer.
//
// Example:
// Input: n = 12, primes = [2,7,13,19]
// Output: 32
// Explanation: [1,2,4,7,8,13,14,16,19,26,28,32] is the sequence of the first 12 super ugly numbers given primes = [2,7,13,19].
//
// Constraints:
// 1 <= n <= 105
// 	1 <= primes.length <= 100
// 	2 <= primes[i] <= 1000
// 	primes[i] is guaranteed to be a prime number.
// 	All the values of primes are unique and sorted in ascending order.
//

int nthSuperUglyNumber(int n, int* primes, int primesSize) {
    int *ugly_numbers = (int *)malloc(n * sizeof(int));
    int *indices = (int *)calloc(primesSize, sizeof(int));
    int *next_multiples = (int *)malloc(primesSize * sizeof(int));
    int i, j;

    ugly_numbers[0] = 1;

    for (i = 0; i < primesSize; i++) {
        next_multiples[i] = primes[i];
    }

    for (i = 1; i < n; i++) {
        int next_ugly = next_multiples[0];
        for (j = 1; j < primesSize; j++) {
            if (next_multiples[j] < next_ugly) {
                next_ugly = next_multiples[j];
            }
        }
        ugly_numbers[i] = next_ugly;

        for (j = 0; j < primesSize; j++) {
            if (next_ugly == next_multiples[j]) {
                indices[j]++;
                next_multiples[j] = ugly_numbers[indices[j]] * primes[j];
            }
        }
    }

    int result = ugly_numbers[n - 1];
    free(ugly_numbers);
    free(indices);
    free(next_multiples);
    return result;      
}
