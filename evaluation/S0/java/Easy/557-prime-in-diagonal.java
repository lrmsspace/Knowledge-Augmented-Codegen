// Source: https://leetcode.com/problems/prime-in-diagonal/   |   Difficulty: Easy
//
// Problem Description:
// You are given a 0-indexed two-dimensional integer array nums.
//
// Return the largest prime number that lies on at least one of the diagonals of nums. In case, no prime is present on any of the diagonals, return 0.
//
// Note that:
//
//
// 	An integer is prime if it is greater than 1 and has no positive integer divisors other than 1 and itself.
// 	An integer val is on one of the diagonals of nums if there exists an integer i for which nums[i][i] = val or an i for which nums[i][nums.length - i - 1] = val.
//
//
//
//
// In the above diagram, one diagonal is [1,5,9] and another diagonal is [3,5,7].
//
// Example:
// Input: nums = [[1,2,3],[5,6,7],[9,10,11]]
// Output: 11
// Explanation: The numbers 1, 3, 6, 9, and 11 are the only numbers present on at least one of the diagonals. Since 11 is the largest prime, we return 11.
//
// Constraints:
// 1 <= nums.length <= 300
// 	nums.length == numsi.length
// 	1 <= nums[i][j] <= 4*106
//

class Solution {
    public int diagonalPrime(int[][] nums) {
        int n = nums.length;
        int maxPrime = 0;

        for (int i = 0; i < n; i++) {
            int val1 = nums[i][i];
            int val2 = nums[i][n - i - 1];

            if (isPrime(val1)) {
                maxPrime = Math.max(maxPrime, val1);
            }
            if (isPrime(val2)) {
                maxPrime = Math.max(maxPrime, val2);
            }
        }

        return maxPrime;            
    }
}
