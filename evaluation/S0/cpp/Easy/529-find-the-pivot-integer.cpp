// Source: https://leetcode.com/problems/find-the-pivot-integer/   |   Difficulty: Easy
//
// Problem Description:
// Given a positive integer n, find the pivot integer x such that:
//
//
// 	The sum of all elements between 1 and x inclusively equals the sum of all elements between x and n inclusively.
//
//
// Return the pivot integer x. If no such integer exists, return -1. It is guaranteed that there will be at most one pivot index for the given input.
//
// Example:
// Input: n = 8
// Output: 6
// Explanation: 6 is the pivot integer since: 1 + 2 + 3 + 4 + 5 + 6 = 6 + 7 + 8 = 21.
//
// Constraints:
// 1 <= n <= 1000
//

class Solution {
public:
    int pivotInteger(int n) {
        int totalSum = n * (n + 1) / 2;
        int leftSum = 0;

        for (int x = 1; x <= n; ++x) {
            leftSum += x;
            int rightSum = totalSum - leftSum + x;

            if (leftSum == rightSum) {
                return x;
            }
        }

        return -1;          
    }
};
