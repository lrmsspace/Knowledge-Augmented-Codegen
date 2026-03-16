// Source: https://leetcode.com/problems/final-array-state-after-k-multiplication-operations-i/   |   Difficulty: Easy
//
// Problem Description:
// You are given an integer array nums, an integer k, and an integer multiplier.
//
// You need to perform k operations on nums. In each operation:
//
//
// 	Find the minimum value x in nums. If there are multiple occurrences of the minimum value, select the one that appears first.
// 	Replace the selected minimum value x with x * multiplier.
//
//
// Return an integer array denoting the final state of nums after performing all k operations.
//
// Example:
// Input: nums = [2,1,3,5,6], k = 5, multiplier = 2
//
// Output: [8,4,6,5,6]
//
// Explanation:
//
//
// 	
// 		
// 			Operation
// 			Result
// 		
// 		
// 			After operation 1
// 			[2, 2, 3, 5, 6]
// 		
// 		
// 			After operation 2
// 			[4, 2, 3, 5, 6]
// 		
// 		
// 			After operation 3
// 			[4, 4, 3, 5, 6]
// 		
// 		
// 			After operation 4
// 			[4, 4, 6, 5, 6]
// 		
// 		
// 			After operation 5
// 			[8, 4, 6, 5, 6]
//
// Constraints:
// 1 <= nums.length <= 100
// 	1 <= nums[i] <= 100
// 	1 <= k <= 10
// 	1 <= multiplier <= 5
//

class Solution {
public:
    vector<int> getFinalState(vector<int>& nums, int k, int multiplier) {
        for (int operation = 0; operation < k; ++operation) {
            int minIndex = 0;
            for (int i = 1; i < nums.size(); ++i) {
                if (nums[i] < nums[minIndex]) {
                    minIndex = i;
                }
            }
            nums[minIndex] *= multiplier;
        }
        return nums;            
    }
};
