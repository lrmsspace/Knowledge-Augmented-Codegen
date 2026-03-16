// Source: https://leetcode.com/problems/earliest-second-to-mark-indices-ii/   |   Difficulty: Hard
//
// Problem Description:
// You are given two 1-indexed integer arrays, nums and, changeIndices, having lengths n and m, respectively.
//
// Initially, all indices in nums are unmarked. Your task is to mark all indices in nums.
//
// In each second, s, in order from 1 to m (inclusive), you can perform one of the following operations:
//
//
// 	Choose an index i in the range [1, n] and decrement nums[i] by 1.
// 	Set nums[changeIndices[s]] to any non-negative value.
// 	Choose an index i in the range [1, n], where nums[i] is equal to 0, and mark index i.
// 	Do nothing.
//
//
// Return an integer denoting the earliest second in the range [1, m] when all indices in nums can be marked by choosing operations optimally, or -1 if it is impossible.
//
// Example:
// Input: nums = [3,2,3], changeIndices = [1,3,2,2,2,2,3]
// Output: 6
// Explanation: In this example, we have 7 seconds. The following operations can be performed to mark all indices:
// Second 1: Set nums[changeIndices[1]] to 0. nums becomes [0,2,3].
// Second 2: Set nums[changeIndices[2]] to 0. nums becomes [0,2,0].
// Second 3: Set nums[changeIndices[3]] to 0. nums becomes [0,0,0].
// Second 4: Mark index 1, since nums[1] is equal to 0.
// Second 5: Mark index 2, since nums[2] is equal to 0.
// Second 6: Mark index 3, since nums[3] is equal to 0.
// Now all indices have been marked.
// It can be shown that it is not possible to mark all indices earlier than the 6th second.
// Hence, the answer is 6.
//
// Constraints:
// 1 <= n == nums.length <= 5000
// 	0 <= nums[i] <= 109
// 	1 <= m == changeIndices.length <= 5000
// 	1 <= changeIndices[i] <= n
//

class Solution {
public:
    int earliestSecondToMarkIndices(vector<int>& nums, vector<int>& changeIndices) {
        int n = nums.size();
        int m = changeIndices.size();
        vector<int> lastChange(n, -1);
        
        for (int s = 0; s < m; s++) {
            lastChange[changeIndices[s] - 1] = s;
        }
        
        vector<pair<int, int>> changes;
        for (int i = 0; i < n; i++) {
            if (lastChange[i] != -1) {
                changes.push_back({lastChange[i], i});
            }
        }
        
        sort(changes.begin(), changes.end());
        
        int time = 0;
        for (auto& change : changes) {
            int s = change.first;
            int idx = change.second;
            if (time + nums[idx] <= s) {
                time += nums[idx];
            } else {
                return -1;
            }
            time++; // marking takes 1 second
        }
        
        return time <= m ? time : -1;           
    }
};
