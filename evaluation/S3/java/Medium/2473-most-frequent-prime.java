// Source: https://leetcode.com/problems/most-frequent-prime/   |   Difficulty: Medium
//
// Problem Description:
// You are given a m x n 0-indexed 2D matrix mat. From every cell, you can create numbers in the following way:
//
//
// 	There could be at most 8 paths from the cells namely: east, south-east, south, south-west, west, north-west, north, and north-east.
// 	Select a path from them and append digits in this path to the number being formed by traveling in this direction.
// 	Note that numbers are generated at every step, for example, if the digits along the path are 1, 9, 1, then there will be three numbers generated along the way: 1, 19, 191.
//
//
// Return the most frequent prime number greater than 10 out of all the numbers created by traversing the matrix or -1 if no such prime number exists. If there are multiple prime numbers with the highest frequency, then return the largest among them.
//
// Note: It is invalid to change the direction during the move.
//
// Example:
// Input: mat = [[1,1],[9,9],[1,1]]
// Output: 19
// Explanation: 
// From cell (0,0) there are 3 possible directions and the numbers greater than 10 which can be created in those directions are:
// East: [11], South-East: [19], South: [19,191].
// Numbers greater than 10 created from the cell (0,1) in all possible directions are: [19,191,19,11].
// Numbers greater than 10 created from the cell (1,0) in all possible directions are: [99,91,91,91,91].
// Numbers greater than 10 created from the cell (1,1) in all possible directions are: [91,91,99,91,91].
// Numbers greater than 10 created from the cell (2,0) in all possible directions are: [11,19,191,19].
// Numbers greater than 10 created from the cell (2,1) in all possible directions are: [11,19,19,191].
// The most frequent prime number among all the created numbers is 19.
//
// Constraints:
// m == mat.length
// 	n == mat[i].length
// 	1 <= m, n <= 6
// 	1 <= mat[i][j] <= 9
//
// Helpful references (internal KB):
// - Sieve of Eratosthenes (array, sieve, enumeration)
//   • When to use: Use when you need to find all prime numbers up to a certain limit or precompute primality for a range. It is efficient for generating primes within a reasonable upper bound.
//   • Idea: The Sieve of Eratosthenes efficiently finds all prime numbers up to a specified integer by iteratively marking multiples of primes as composite. It achieves a time complexity of O(N log log N).
//   • Invariants: All numbers less than the current prime 'p' have already been processed.; If 'i' is marked as prime, then all its multiples less than 'i*i' have been marked composite by smaller primes.
//   • Tips: Optimize by starting inner loop from p*p, as smaller multiples would have been marked.; Use a boolean array for primality, or an integer array to store smallest prime factor (SPF).
//   • Pitfalls: Incorrectly handling 0 and 1, which are neither prime nor composite.; Off-by-one errors when setting array bounds or loop conditions.
// - Sieve of Eratosthenes (array, bitset, sieve)
//   • When to use: Use when you need to find all prime numbers up to a certain limit N efficiently. It is ideal for problems requiring primality tests or prime factorizations for multiple numbers within a fixed range.
//   • Idea: The Sieve of Eratosthenes is an efficient algorithm for finding all prime numbers up to a specified integer N. It works by iteratively marking the multiples of each prime number as composite, achieving a time complexity of O(N log log N).
//   • Invariants: For any number `p` processed, all its multiples less than `p*p` are already marked composite.; At the start of an iteration for `i`, if `is_prime[i]` is true, then `i` is a prime number.
//   • Tips: Initialize a boolean array `is_prime` to true for all numbers.; Start marking multiples from `p*p` for each prime `p` to optimize.
//   • Pitfalls: Forgetting to handle 0 and 1 correctly (they are not prime).; Integer overflow when calculating `i*i` for large `i`.
// - Sieve of Eratosthenes (array, bitset, sieve)
//   • When to use: When you need to find all prime numbers up to a certain limit N, or efficiently check primality for many numbers within that range. It is ideal for precomputing primes.
//   • Idea: The Sieve of Eratosthenes efficiently finds all prime numbers up to a specified integer N by iteratively marking multiples of each prime. It achieves O(N log log N) time complexity and O(N) space.
//   • Invariants: For any number i less than the current prime p, is_prime[i] correctly reflects its primality.; All multiples of primes smaller than the current prime p have already been marked as composite.
//   • Tips: Optimize by starting marking multiples from p*p for each prime p.; Use a bitset for memory efficiency when N is large.
//   • Pitfalls: Forgetting to explicitly handle 0 and 1 as non-prime.; Incorrectly marking multiples, e.g., starting from 2*p instead of p*p.
//
// Notes:
// - Keep the given method signatures unchanged.
// - Use only Java standard library (`java.*`); no external dependencies.
// - Do not change input/output formats or return value semantics.
// - Conformance: single public class 'Solution'; no 'package' statement; place any extra types as static inner classes.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
    public int mostFrequentPrime(int[][] mat) {
        int m = mat.length, n = mat[0].length;
        int maxNum = 0;
        for (int[] row : mat) {
            for (int num : row) {
                maxNum = Math.max(maxNum, num);
            }
        }
        maxNum = (int) Math.pow(10, Math.min(m, n)) * maxNum; // Max possible number formed

        boolean[] isPrime = sieveOfEratosthenes(maxNum);
        Map<Integer, Integer> primeFrequency = new HashMap<>();

        int[][] directions = {{0, 1}, {1, 1}, {1, 0}, {1, -1}, {0, -1}, {-1, -1}, {-1, 0}, {-1, 1}};
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                for (int[] dir : directions) {
                    int num = 0;
                    int x = i, y = j;
                    while (x >= 0 && x < m && y >= 0 && y < n) {
                        num = num * 10 + mat[x][y];
                        if (num > 10 && isPrime[num]) {
                            primeFrequency.put(num, primeFrequency.getOrDefault(num, 0) + 1);
                        }
                        x += dir[0];
                        y += dir[1];
                    }
                }
            }
        }

        int mostFrequentPrime = -1;
        int highestFrequency = 0;
        for (Map.Entry<Integer, Integer> entry : primeFrequency.entrySet()) {
            int prime = entry.getKey();
            int frequency = entry.getValue();
            if (frequency > highestFrequency || (frequency == highestFrequency && prime > mostFrequentPrime)) {
                mostFrequentPrime = prime;
                highestFrequency = frequency;
            }
        }

        return mostFrequentPrime;           
    }
}
