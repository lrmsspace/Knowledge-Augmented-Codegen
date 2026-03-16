// Source: https://leetcode.com/problems/subarrays-with-k-different-integers/   |   Difficulty: Hard
//
// Problem Description:
// Given an integer array nums and an integer k, return the number of good subarrays of nums.
//
// A good array is an array where the number of different integers in that array is exactly k.
//
//
// 	For example, [1,2,3,1,2] has 3 different integers: 1, 2, and 3.
//
//
// A subarray is a contiguous part of an array.
//
// Example:
// Input: nums = [1,2,1,2,3], k = 2
// Output: 7
// Explanation: Subarrays formed with exactly 2 different integers: [1,2], [2,1], [1,2], [2,3], [1,2,1], [2,1,2], [1,2,1,2]
//
// Constraints:
// 1 <= nums.length <= 2 * 104
// 	1 <= nums[i], k <= nums.length
//

int subarraysWithKDistinct(int* nums, int numsSize, int k) {
    if (k <= 0 || numsSize <= 0) return 0;

    int *count = (int*)calloc(numsSize + 1, sizeof(int));
    if (!count) return 0;

    int left1 = 0, left2 = 0, right = 0;
    int distinct1 = 0, distinct2 = 0;
    int result = 0;

    while (right < numsSize) {
        /* Expand the window to the right */
        if (count[nums[right]] == 0) distinct1++;
        count[nums[right]]++;
        right++;

        /* Shrink the first window to have at most k distinct */
        while (distinct1 > k) {
            count[nums[left1]]--;
            if (count[nums[left1]] == 0) distinct1--;
            left1++;
        }

        /* Shrink the second window to have at most k-1 distinct */
        while (distinct2 >= k) {
            count[nums[left2]]--;
            if (count[nums[left2]] == 0) distinct2--;
            left2++;
        }

        result += left2 - left1;
    }

    free(count);
    return result;      
}
