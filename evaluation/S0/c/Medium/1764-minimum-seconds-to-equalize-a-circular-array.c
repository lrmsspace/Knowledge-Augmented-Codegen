// Source: https://leetcode.com/problems/minimum-seconds-to-equalize-a-circular-array/   |   Difficulty: Medium
//
// Problem Description:
// You are given a 0-indexed array nums containing n integers.
//
// At each second, you perform the following operation on the array:
//
//
// 	For every index i in the range [0, n - 1], replace nums[i] with either nums[i], nums[(i - 1 + n) % n], or nums[(i + 1) % n].
//
//
// Note that all the elements get replaced simultaneously.
//
// Return the minimum number of seconds needed to make all elements in the array nums equal.
//
// Example:
// Input: nums = [1,2,1,2]
// Output: 1
// Explanation: We can equalize the array in 1 second in the following way:
// - At 1st second, replace values at each index with [nums[3],nums[1],nums[3],nums[3]]. After replacement, nums = [2,2,2,2].
// It can be proven that 1 second is the minimum amount of seconds needed for equalizing the array.
//
// Constraints:
// 1 <= n == nums.length <= 105
// 	1 <= nums[i] <= 109
//

int minimumSeconds(int* nums, int numsSize) {
    int maxCount = 0;
    for (int i = 0; i < numsSize; ) {
        int count = 0;
        int j = i;
        while (j < numsSize && nums[j] == nums[i]) {
            count++;
            j++;
        }
        if (j == numsSize && nums[0] == nums[i]) {
            int k = 0;
            while (k < i && nums[k] == nums[i]) {
                count++;
                k++;
            }
        }
        if (count > maxCount) {
            maxCount = count;
        }
        i = j;
    }
    return (numsSize - maxCount + 1) / 2;       
}
