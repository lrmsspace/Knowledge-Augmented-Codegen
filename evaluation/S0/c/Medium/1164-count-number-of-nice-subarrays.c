// Source: https://leetcode.com/problems/count-number-of-nice-subarrays/   |   Difficulty: Medium
//
// Problem Description:
// Given an array of integers nums and an integer k. A continuous subarray is called nice if there are k odd numbers on it.
//
// Return the number of nice sub-arrays.
//
// Example:
// Input: nums = [1,1,2,1,1], k = 3
// Output: 2
// Explanation: The only sub-arrays with 3 odd numbers are [1,1,2,1] and [1,2,1,1].
//
// Constraints:
// 1 <= nums.length <= 50000
// 	1 <= nums[i] <= 10^5
// 	1 <= k <= nums.length
//

int numberOfSubarrays(int* nums, int numsSize, int k) {
    int count = 0;
    int oddCount = 0;
    int left = 0;
    int right = 0;
    int prefixEvenCount = 0;

    while (right < numsSize) {
        if (nums[right] % 2 == 1) {
            oddCount++;
            prefixEvenCount = 0;
        }

        while (oddCount == k) {
            if (nums[left] % 2 == 0) {
                prefixEvenCount++;
            } else {
                oddCount--;
            }
            left++;
        }

        count += prefixEvenCount;
        right++;
    }

    return count;       
}
