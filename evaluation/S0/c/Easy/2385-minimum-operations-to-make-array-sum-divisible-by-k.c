// Source: https://leetcode.com/problems/minimum-operations-to-make-array-sum-divisible-by-k/   |   Difficulty: Easy
//
// Problem Description:
// You are given an integer array nums and an integer k. You can perform the following operation any number of times:
//
//
// 	Select an index i and replace nums[i] with nums[i] - 1.
//
//
// Return the minimum number of operations required to make the sum of the array divisible by k.
//
// Example:
// Input: nums = [3,9,7], k = 5
//
// Output: 4
//
// Explanation:
//
//
// 	Perform 4 operations on nums[1] = 9. Now, nums = [3, 5, 7].
// 	The sum is 15, which is divisible by 5.
//
// Constraints:
// 1 <= nums.length <= 1000
// 	1 <= nums[i] <= 1000
// 	1 <= k <= 100
//

int minOperations(int* nums, int numsSize, int k) {
    int total_sum = 0;
    for (int i = 0; i < numsSize; i++) {
        total_sum += nums[i];
    }

    int remainder = total_sum % k;
    if (remainder == 0) {
        return 0;
    }

    int min_operations = k; // Initialize with a value larger than any possible operations
    for (int i = 0; i < numsSize; i++) {
        int current_remainder = nums[i] % k;
        int operations_needed = (current_remainder >= remainder) ? (current_remainder - remainder) : (current_remainder + k - remainder);
        if (operations_needed < min_operations) {
            min_operations = operations_needed;
        }
    }

    return min_operations;      
}
