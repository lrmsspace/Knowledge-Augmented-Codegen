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

class Solution {
    public int nthSuperUglyNumber(int n, int[] primes) {
        int[] uglyNumbers = new int[n];
        uglyNumbers[0] = 1;

        int k = primes.length;
        int[] indices = new int[k];
        int[] nextMultiples = new int[k];

        for (int i = 0; i < k; i++) {
            nextMultiples[i] = primes[i];
        }

        for (int i = 1; i < n; i++) {
            int nextUgly = Integer.MAX_VALUE;
            for (int j = 0; j < k; j++) {
                nextUgly = Math.min(nextUgly, nextMultiples[j]);
            }
            uglyNumbers[i] = nextUgly;

            for (int j = 0; j < k; j++) {
                if (nextUgly == nextMultiples[j]) {
                    indices[j]++;
                    nextMultiples[j] = uglyNumbers[indices[j]] * primes[j];
                }
            }
        }

        return uglyNumbers[n - 1];          
    }
}
