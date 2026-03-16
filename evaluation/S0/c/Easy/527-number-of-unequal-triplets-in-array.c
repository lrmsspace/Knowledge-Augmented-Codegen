// Source: https://leetcode.com/problems/number-of-unequal-triplets-in-array/   |   Difficulty: Easy
//
// Problem Description:
// You are given a 0-indexed array of positive integers nums. Find the number of triplets (i, j, k) that meet the following conditions:
//
//
// 	0 <= i < j < k < nums.length
// 	nums[i], nums[j], and nums[k] are pairwise distinct.
// 	
// 		In other words, nums[i] != nums[j], nums[i] != nums[k], and nums[j] != nums[k].
// 	
// 	
//
//
// Return the number of triplets that meet the conditions.
//
// Example:
// Input: nums = [4,4,2,4,3]
// Output: 3
// Explanation: The following triplets meet the conditions:
// - (0, 2, 4) because 4 != 2 != 3
// - (1, 2, 4) because 4 != 2 != 3
// - (2, 3, 4) because 2 != 4 != 3
// Since there are 3 triplets, we return 3.
// Note that (2, 0, 4) is not a valid triplet because 2 > 0.
//
// Constraints:
// 3 <= nums.length <= 100
// 	1 <= nums[i] <= 1000
//

int unequalTriplets(int* nums, int numsSize) {
    int count[1001] = {0};
    for (int i = 0; i < numsSize; i++) {
        count[nums[i]]++;
    }

    int uniqueCount = 0;
    for (int i = 0; i <= 1000; i++) {
        if (count[i] > 0) {
            uniqueCount++;
        }
    }

    if (uniqueCount < 3) {
        return 0;
    }

    int result = 0;
    for (int i = 0; i <= 1000; i++) {
        if (count[i] > 0) {
            uniqueCount--;
            result += count[i] * (uniqueCount * (uniqueCount - 1)) / 2;
        }
    }

    return result;      
}
