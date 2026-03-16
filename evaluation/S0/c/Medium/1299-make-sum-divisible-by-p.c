// Source: https://leetcode.com/problems/make-sum-divisible-by-p/   |   Difficulty: Medium
//
// Problem Description:
// Given an array of positive integers nums, remove the smallest subarray (possibly empty) such that the sum of the remaining elements is divisible by p. It is not allowed to remove the whole array.
//
// Return the length of the smallest subarray that you need to remove, or -1 if it's impossible.
//
// A subarray is defined as a contiguous block of elements in the array.
//
// Example:
// Input: nums = [3,1,4,2], p = 6
// Output: 1
// Explanation: The sum of the elements in nums is 10, which is not divisible by 6. We can remove the subarray [4], and the sum of the remaining elements is 6, which is divisible by 6.
//
// Constraints:
// 1 <= nums.length <= 105
// 	1 <= nums[i] <= 109
// 	1 <= p <= 109
//

int minSubarray(int* nums, int numsSize, int p) {
    long total = 0;
    for (int i = 0; i < numsSize; i++) {
        total = (total + nums[i]) % p;
    }
    if (total == 0) {
        return 0;
    }

    int minLength = numsSize;
    long current = 0;
    int left = 0;
    int modIndexMap[p];
    for (int i = 0; i < p; i++) {
        modIndexMap[i] = -1;
    }
    modIndexMap[0] = -1; // Base case

    for (int right = 0; right < numsSize; right++) {
        current = (current + nums[right]) % p;
        int targetMod = (current - total + p) % p;

        if (modIndexMap[targetMod] != -1) {
            int length = right - modIndexMap[targetMod];
            if (length < minLength) {
                minLength = length;
            }
        }
        modIndexMap[current] = right;
    }

    return minLength == numsSize ? -1 : minLength;      
}
