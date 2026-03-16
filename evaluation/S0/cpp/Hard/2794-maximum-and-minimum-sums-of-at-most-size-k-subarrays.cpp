// Source: https://leetcode.com/problems/maximum-and-minimum-sums-of-at-most-size-k-subarrays/   |   Difficulty: Hard
//
// Problem Description:
// You are given an integer array nums and a positive integer k. Return the sum of the maximum and minimum elements of all subarrays with at most k elements.
//
// Example:
// Input: nums = [1,2,3], k = 2
//
// Output: 20
//
// Explanation:
//
// The subarrays of nums with at most 2 elements are:
//
//
// 	
// 		
// 			Subarray
// 			Minimum
// 			Maximum
// 			Sum
// 		
// 		
// 			[1]
// 			1
// 			1
// 			2
// 		
// 		
// 			[2]
// 			2
// 			2
// 			4
// 		
// 		
// 			[3]
// 			3
// 			3
// 			6
// 		
// 		
// 			[1, 2]
// 			1
// 			2
// 			3
// 		
// 		
// 			[2, 3]
// 			2
// 			3
// 			5
// 		
// 		
// 			Final Total
// 			 
// 			 
// 			20
// 		
// 	
//
//
// The output would be 20.
//
// Constraints:
// 1 <= nums.length <= 80000
// 	1 <= k <= nums.length
// 	-106 <= nums[i] <= 106
//

class Solution {
public:
    long long minMaxSubarraySum(vector<int>& nums, int k) {
        const int MOD = 1e9 + 7;
        int n = nums.size();
        long long totalSum = 0;

        // Calculate sum of maximums
        deque<int> maxDeque;
        for (int i = 0; i < n; ++i) {
            while (!maxDeque.empty() && nums[maxDeque.back()] <= nums[i]) {
                maxDeque.pop_back();
            }
            maxDeque.push_back(i);
            if (i >= k && maxDeque.front() == i - k) {
                maxDeque.pop_front();
            }
            totalSum = (totalSum + nums[maxDeque.front()]) % MOD;
        }

        // Calculate sum of minimums
        deque<int> minDeque;
        for (int i = 0; i < n; ++i) {
            while (!minDeque.empty() && nums[minDeque.back()] >= nums[i]) {
                minDeque.pop_back();
            }
            minDeque.push_back(i);
            if (i >= k && minDeque.front() == i - k) {
                minDeque.pop_front();
            }
            totalSum = (totalSum + nums[minDeque.front()]) % MOD;
        }

        return totalSum;            
    }
};
