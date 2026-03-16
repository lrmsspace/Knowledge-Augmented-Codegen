// Source: https://leetcode.com/problems/sum-of-imbalance-numbers-of-all-subarrays/   |   Difficulty: Hard
//
// Problem Description:
// The imbalance number of a 0-indexed integer array arr of length n is defined as the number of indices in sarr = sorted(arr) such that:
//
//
// 	0 <= i < n - 1, and
// 	sarr[i+1] - sarr[i] > 1
//
//
// Here, sorted(arr) is the function that returns the sorted version of arr.
//
// Given a 0-indexed integer array nums, return the sum of imbalance numbers of all its subarrays.
//
// A subarray is a contiguous non-empty sequence of elements within an array.
//
// Example:
// Input: nums = [2,3,1,4]
// Output: 3
// Explanation: There are 3 subarrays with non-zero imbalance numbers:
// - Subarray [3, 1] with an imbalance number of 1.
// - Subarray [3, 1, 4] with an imbalance number of 1.
// - Subarray [1, 4] with an imbalance number of 1.
// The imbalance number of all other subarrays is 0. Hence, the sum of imbalance numbers of all the subarrays of nums is 3.
//
// Constraints:
// 1 <= nums.length <= 1000
// 	1 <= nums[i] <= nums.length
//

int sumImbalanceNumbers(int* nums, int numsSize) {
    int result = 0;
    for (int start = 0; start < numsSize; ++start) {
        int present[1001] = {0};
        present[nums[start]] = 1;
        int imbalance = 0;
        for (int end = start + 1; end < numsSize; ++end) {
            int val = nums[end];
            present[val] = 1;
            if (present[val - 1] == 0 && present[val + 1] == 0) {
                imbalance += 1;
            } else if (present[val - 1] == 1 && present[val + 1] == 1) {
                imbalance -= 1;
            }
            result += imbalance;
        }
    }
    return result;      
}
