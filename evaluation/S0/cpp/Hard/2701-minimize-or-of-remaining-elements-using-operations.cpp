// Source: https://leetcode.com/problems/minimize-or-of-remaining-elements-using-operations/   |   Difficulty: Hard
//
// Problem Description:
// You are given a 0-indexed integer array nums and an integer k.
//
// In one operation, you can pick any index i of nums such that 0 <= i < nums.length - 1 and replace nums[i] and nums[i + 1] with a single occurrence of nums[i] & nums[i + 1], where & represents the bitwise AND operator.
//
// Return the minimum possible value of the bitwise OR of the remaining elements of nums after applying at most k operations.
//
// Example:
// Input: nums = [3,5,3,2,7], k = 2
// Output: 3
// Explanation: Let's do the following operations:
// 1. Replace nums[0] and nums[1] with (nums[0] & nums[1]) so that nums becomes equal to [1,3,2,7].
// 2. Replace nums[2] and nums[3] with (nums[2] & nums[3]) so that nums becomes equal to [1,3,2].
// The bitwise-or of the final array is 3.
// It can be shown that 3 is the minimum possible value of the bitwise OR of the remaining elements of nums after applying at most k operations.
//
// Constraints:
// 1 <= nums.length <= 105
// 	0 <= nums[i] < 230
// 	0 <= k < nums.length
//

class Solution {
public:
    int minOrAfterOperations(vector<int>& nums, int k) {
        int n = nums.size();
        int left = 0, right = (1 << 30) - 1;
        int answer = right;
        
        while (left <= right) {
            int mid = left + (right - left) / 2;
            
            // Check if we can achieve bitwise OR <= mid with at most k operations
            int operations = 0;
            int i = 0;
            while (i < n) {
                int currentAnd = nums[i];
                int j = i;
                
                // Try to merge as many elements as possible without exceeding mid
                while (j + 1 < n && (currentAnd & nums[j + 1]) <= mid) {
                    currentAnd &= nums[j + 1];
                    j++;
                }
                
                if (j > i) {
                    operations += (j - i); // Number of merges
                }
                
                i = j + 1; // Move to the next unmerged element
            }
            
            if (operations <= k) {
                answer = mid;
                right = mid - 1;
            } else {
                left = mid + 1;
            }
        }
        
        return answer;          
    }
};
