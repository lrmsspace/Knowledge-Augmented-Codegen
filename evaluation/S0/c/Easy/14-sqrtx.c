// Source: https://leetcode.com/problems/sqrtx/   |   Difficulty: Easy
//
// Problem Description:
// Given a non-negative integer x, return the square root of x rounded down to the nearest integer. The returned integer should be non-negative as well.
//
// You must not use any built-in exponent function or operator.
//
//
// 	For example, do not use pow(x, 0.5) in c++ or x ** 0.5 in python.
//
// Example:
// Input: x = 4
// Output: 2
// Explanation: The square root of 4 is 2, so we return 2.
//
// Constraints:
// 0 <= x <= 231 - 1
//

int mySqrt(int x) {
    if (x == 0) return 0;
    int left = 1, right = x, ans = 0;
    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (mid <= x / mid) {
            ans = mid; // mid is a potential answer
            left = mid + 1; // try for a larger mid
        } else {
            right = mid - 1; // mid is too large
        }
    }
    return ans;     
}
