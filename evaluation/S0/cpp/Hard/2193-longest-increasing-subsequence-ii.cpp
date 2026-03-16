// Source: https://leetcode.com/problems/longest-increasing-subsequence-ii/   |   Difficulty: Hard
//
// Problem Description:
// You are given an integer array nums and an integer k.
//
// Find the longest subsequence of nums that meets the following requirements:
//
//
// 	The subsequence is strictly increasing and
// 	The difference between adjacent elements in the subsequence is at most k.
//
//
// Return the length of the longest subsequence that meets the requirements.
//
// A subsequence is an array that can be derived from another array by deleting some or no elements without changing the order of the remaining elements.
//
// Example:
// Input: nums = [4,2,1,4,3,4,5,8,15], k = 3
// Output: 5
// Explanation:
// The longest subsequence that meets the requirements is [1,3,4,5,8].
// The subsequence has a length of 5, so we return 5.
// Note that the subsequence [1,3,4,5,8,15] does not meet the requirements because 15 - 8 = 7 is larger than 3.
//
// Constraints:
// 1 <= nums.length <= 105
// 	1 <= nums[i], k <= 105
//

class Solution {
public:
    int lengthOfLIS(vector<int>& nums, int k) {
        const int MAX_VAL = 100000;
        vector<int> segTree(4 * (MAX_VAL + 1), 0);
        
        function<void(int, int, int, int, int, int)> update = [&](int node, int start, int end, int idx, int val) {
            if (start == end) {
                segTree[node] = max(segTree[node], val);
                return;
            }
            int mid = (start + end) / 2;
            if (idx <= mid) {
                update(2 * node + 1, start, mid, idx, val);
            } else {
                update(2 * node + 2, mid + 1, end, idx, val);
            }
            segTree[node] = max(segTree[2 * node + 1], segTree[2 * node + 2]);
        };
        
        function<int(int, int, int, int, int)> query = [&](int node, int start, int end, int l, int r) {
            if (r < start || end < l) return 0;
            if (l <= start && end <= r) return segTree[node];
            int mid = (start + end) / 2;
            return max(query(2 * node + 1, start, mid, l, r),
                       query(2 * node + 2, mid + 1, end, l, r));
        };
        
        int result = 0;
        for (int num : nums) {
            int left = max(1, num - k);
            int right = num - 1;
            int bestPrev = query(0, 1, MAX_VAL, left, right);
            int currLen = bestPrev + 1;
            update(0, 1, MAX_VAL, num, currLen);
            result = max(result, currLen);
        }
        
        return result;          
    }
};
