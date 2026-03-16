// Source: https://leetcode.com/problems/removing-minimum-and-maximum-from-array/   |   Difficulty: Medium
//
// Problem Description:
// You are given a 0-indexed array of distinct integers nums.
//
// There is an element in nums that has the lowest value and an element that has the highest value. We call them the minimum and maximum respectively. Your goal is to remove both these elements from the array.
//
// A deletion is defined as either removing an element from the front of the array or removing an element from the back of the array.
//
// Return the minimum number of deletions it would take to remove both the minimum and maximum element from the array.
//
// Example:
// Input: nums = [2,10,7,5,4,1,8,6]
// Output: 5
// Explanation: 
// The minimum element in the array is nums[5], which is 1.
// The maximum element in the array is nums[1], which is 10.
// We can remove both the minimum and maximum by removing 2 elements from the front and 3 elements from the back.
// This results in 2 + 3 = 5 deletions, which is the minimum number possible.
//
// Constraints:
// 1 <= nums.length <= 105
// 	-105 <= nums[i] <= 105
// 	The integers in nums are distinct.
//

int minimumDeletions(int* nums, int numsSize) {
    int minIndex = 0, maxIndex = 0;
    for (int i = 1; i < numsSize; i++) {
        if (nums[i] < nums[minIndex]) {
            minIndex = i;
        }
        if (nums[i] > nums[maxIndex]) {
            maxIndex = i;
        }
    }

    int left = (minIndex < maxIndex) ? minIndex : maxIndex;
    int right = (minIndex > maxIndex) ? minIndex : maxIndex;

    int removeFromLeft = right + 1;
    int removeFromRight = numsSize - left;
    int removeFromBothSides = (left + 1) + (numsSize - right);

    int minDeletions = removeFromLeft;
    if (removeFromRight < minDeletions) {
        minDeletions = removeFromRight;
    }
    if (removeFromBothSides < minDeletions) {
        minDeletions = removeFromBothSides;
    }

    return minDeletions;        
}
