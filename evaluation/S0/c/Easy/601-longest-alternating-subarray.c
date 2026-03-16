// Source: https://leetcode.com/problems/longest-alternating-subarray/   |   Difficulty: Easy
//
// Problem Description:
// You are given a 0-indexed integer array nums. A subarray s of length m is called alternating if:
//
//
// 	m is greater than 1.
// 	s1 = s0 + 1.
// 	The 0-indexed subarray s looks like [s0, s1, s0, s1,...,s(m-1) % 2]. In other words, s1 - s0 = 1, s2 - s1 = -1, s3 - s2 = 1, s4 - s3 = -1, and so on up to s[m - 1] - s[m - 2] = (-1)m.
//
//
// Return the maximum length of all alternating subarrays present in nums or -1 if no such subarray exists.
//
// A subarray is a contiguous non-empty sequence of elements within an array.
//
// Example:
// Input: nums = [2,3,4,3,4]
//
// Output: 4
//
// Explanation:
//
// The alternating subarrays are [2, 3], [3,4], [3,4,3], and [3,4,3,4]. The longest of these is [3,4,3,4], which is of length 4.
//
// Constraints:
// 2 <= nums.length <= 100
// 	1 <= nums[i] <= 104
//

int alternatingSubarray(int* nums, int numsSize) {
    int max_len = -1;

    for (int i = 0; i < numsSize - 1; i++) {
        if (nums[i + 1] == nums[i] + 1) {
            int current_len = 2;
            int expected = nums[i];

            for (int j = i + 2; j < numsSize; j++) {
                if (nums[j] == expected) {
                    current_len++;
                    expected = (expected == nums[i]) ? nums[i] + 1 : nums[i];
                } else {
                    break;
                }
            }

            if (current_len > max_len) {
                max_len = current_len;
            }
        }
    }

    return max_len;     
}
