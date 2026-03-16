// Source: https://leetcode.com/problems/minimum-array-end/   |   Difficulty: Medium
//
// Problem Description:
// You are given two integers n and x. You have to construct an array of positive integers nums of size n where for every 0 <= i < n - 1, nums[i + 1] is greater than nums[i], and the result of the bitwise AND operation between all elements of nums is x.
//
// Return the minimum possible value of nums[n - 1].
//
// Example:
// Input: n = 3, x = 4
//
// Output: 6
//
// Explanation:
//
// nums can be [4,5,6] and its last element is 6.
//
// Constraints:
// 1 <= n, x <= 108
//

long long minEnd(int n, int x) {
    long long left = x;
    long long right = 1e18;
    long long answer = -1;

    while (left <= right) {
        long long mid = left + (right - left) / 2;
        long long count = 0;

        for (long long num = mid; num >= x; num--) {
            if ((num & x) == x) {
                count++;
            }
            if (count >= n) {
                break;
            }
        }

        if (count >= n) {
            answer = mid;
            right = mid - 1;
        } else {
            left = mid + 1;
        }
    }

    return answer;      
}
