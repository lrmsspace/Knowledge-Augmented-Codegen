// Source: https://leetcode.com/problems/minimize-the-maximum-adjacent-element-difference/   |   Difficulty: Hard
//
// Problem Description:
// You are given an array of integers nums. Some values in nums are missing and are denoted by -1.
//
// You must choose a pair of positive integers (x, y) exactly once and replace each missing element with either x or y.
//
// You need to minimize the maximum absolute difference between adjacent elements of nums after replacements.
//
// Return the minimum possible difference.
//
// Example:
// Input: nums = [1,2,-1,10,8]
//
// Output: 4
//
// Explanation:
//
// By choosing the pair as (6, 7), nums can be changed to [1, 2, 6, 10, 8].
//
// The absolute differences between adjacent elements are:
//
//
// 	|1 - 2| == 1
// 	|2 - 6| == 4
// 	|6 - 10| == 4
// 	|10 - 8| == 2
//
// Constraints:
// 2 <= nums.length <= 105
// 	nums[i] is either -1 or in the range [1, 109].
//

int minDifference(int* nums, int numsSize) {
    int left = 1, right = 1000000000;
    int maxAdjDiff = 0;
    int minNeighbor = 1000000000;
    int maxNeighbor = 1;

    for (int i = 0; i < numsSize; ++i) {
        if (nums[i] != -1) {
            if (i > 0 && nums[i-1] != -1) {
                int diff = nums[i] > nums[i-1] ? nums[i] - nums[i-1] : nums[i-1] - nums[i];
                if (diff > maxAdjDiff) maxAdjDiff = diff;
            }
            if (i + 1 < numsSize && nums[i+1] != -1) {
                int diff = nums[i] > nums[i+1] ? nums[i] - nums[i+1] : nums[i+1] - nums[i];
                if (diff > maxAdjDiff) maxAdjDiff = diff;
            }
        } else {
            if (i > 0 && nums[i-1] != -1) {
                if (nums[i-1] < minNeighbor) minNeighbor = nums[i-1];
                if (nums[i-1] > maxNeighbor) maxNeighbor = nums[i-1];
            }
            if (i + 1 < numsSize && nums[i+1] != -1) {
                if (nums[i+1] < minNeighbor) minNeighbor = nums[i+1];
                if (nums[i+1] > maxNeighbor) maxNeighbor = nums[i+1];
            }
        }
    }

    if (minNeighbor == 1000000000 && maxNeighbor == 1) {
        return 0; /* no known neighbors */
    }

    int mid = (minNeighbor + maxNeighbor) / 2;
    int candidateDiff = maxNeighbor - mid;
    if (mid - minNeighbor > candidateDiff) candidateDiff = mid - minNeighbor;

    return candidateDiff < maxAdjDiff ? maxAdjDiff : candidateDiff;     
}
