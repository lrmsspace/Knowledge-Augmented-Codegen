// Source: https://leetcode.com/problems/divide-an-array-into-subarrays-with-minimum-cost-ii/   |   Difficulty: Hard
//
// Problem Description:
// You are given a 0-indexed array of integers nums of length n, and two positive integers k and dist.
//
// The cost of an array is the value of its first element. For example, the cost of [1,2,3] is 1 while the cost of [3,4,1] is 3.
//
// You need to divide nums into k disjoint contiguous subarrays, such that the difference between the starting index of the second subarray and the starting index of the kth subarray should be less than or equal to dist. In other words, if you divide nums into the subarrays nums[0..(i1 - 1)], nums[i1..(i2 - 1)], ..., nums[ik-1..(n - 1)], then ik-1 - i1 <= dist.
//
// Return the minimum possible sum of the cost of these subarrays.
//
// Example:
// Input: nums = [1,3,2,6,4,2], k = 3, dist = 3
// Output: 5
// Explanation: The best possible way to divide nums into 3 subarrays is: [1,3], [2,6,4], and [2]. This choice is valid because ik-1 - i1 is 5 - 2 = 3 which is equal to dist. The total cost is nums[0] + nums[2] + nums[5] which is 1 + 2 + 2 = 5.
// It can be shown that there is no possible way to divide nums into 3 subarrays at a cost lower than 5.
//
// Constraints:
// 3 <= n <= 105
//  1 <= nums[i] <= 109
//  3 <= k <= n
//  k - 2 <= dist <= n - 2
//

class Solution {
public:
    long long minimumCost(vector<int>& nums, int k, int dist) {
        int n = nums.size();
        vector<long long> dp(n + 1, LLONG_MAX);
        dp[0] = 0;
        
        for (int subarrays = 1; subarrays <= k; subarrays++) {
            vector<long long> newDp(n + 1, LLONG_MAX);
            // Use a deque to maintain the minimum dp[j] for j in [i - dist, i - 1]
            deque<int> dq;
            for (int i = 1; i <= n; i++) {
                // Remove indices out of range
                while (!dq.empty() && dq.front() < i - dist) {
                    dq.pop_front();
                }
                
                // Add dp[i - 1] to the deque
                if (dp[i - 1] != LLONG_MAX) {
                    while (!dq.empty() && dp[dq.back()] >= dp[i - 1]) {
                        dq.pop_back();
                    }
                    dq.push_back(i - 1);
                }
                
                // Update newDp[i] using the minimum dp[j] in range
                if (!dq.empty()) {
                    newDp[i] = dp[dq.front()] + nums[i - 1];
                }
            }
            dp = move(newDp);
        }
        
        return dp[n];           
    }
};
