// Source: https://leetcode.com/problems/minimize-the-maximum-difference-of-pairs/   |   Difficulty: Medium
//
// Problem Description:
// You are given a 0-indexed integer array nums and an integer p. Find p pairs of indices of nums such that the maximum difference amongst all the pairs is minimized. Also, ensure no index appears more than once amongst the p pairs.
//
// Note that for a pair of elements at the index i and j, the difference of this pair is |nums[i] - nums[j]|, where |x| represents the absolute value of x.
//
// Return the minimum maximum difference among all p pairs. We define the maximum of an empty set to be zero.
//
// Example:
// Input: nums = [10,1,2,7,1,3], p = 2
// Output: 1
// Explanation: The first pair is formed from the indices 1 and 4, and the second pair is formed from the indices 2 and 5. 
// The maximum difference is max(|nums[1] - nums[4]|, |nums[2] - nums[5]|) = max(0, 1) = 1. Therefore, we return 1.
//
// Constraints:
// 1 <= nums.length <= 105
// 	0 <= nums[i] <= 109
// 	0 <= p <= (nums.length)/2
//

int minimizeMax(int* nums, int numsSize, int p) {
    // Helper function to compare two integers for qsort
    int compare(const void* a, const void* b) {
        return (*(int*)a - *(int*)b);
    }

    // Function to check if we can form p pairs with max difference <= mid
    int canFormPairs(int* nums, int numsSize, int p, int mid) {
        int count = 0;
        for (int i = 1; i < numsSize && count < p; i++) {
            if (nums[i] - nums[i - 1] <= mid) {
                count++;
                i++; // Skip the next element as it's already paired
            }
        }
        return count >= p;
    }

    // Sort the array
    qsort(nums, numsSize, sizeof(int), compare);

    // Binary search for the minimum maximum difference
    int left = 0;
    int right = nums[numsSize - 1] - nums[0];
    int result = right;

    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (canFormPairs(nums, numsSize, p, mid)) {
            result = mid;
            right = mid - 1;
        } else {
            left = mid + 1;
        }
    }

    return result;      
}
