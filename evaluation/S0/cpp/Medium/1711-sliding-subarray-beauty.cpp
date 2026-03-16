// Source: https://leetcode.com/problems/sliding-subarray-beauty/   |   Difficulty: Medium
//
// Problem Description:
// Given an integer array nums containing n integers, find the beauty of each subarray of size k.
//
// The beauty of a subarray is the xth smallest integer in the subarray if it is negative, or 0 if there are fewer than x negative integers.
//
// Return an integer array containing n - k + 1 integers, which denote the beauty of the subarrays in order from the first index in the array.
//
//
// 	
// 	A subarray is a contiguous non-empty sequence of elements within an array.
//
// Example:
// Input: nums = [1,-1,-3,-2,3], k = 3, x = 2
// Output: [-1,-2,-2]
// Explanation: There are 3 subarrays with size k = 3. 
// The first subarray is [1, -1, -3] and the 2nd smallest negative integer is -1. 
// The second subarray is [-1, -3, -2] and the 2nd smallest negative integer is -2. 
// The third subarray is [-3, -2, 3] and the 2nd smallest negative integer is -2.
//
// Constraints:
// n == nums.length 
// 	1 <= n <= 105
// 	1 <= k <= n
// 	1 <= x <= k 
// 	-50 <= nums[i] <= 50
//

class Solution {
public:
    vector<int> getSubarrayBeauty(vector<int>& nums, int k, int x) {
        vector<int> freq(51, 0);
        vector<int> result;
        int n = nums.size();

        // Initialize frequency for the first window
        for (int i = 0; i < k; ++i) {
            if (nums[i] < 0) {
                freq[-nums[i]]++;
            }
        }

        // Function to find the x-th smallest negative number in the current frequency array
        auto findXthSmallestNegative = [&]() {
            int count = 0;
            for (int i = 50; i >= 1; --i) {
                count += freq[i];
                if (count >= x) {
                    return -i;
                }
            }
            return 0;
        };

        result.push_back(findXthSmallestNegative());

        // Slide the window
        for (int i = k; i < n; ++i) {
            // Remove the element going out of the window
            if (nums[i - k] < 0) {
                freq[-nums[i - k]]--;
            }
            // Add the new element coming into the window
            if (nums[i] < 0) {
                freq[-nums[i]]++;
            }
            result.push_back(findXthSmallestNegative());
        }

        return result;          
    }
};
