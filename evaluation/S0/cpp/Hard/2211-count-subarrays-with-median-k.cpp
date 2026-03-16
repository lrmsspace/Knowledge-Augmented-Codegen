// Source: https://leetcode.com/problems/count-subarrays-with-median-k/   |   Difficulty: Hard
//
// Problem Description:
// You are given an array nums of size n consisting of distinct integers from 1 to n and a positive integer k.
//
// Return the number of non-empty subarrays in nums that have a median equal to k.
//
// Note:
//
//
// 	The median of an array is the middle element after sorting the array in ascending order. If the array is of even length, the median is the left middle element.
//
// 	
// 		For example, the median of [2,3,1,4] is 2, and the median of [8,4,3,5,1] is 4.
// 	
// 	
// 	A subarray is a contiguous part of an array.
//
// Example:
// Input: nums = [3,2,1,4,5], k = 4
// Output: 3
// Explanation: The subarrays that have a median equal to 4 are: [4], [4,5] and [1,4,5].
//
// Constraints:
// n == nums.length
// 	1 <= n <= 105
// 	1 <= nums[i], k <= n
// 	The integers in nums are distinct.
//

class Solution {
public:
    int countSubarrays(vector<int>& nums, int k) {
        int n = nums.size();
        int kIndex = 0;
        for (int i = 0; i < n; i++) {
            if (nums[i] == k) {
                kIndex = i;
                break;
            }
        }
        
        unordered_map<int, int> countMap;
        int balance = 0;
        countMap[0] = 1;  // empty prefix
        
        // Count balances to the left of k
        for (int i = kIndex - 1; i >= 0; i--) {
            if (nums[i] < k) {
                balance--;
            } else {
                balance++;
            }
            countMap[balance]++;
        }
        
        int result = 0;
        balance = 0;
        
        // Count valid subarrays including and to the right of k
        for (int i = kIndex; i < n; i++) {
            if (nums[i] < k) {
                balance--;
            } else {
                balance++;
            }
            result += countMap[balance];
            result += countMap[balance - 1];
        }
        
        return result;          
    }
};
