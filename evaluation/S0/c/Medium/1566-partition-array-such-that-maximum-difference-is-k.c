// Source: https://leetcode.com/problems/partition-array-such-that-maximum-difference-is-k/   |   Difficulty: Medium
//
// Problem Description:
// You are given an integer array nums and an integer k. You may partition nums into one or more subsequences such that each element in nums appears in exactly one of the subsequences.
//
// Return the minimum number of subsequences needed such that the difference between the maximum and minimum values in each subsequence is at most k.
//
// A subsequence is a sequence that can be derived from another sequence by deleting some or no elements without changing the order of the remaining elements.
//
// Example:
// Input: nums = [3,6,1,2,5], k = 2
// Output: 2
// Explanation:
// We can partition nums into the two subsequences [3,1,2] and [6,5].
// The difference between the maximum and minimum value in the first subsequence is 3 - 1 = 2.
// The difference between the maximum and minimum value in the second subsequence is 6 - 5 = 1.
// Since two subsequences were created, we return 2. It can be shown that 2 is the minimum number of subsequences needed.
//
// Constraints:
// 1 <= nums.length <= 105
// 	0 <= nums[i] <= 105
// 	0 <= k <= 105
//

int partitionArray(int* nums, int numsSize, int k) {
    // Sort the array to group elements with minimal differences together
    qsort(nums, numsSize, sizeof(int), (int (*)(const void*, const void*))strcmp);

    int count = 1; // At least one subsequence is needed
    int minVal = nums[0]; // Minimum value of the current subsequence

    for (int i = 1; i < numsSize; i++) {
        // If the difference exceeds k, start a new subsequence
        if (nums[i] - minVal > k) {
            count++;
            minVal = nums[i]; // Update the minimum value for the new subsequence
        }
    }

    return count;       
}
