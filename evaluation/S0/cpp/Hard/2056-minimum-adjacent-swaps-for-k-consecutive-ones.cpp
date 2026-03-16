// Source: https://leetcode.com/problems/minimum-adjacent-swaps-for-k-consecutive-ones/   |   Difficulty: Hard
//
// Problem Description:
// You are given an integer array, nums, and an integer k. nums comprises of only 0's and 1's. In one move, you can choose two adjacent indices and swap their values.
//
// Return the minimum number of moves required so that nums has k consecutive 1's.
//
// Example:
// Input: nums = [1,0,0,1,0,1], k = 2
// Output: 1
// Explanation: In 1 move, nums could be [1,0,0,0,1,1] and have 2 consecutive 1's.
//
// Constraints:
// 1 <= nums.length <= 105
// 	nums[i] is 0 or 1.
// 	1 <= k <= sum(nums)
//

class Solution {
public:
    int minMoves(vector<int>& nums, int k) {
        vector<int> positions;
        for (int i = 0; i < nums.size(); i++) {
            if (nums[i] == 1) {
                positions.push_back(i);
            }
        }
        
        int n = positions.size();
        vector<long long> prefixSum(n + 1, 0);
        for (int i = 0; i < n; i++) {
            prefixSum[i + 1] = prefixSum[i] + positions[i];
        }
        
        long long minMoves = LLONG_MAX;
        for (int i = 0; i <= n - k; i++) {
            int mid = i + k / 2;
            long long leftSum = prefixSum[mid] - prefixSum[i];
            long long rightSum = prefixSum[i + k] - prefixSum[mid + 1];
            long long median = positions[mid];
            
            long long leftMoves = median * (mid - i) - leftSum;
            long long rightMoves = rightSum - median * (i + k - mid - 1);
            
            // Adjust for the gaps
            long long gapAdjustment = (long long)(k / 2) * (k - k / 2);
            long long totalMoves = leftMoves + rightMoves - gapAdjustment;
            
            minMoves = min(minMoves, totalMoves);
        }
        
        return (int)minMoves;           
    }
};
