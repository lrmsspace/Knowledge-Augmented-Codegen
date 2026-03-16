// Source: https://leetcode.com/problems/maximum-erasure-value/   |   Difficulty: Medium
//
// Problem Description:
// You are given an array of positive integers nums and want to erase a subarray containing unique elements. The score you get by erasing the subarray is equal to the sum of its elements.
//
// Return the maximum score you can get by erasing exactly one subarray.
//
// An array b is called to be a subarray of a if it forms a contiguous subsequence of a, that is, if it is equal to a[l],a[l+1],...,a[r] for some (l,r).
//
// Example:
// Input: nums = [4,2,4,5,6]
// Output: 17
// Explanation: The optimal subarray here is [2,4,5,6].
//
// Constraints:
// 1 <= nums.length <= 105
// 	1 <= nums[i] <= 104
//

int maximumUniqueSubarray(int* nums, int numsSize) {
    int left = 0, right = 0;
    int current_sum = 0, max_sum = 0;
    int seen[10001] = {0}; // Since nums[i] is in the range [1, 10^4]

    while (right < numsSize) {
        if (seen[nums[right]] == 0) {
            // Element not seen, include it in the current subarray
            seen[nums[right]] = 1;
            current_sum += nums[right];
            max_sum = (current_sum > max_sum) ? current_sum : max_sum;
            right++;
        } else {
            // Element already seen, remove elements from the left until it's unique
            seen[nums[left]] = 0;
            current_sum -= nums[left];
            left++;
        }
    }

    return max_sum;     
}
