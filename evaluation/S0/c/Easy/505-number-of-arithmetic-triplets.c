// Source: https://leetcode.com/problems/number-of-arithmetic-triplets/   |   Difficulty: Easy
//
// Problem Description:
// You are given a 0-indexed, strictly increasing integer array nums and a positive integer diff. A triplet (i, j, k) is an arithmetic triplet if the following conditions are met:
//
//
// 	i < j < k,
// 	nums[j] - nums[i] == diff, and
// 	nums[k] - nums[j] == diff.
//
//
// Return the number of unique arithmetic triplets.
//
// Example:
// Input: nums = [0,1,4,6,7,10], diff = 3
// Output: 2
// Explanation:
// (1, 2, 4) is an arithmetic triplet because both 7 - 4 == 3 and 4 - 1 == 3.
// (2, 4, 5) is an arithmetic triplet because both 10 - 7 == 3 and 7 - 4 == 3.
//
// Constraints:
// 3 <= nums.length <= 200
// 	0 <= nums[i] <= 200
// 	1 <= diff <= 50
// 	nums is strictly increasing.
//

int arithmeticTriplets(int* nums, int numsSize, int diff) {
    int count = 0;
    for (int i = 0; i < numsSize - 2; i++) {
        for (int j = i + 1; j < numsSize - 1; j++) {
            if (nums[j] - nums[i] == diff) {
                for (int k = j + 1; k < numsSize; k++) {
                    if (nums[k] - nums[j] == diff) {
                        count++;
                    }
                }
            }
        }
    }
    return count;       
}
