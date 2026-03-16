// Source: https://leetcode.com/problems/minimum-size-subarray-sum/   |   Difficulty: Medium
//
// Problem Description:
// Given an array of positive integers nums and a positive integer target, return the minimal length of a subarray whose sum is greater than or equal to target. If there is no such subarray, return 0 instead.
//
// Example:
// Input: target = 7, nums = [2,3,1,2,4,3]
// Output: 2
// Explanation: The subarray [4,3] has the minimal length under the problem constraint.
//
// Constraints:
// 1 <= target <= 109
// 	1 <= nums.length <= 105
// 	1 <= nums[i] <= 104
//
//
//  
// Follow up: If you have figured out the O(n) solution, try coding another solution of which the time complexity is O(n log(n)).
//

int minSubArrayLen(int target, int* nums, int numsSize) {
    int left = 0, right = 0;
    int sum = 0;
    int minLength = numsSize + 1;

    while (right < numsSize) {
        sum += nums[right];

        while (sum >= target) {
            minLength = (right - left + 1 < minLength) ? (right - left + 1) : minLength;
            sum -= nums[left];
            left++;
        }
        right++;
    }

    return (minLength == numsSize + 1) ? 0 : minLength;     
}
