// Source: https://leetcode.com/problems/count-complete-subarrays-in-an-array/   |   Difficulty: Medium
//
// Problem Description:
// You are given an array nums consisting of positive integers.
//
// We call a subarray of an array complete if the following condition is satisfied:
//
//
// 	The number of distinct elements in the subarray is equal to the number of distinct elements in the whole array.
//
//
// Return the number of complete subarrays.
//
// A subarray is a contiguous non-empty part of an array.
//
// Example:
// Input: nums = [1,3,1,2,2]
// Output: 4
// Explanation: The complete subarrays are the following: [1,3,1,2], [1,3,1,2,2], [3,1,2] and [3,1,2,2].
//
// Constraints:
// 1 <= nums.length <= 1000
// 	1 <= nums[i] <= 2000
//

int countCompleteSubarrays(int* nums, int numsSize) {
    int totalDistinct = 0;
    int freqMap[2001] = {0};
    
    // Count total distinct elements in the entire array
    for (int i = 0; i < numsSize; i++) {
        if (freqMap[nums[i]] == 0) {
            totalDistinct++;
        }
        freqMap[nums[i]]++;
    }
    
    int result = 0;
    
    // Iterate through all possible starting points of subarrays
    for (int start = 0; start < numsSize; start++) {
        int currentDistinct = 0;
        int currentFreqMap[2001] = {0};
        
        // Iterate through all possible ending points of subarrays
        for (int end = start; end < numsSize; end++) {
            if (currentFreqMap[nums[end]] == 0) {
                currentDistinct++;
            }
            currentFreqMap[nums[end]]++;
            
            // If the number of distinct elements matches, increment result
            if (currentDistinct == totalDistinct) {
                result++;
            }
        }
    }
    
    return result;      
}
