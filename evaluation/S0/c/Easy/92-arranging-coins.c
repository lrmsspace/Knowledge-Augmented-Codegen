// Source: https://leetcode.com/problems/arranging-coins/   |   Difficulty: Easy
//
// Problem Description:
// You have n coins and you want to build a staircase with these coins. The staircase consists of k rows where the ith row has exactly i coins. The last row of the staircase may be incomplete.
//
// Given the integer n, return the number of complete rows of the staircase you will build.
//
// Example:
// Input: n = 5
// Output: 2
// Explanation: Because the 3rd row is incomplete, we return 2.
//
// Constraints:
// 1 <= n <= 231 - 1
//

int arrangeCoins(int n) {
    long left = 0, right = n;
    while (left <= right) {
        long mid = left + (right - left) / 2;
        long curr = mid * (mid + 1) / 2;
        if (curr == n) {
            return (int)mid;
        }
        if (curr < n) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }
    return (int)right;      
}
