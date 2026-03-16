// Source: https://leetcode.com/problems/next-greater-numerically-balanced-number/   |   Difficulty: Medium
//
// Problem Description:
// An integer x is numerically balanced if for every digit d in the number x, there are exactly d occurrences of that digit in x.
//
// Given an integer n, return the smallest numerically balanced number strictly greater than n.
//
// Example:
// Input: n = 1
// Output: 22
// Explanation: 
// 22 is numerically balanced since:
// - The digit 2 occurs 2 times. 
// It is also the smallest numerically balanced number strictly greater than 1.
//
// Constraints:
// 0 <= n <= 106
//

class Solution {
    public int nextBeautifulNumber(int n) {
        int[] balancedNumbers = {1, 22, 122, 333, 4444, 55555, 666666, 7777777, 88888888, 999999999,
                                 1122, 1212, 2112, 2211, 1233, 1323, 1332, 2133, 2313, 2331,
                                 3123, 3132, 3213, 3231, 3312, 3321, 2244, 2424, 2442, 4224,
                                 4242, 4422, 12333, 13233, 13323, 13332, 21333, 23133, 23313,
                                 23331, 31233, 31323, 31332, 32133, 32313, 32331, 33123,
                                 33132, 33213, 33231};

        for (int balancedNumber : balancedNumbers) {
            if (balancedNumber > n) {
                return balancedNumber;
            }
        }

        return -1; // This line should never be reached given the problem constraints.          
    }
}
