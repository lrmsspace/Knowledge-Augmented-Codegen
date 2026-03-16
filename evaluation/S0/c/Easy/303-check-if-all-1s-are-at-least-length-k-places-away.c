// Source: https://leetcode.com/problems/check-if-all-1s-are-at-least-length-k-places-away/   |   Difficulty: Easy
//
// Problem Description:
// Given an binary array nums and an integer k, return true if all 1's are at least k places away from each other, otherwise return false.
//
// Example:
// Input: nums = [1,0,0,0,1,0,0,1], k = 2
// Output: true
// Explanation: Each of the 1s are at least 2 places away from each other.
//
// Constraints:
// 1 <= nums.length <= 105
// 	0 <= k <= nums.length
// 	nums[i] is 0 or 1
//

bool kLengthApart(int* nums, int numsSize, int k) {
    int last_one_index = -k - 1; // Initialize to ensure the first 1 is valid
    for (int i = 0; i < numsSize; i++) {
        if (nums[i] == 1) {
            if (i - last_one_index - 1 < k) {
                return false; // Not enough distance between 1s
            }
            last_one_index = i; // Update the index of the last found 1
        }
    }
    return true; // All 1s are at least k places apart      
}
