// Source: https://leetcode.com/problems/sum-of-good-numbers/   |   Difficulty: Easy
//
// Problem Description:
// Given an array of integers nums and an integer k, an element nums[i] is considered good if it is strictly greater than the elements at indices i - k and i + k (if those indices exist). If neither of these indices exists, nums[i] is still considered good.
//
// Return the sum of all the good elements in the array.
//
// Example:
// Input: nums = [1,3,2,1,5,4], k = 2
//
// Output: 12
//
// Explanation:
//
// The good numbers are nums[1] = 3, nums[4] = 5, and nums[5] = 4 because they are strictly greater than the numbers at indices i - k and i + k.
//
// Constraints:
// 2 <= nums.length <= 100
// 	1 <= nums[i] <= 1000
// 	1 <= k <= floor(nums.length / 2)
//

int sumOfGoodNumbers(int* nums, int numsSize, int k) {
    int sum = 0;
    for (int i = 0; i < numsSize; i++) {
        int leftIndex = i - k;
        int rightIndex = i + k;
        int isGood = 1;

        if (leftIndex >= 0 && nums[i] <= nums[leftIndex]) {
            isGood = 0;
        }
        if (rightIndex < numsSize && nums[i] <= nums[rightIndex]) {
            isGood = 0;
        }

        if (isGood) {
            sum += nums[i];
        }
    }
    return sum;     
}
