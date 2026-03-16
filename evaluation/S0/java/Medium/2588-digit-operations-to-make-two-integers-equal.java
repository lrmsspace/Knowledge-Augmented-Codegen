// Source: https://leetcode.com/problems/digit-operations-to-make-two-integers-equal/   |   Difficulty: Medium
//
// Problem Description:
// You are given two integers n and m that consist of the same number of digits.
//
// You can perform the following operations any number of times:
//
//
// 	Choose any digit from n that is not 9 and increase it by 1.
// 	Choose any digit from n that is not 0 and decrease it by 1.
//
//
// The integer n must not be a prime number at any point, including its original value and after each operation.
//
// The cost of a transformation is the sum of all values that n takes throughout the operations performed.
//
// Return the minimum cost to transform n into m. If it is impossible, return -1.
//
// Example:
// Input: n = 10, m = 12
//
// Output: 85
//
// Explanation:
//
// We perform the following operations:
//
//
// 	Increase the first digit, now n = 20.
// 	Increase the second digit, now n = 21.
// 	Increase the second digit, now n = 22.
// 	Decrease the first digit, now n = 12.
//
// Constraints:
// 1 <= n, m < 104
// 	n and m consist of the same number of digits.
//

class Solution {
    public int minOperations(int n, int m) {
        int max = Math.max(n, m);
        boolean[] isPrime = new boolean[max + 1];
        sieveOfEratosthenes(isPrime, max);

        int totalCost = 0;
        while (n != m) {
            int diff = m - n;
            int step = Integer.signum(diff);
            int nextN = n + step;

            while (isPrime[nextN]) {
                nextN += step;
                if (nextN < 0 || nextN > max) {
                    return -1;
                }
            }

            totalCost += nextN;
            n = nextN;
        }

        return totalCost + n; // Add the final value of n           
    }
}
