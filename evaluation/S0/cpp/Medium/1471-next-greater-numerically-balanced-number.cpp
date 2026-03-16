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
public:
    int nextBeautifulNumber(int n) {
        for (int num = n + 1; ; ++num) {
            if (isNumericallyBalanced(num)) {
                return num;
            }
        }
        return -1; // This line will never be reached           
    }
};
