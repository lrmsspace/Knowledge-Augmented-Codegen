// Source: https://leetcode.com/problems/maximum-number-of-non-overlapping-subarrays-with-sum-equals-target/   |   Difficulty: Medium
//
// Problem Description:
// Given an array nums and an integer target, return the maximum number of non-empty non-overlapping subarrays such that the sum of values in each subarray is equal to target.
//
// Example:
// Input: nums = [1,1,1,1,1], target = 2
// Output: 2
// Explanation: There are 2 non-overlapping subarrays [1,1,1,1,1] with sum equals to target(2).
//
// Constraints:
// 1 <= nums.length <= 105
// 	-104 <= nums[i] <= 104
// 	0 <= target <= 106
//

int maxNonOverlapping(int* nums, int numsSize, int target) {
    int count = 0;
    int sum = 0;
    // Using a hash set to store the prefix sums
    // We use a simple array to simulate a hash set for this problem
    // The size of the array is determined by the constraints of the problem
    // Here we assume the maximum possible prefix sum is 10^6 + 10^4 * 10^5
    // and the minimum possible prefix sum is -10^4 * 10^5
    int offset = 1000000; // to handle negative indices
    int maxSize = 2000001; // range from -10^6 to 10^6
    char *prefixSums = (char *)calloc(maxSize, sizeof(char));
    
    prefixSums[offset] = 1; // base case: prefix sum of 0 exists

    for (int i = 0; i < numsSize; i++) {
        sum += nums[i];
        if (sum - target + offset >= 0 && sum - target + offset < maxSize && prefixSums[sum - target + offset]) {
            count++;
            // Reset for non-overlapping subarrays
            sum = 0;
            memset(prefixSums, 0, maxSize * sizeof(char));
            prefixSums[offset] = 1; // reset base case
        } else {
            prefixSums[sum + offset] = 1;
        }
    }

    free(prefixSums);
    return count;       
}
