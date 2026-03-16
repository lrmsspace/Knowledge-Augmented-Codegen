// Source: https://leetcode.com/problems/maximum-value-at-a-given-index-in-a-bounded-array/   |   Difficulty: Medium
//
// Problem Description:
// You are given three positive integers: n, index, and maxSum. You want to construct an array nums (0-indexed) that satisfies the following conditions:
//
//
// 	nums.length == n
// 	nums[i] is a positive integer where 0 <= i < n.
// 	abs(nums[i] - nums[i+1]) <= 1 where 0 <= i < n-1.
// 	The sum of all the elements of nums does not exceed maxSum.
// 	nums[index] is maximized.
//
//
// Return nums[index] of the constructed array.
//
// Note that abs(x) equals x if x >= 0, and -x otherwise.
//
// Example:
// Input: n = 4, index = 2,  maxSum = 6
// Output: 2
// Explanation: nums = [1,2,2,1] is one array that satisfies all the conditions.
// There are no arrays that satisfy all the conditions and have nums[2] == 3, so 2 is the maximum nums[2].
//
// Constraints:
// 1 <= n <= maxSum <= 109
// 	0 <= index < n
//

int maxValue(int n, int index, int maxSum) {
    long left = 1, right = maxSum;
    long ans = 0;

    while (left <= right) {
        long mid = left + (right - left) / 2;
        long total = mid;

        // Calculate left side sum
        if (mid - 1 >= index) {
            total += (long)(mid - 1 + mid - index) * index / 2;
        } else {
            total += (long)(mid - 1) * mid / 2;
            total += index - (mid - 1);
        }

        // Calculate right side sum
        if (mid - 1 >= n - index - 1) {
            total += (long)(mid - 1 + mid - (n - index - 1)) * (n - index - 1) / 2;
        } else {
            total += (long)(mid - 1) * mid / 2;
            total += (n - index - 1) - (mid - 1);
        }

        if (total <= maxSum) {
            ans = mid;
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }

    return (int)ans;        
}
