// Source: https://leetcode.com/problems/closest-divisors/   |   Difficulty: Medium
//
// Problem Description:
// Given an integer num, find the closest two integers in absolute difference whose product equals num + 1 or num + 2.
//
// Return the two integers in any order.
//
// Example:
// Input: num = 8
// Output: [3,3]
// Explanation: For num + 1 = 9, the closest divisors are 3 & 3, for num + 2 = 10, the closest divisors are 2 & 5, hence 3 & 3 is chosen.
//
// Constraints:
// 1 <= num <= 10^9
//

class Solution {
    public int[] closestDivisors(int num) {
        int[] result1 = findClosestDivisors(num + 1);
        int[] result2 = findClosestDivisors(num + 2);

        return Math.abs(result1[0] - result1[1]) <= Math.abs(result2[0] - result2[1]) ? result1 : result2;          
    }
}
