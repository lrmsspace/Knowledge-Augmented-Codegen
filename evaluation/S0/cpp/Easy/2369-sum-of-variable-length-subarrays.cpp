// Source: https://leetcode.com/problems/sum-of-variable-length-subarrays/   |   Difficulty: Easy
//
// Problem Description:
// You are given an integer array nums of size n. For each index i where 0 <= i < n, define a subarray nums[start ... i] where start = max(0, i - nums[i]).
//
// Return the total sum of all elements from the subarray defined for each index in the array.
//
// Example:
// Input: nums = [2,3,1]
//
// Output: 11
//
// Explanation:
//
//
// 	
// 		
// 			i
// 			Subarray
// 			Sum
// 		
// 		
// 			0
// 			nums[0] = [2]
// 			2
// 		
// 		
// 			1
// 			nums[0 ... 1] = [2, 3]
// 			5
// 		
// 		
// 			2
// 			nums[1 ... 2] = [3, 1]
// 			4
// 		
// 		
// 			Total Sum
// 			 
// 			11
// 		
// 	
//
//
// The total sum is 11. Hence, 11 is the output.
//
// Constraints:
// 1 <= n == nums.length <= 100
// 	1 <= nums[i] <= 1000
//

class Solution {
public:
    int subarraySum(vector<int>& nums) {
        int n = nums.size();
        int totalSum = 0;

        for (int i = 0; i < n; ++i) {
            int start = max(0, i - nums[i]);
            for (int j = start; j <= i; ++j) {
                totalSum += nums[j];
            }
        }

        return totalSum;            
    }
};
