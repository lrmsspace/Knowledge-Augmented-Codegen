// Source: https://leetcode.com/problems/count-non-decreasing-subarrays-after-k-operations/   |   Difficulty: Hard
//
// Problem Description:
// You are given an array nums of n integers and an integer k.
//
// For each subarray of nums, you can apply up to k operations on it. In each operation, you increment any element of the subarray by 1.
//
// Note that each subarray is considered independently, meaning changes made to one subarray do not persist to another.
//
// Return the number of subarrays that you can make non-decreasing ​​​​​after performing at most k operations.
//
// An array is said to be non-decreasing if each element is greater than or equal to its previous element, if it exists.
//
// Example:
// Input: nums = [6,3,1,2,4,4], k = 7
//
// Output: 17
//
// Explanation:
//
// Out of all 21 possible subarrays of nums, only the subarrays [6, 3, 1], [6, 3, 1, 2], [6, 3, 1, 2, 4] and [6, 3, 1, 2, 4, 4] cannot be made non-decreasing after applying up to k = 7 operations. Thus, the number of non-decreasing subarrays is 21 - 4 = 17.
//
// Constraints:
// 1 <= nums.length <= 105
// 	1 <= nums[i] <= 109
// 	1 <= k <= 109
//

class Solution {
public:
    long long countNonDecreasingSubarrays(vector<int>& nums, int k) {
        int n = nums.size();
        long long result = 0;
        
        for (int start = 0; start < n; start++) {
            long long operationsUsed = 0;
            int prev = nums[start];
            
            for (int end = start; end < n; end++) {
                if (nums[end] < prev) {
                    operationsUsed += (prev - nums[end]);
                } else {
                    prev = nums[end];
                }
                
                if (operationsUsed <= k) {
                    result++;
                } else {
                    break;
                }
            }
        }
        
        return result;          
    }
};
