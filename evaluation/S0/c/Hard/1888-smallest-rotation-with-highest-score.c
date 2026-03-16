// Source: https://leetcode.com/problems/smallest-rotation-with-highest-score/   |   Difficulty: Hard
//
// Problem Description:
// You are given an array nums. You can rotate it by a non-negative integer k so that the array becomes [nums[k], nums[k + 1], ... nums[nums.length - 1], nums[0], nums[1], ..., nums[k-1]]. Afterward, any entries that are less than or equal to their index are worth one point.
//
//
// 	For example, if we have nums = [2,4,1,3,0], and we rotate by k = 2, it becomes [1,3,0,2,4]. This is worth 3 points because 1 > 0 [no points], 3 > 1 [no points], 0 <= 2 [one point], 2 <= 3 [one point], 4 <= 4 [one point].
//
//
// Return the rotation index k that corresponds to the highest score we can achieve if we rotated nums by it. If there are multiple answers, return the smallest such index k.
//
// Example:
// Input: nums = [2,3,1,4,0]
// Output: 3
// Explanation: Scores for each k are listed below: 
// k = 0,  nums = [2,3,1,4,0],    score 2
// k = 1,  nums = [3,1,4,0,2],    score 3
// k = 2,  nums = [1,4,0,2,3],    score 3
// k = 3,  nums = [4,0,2,3,1],    score 4
// k = 4,  nums = [0,2,3,1,4],    score 3
// So we should choose k = 3, which has the highest score.
//
// Constraints:
// 1 <= nums.length <= 105
// 	0 <= nums[i] < nums.length
//

int bestRotation(int* nums, int numsSize) {
    if (numsSize <= 1) return 0;

    int *diff = (int*)calloc(numsSize, sizeof(int));
    if (!diff) return 0; /* allocation failure, but continue gracefully */

    for (int i = 0; i < numsSize; ++i) {
        int low = (i + 1) % numsSize;
        int high = (i - nums[i] + numsSize + 1) % numsSize;
        diff[low] += 1;
        diff[high] -= 1;
        if (low >= high) {
            diff[0] += 1;
        }
    }

    int maxScore = -1;
    int bestK = 0;
    int currScore = 0;
    for (int k = 0; k < numsSize; ++k) {
        currScore += diff[k];
        if (currScore > maxScore) {
            maxScore = currScore;
            bestK = k;
        }
    }

    free(diff);
    return bestK;       
}
