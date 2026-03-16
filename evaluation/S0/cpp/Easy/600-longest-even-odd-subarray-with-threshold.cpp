// Source: https://leetcode.com/problems/longest-even-odd-subarray-with-threshold/   |   Difficulty: Easy
//
// Problem Description:
// You are given a 0-indexed integer array nums and an integer threshold.
//
// Find the length of the longest subarray of nums starting at index l and ending at index r (0 <= l <= r < nums.length) that satisfies the following conditions:
//
//
// 	nums[l] % 2 == 0
// 	For all indices i in the range [l, r - 1], nums[i] % 2 != nums[i + 1] % 2
// 	For all indices i in the range [l, r], nums[i] <= threshold
//
//
// Return an integer denoting the length of the longest such subarray.
//
// Note: A subarray is a contiguous non-empty sequence of elements within an array.
//
// Example:
// Input: nums = [3,2,5,4], threshold = 5
// Output: 3
// Explanation: In this example, we can select the subarray that starts at l = 1 and ends at r = 3 => [2,5,4]. This subarray satisfies the conditions.
// Hence, the answer is the length of the subarray, 3. We can show that 3 is the maximum possible achievable length.
//
// Constraints:
// 1 <= nums.length <= 100 
// 	1 <= nums[i] <= 100 
// 	1 <= threshold <= 100
//

class Solution {
public:
    int longestAlternatingSubarray(vector<int>& nums, int threshold) {
        int maxLength = 0;
        int currentLength = 0;
        bool expectingEven = true; // Start by expecting an even number

        for (int num : nums) {
            if (num > threshold) {
                // Reset if the number exceeds the threshold
                currentLength = 0;
                expectingEven = true;
                continue;
            }

            if ((expectingEven && num % 2 == 0) || (!expectingEven && num % 2 != 0)) {
                // Valid number in the alternating sequence
                currentLength++;
                maxLength = max(maxLength, currentLength);
                expectingEven = !expectingEven; // Toggle expectation
            } else {
                // Reset the sequence if the expectation is not met
                currentLength = (num % 2 == 0) ? 1 : 0; // Start new sequence if even
                expectingEven = (num % 2 != 0); // Set next expectation
            }
        }

        return maxLength;           
    }
};
