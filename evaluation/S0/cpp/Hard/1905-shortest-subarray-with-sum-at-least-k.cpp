// Source: https://leetcode.com/problems/shortest-subarray-with-sum-at-least-k/   |   Difficulty: Hard
//
// Problem Description:
// Given an integer array nums and an integer k, return the length of the shortest non-empty subarray of nums with a sum of at least k. If there is no such subarray, return -1.
//
// A subarray is a contiguous part of an array.
//
// Example:
// Input: nums = [1], k = 1
// Output: 1
//
// Constraints:
// 1 <= nums.length <= 105
// 	-105 <= nums[i] <= 105
// 	1 <= k <= 109
//

class Solution {
public:
    int shortestSubarray(vector<int>& nums, int k) {
        int n = nums.size();
        vector<long long> prefixSums(n + 1, 0);
        for (int i = 0; i < n; i++) {
            prefixSums[i + 1] = prefixSums[i] + nums[i];
        }
        
        deque<int> dq;
        int minLength = n + 1;
        
        for (int i = 0; i <= n; i++) {
            while (!dq.empty() && prefixSums[i] - prefixSums[dq.front()] >= k) {
                minLength = min(minLength, i - dq.front());
                dq.pop_front();
            }
            
            while (!dq.empty() && prefixSums[i] <= prefixSums[dq.back()]) {
                dq.pop_back();
            }
            
            dq.push_back(i);
        }
        
        return minLength == n + 1 ? -1 : minLength;         
    }
};
