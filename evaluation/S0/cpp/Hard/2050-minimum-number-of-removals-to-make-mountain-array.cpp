// Source: https://leetcode.com/problems/minimum-number-of-removals-to-make-mountain-array/   |   Difficulty: Hard
//
// Problem Description:
// You may recall that an array arr is a mountain array if and only if:
//
//
// 	arr.length >= 3
// 	There exists some index i (0-indexed) with 0 < i < arr.length - 1 such that:
// 	
// 		arr[0] < arr[1] < ... < arr[i - 1] < arr[i]
// 		arr[i] > arr[i + 1] > ... > arr[arr.length - 1]
// 	
// 	
//
//
// Given an integer array nums​​​, return the minimum number of elements to remove to make nums​​​ a mountain array.
//
// Example:
// Input: nums = [1,3,1]
// Output: 0
// Explanation: The array itself is a mountain array so we do not need to remove any elements.
//
// Constraints:
// 3 <= nums.length <= 1000
// 	1 <= nums[i] <= 109
// 	It is guaranteed that you can make a mountain array out of nums.
//

class Solution {
public:
    int minimumMountainRemovals(vector<int>& nums) {
        int n = nums.size();
        vector<int> lis(n, 1), lds(n, 1);
        
        // Compute LIS from left to right
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < i; j++) {
                if (nums[j] < nums[i]) {
                    lis[i] = max(lis[i], lis[j] + 1);
                }
            }
        }
        
        // Compute LDS from right to left
        for (int i = n - 1; i >= 0; i--) {
            for (int j = n - 1; j > i; j--) {
                if (nums[j] < nums[i]) {
                    lds[i] = max(lds[i], lds[j] + 1);
                }
            }
        }
        
        int maxMountainLen = 0;
        
        // Find maximum length of mountain array
        for (int i = 1; i < n - 1; i++) {
            if (lis[i] > 1 && lds[i] > 1) {
                maxMountainLen = max(maxMountainLen, lis[i] + lds[i] - 1);
            }
        }
        
        return n - maxMountainLen;          
    }
};
