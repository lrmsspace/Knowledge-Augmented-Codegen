// Source: https://leetcode.com/problems/search-insert-position/   |   Difficulty: Easy
//
// Problem Description:
// Given a sorted array of distinct integers and a target value, return the index if the target is found. If not, return the index where it would be if it were inserted in order.
//
// You must write an algorithm with O(log n) runtime complexity.
//
// Example:
// Input: nums = [1,3,5,6], target = 5
// Output: 2
//
// Constraints:
// 1 <= nums.length <= 104
// 	-104 <= nums[i] <= 104
// 	nums contains distinct values sorted in ascending order.
// 	-104 <= target <= 104
//

int searchInsert(int* nums, int numsSize, int target) {
    int left = 0, right = numsSize - 1;
    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (nums[mid] == target) {
            return mid;
        } else if (nums[mid] < target) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }
    return left;        
}
