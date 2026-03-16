// Source: https://leetcode.com/problems/identify-the-largest-outlier-in-an-array/   |   Difficulty: Medium
//
// Problem Description:
// You are given an integer array nums. This array contains n elements, where exactly n - 2 elements are special numbers. One of the remaining two elements is the sum of these special numbers, and the other is an outlier.
//
// An outlier is defined as a number that is neither one of the original special numbers nor the element representing the sum of those numbers.
//
// Note that special numbers, the sum element, and the outlier must have distinct indices, but may share the same value.
//
// Return the largest potential outlier in nums.
//
// Example:
// Input: nums = [2,3,5,10]
//
// Output: 10
//
// Explanation:
//
// The special numbers could be 2 and 3, thus making their sum 5 and the outlier 10.
//
// Constraints:
// 3 <= nums.length <= 105
// 	-1000 <= nums[i] <= 1000
// 	The input is generated such that at least one potential outlier exists in nums.
//

int getLargestOutlier(int* nums, int numsSize) {
    int maxOutlier = -1001; // Given constraints: -1000 <= nums[i] <= 1000
    for (int i = 0; i < numsSize; i++) {
        int sum = 0;
        for (int j = 0; j < numsSize; j++) {
            if (i != j) {
                sum += nums[j];
            }
        }
        for (int k = 0; k < numsSize; k++) {
            if (k != i && k != j && nums[k] != sum) {
                if (nums[k] > maxOutlier) {
                    maxOutlier = nums[k];
                }
            }
        }
    }
    return maxOutlier;      
}
