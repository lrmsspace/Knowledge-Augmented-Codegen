// Source: https://leetcode.com/problems/make-the-xor-of-all-segments-equal-to-zero/   |   Difficulty: Hard
//
// Problem Description:
// You are given an array nums​​​ and an integer k​​​​​. The XOR of a segment [left, right] where left <= right is the XOR of all the elements with indices between left and right, inclusive: nums[left] XOR nums[left+1] XOR ... XOR nums[right].
//
// Return the minimum number of elements to change in the array such that the XOR of all segments of size k​​​​​​ is equal to zero.
//
// Example:
// Input: nums = [1,2,0,3,0], k = 1
// Output: 3
// Explanation: Modify the array from [1,2,0,3,0] to from [0,0,0,0,0].
//
// Constraints:
// 1 <= k <= nums.length <= 2000
// 	​​​​​​0 <= nums[i] < 210
//

class Solution {
public:
    int minChanges(vector<int>& nums, int k) {
        const int MAX_XOR = 1 << 10;
        const int INF = 1e9;
        int n = nums.size();
        
        vector<vector<int>> count(k, vector<int>(MAX_XOR, 0));
        vector<int> size(k, 0);
        
        // Count frequency of numbers in each group
        for (int i = 0; i < n; i++) {
            count[i % k][nums[i]]++;
            size[i % k]++;
        }
        
        // DP array
        vector<int> dp(MAX_XOR, INF);
        dp[0] = 0;
        
        for (int i = 0; i < k; i++) {
            vector<int> ndp(MAX_XOR, INF);
            int minPrev = *min_element(dp.begin(), dp.end());
            
            for (int xorVal = 0; xorVal < MAX_XOR; xorVal++) {
                // Case 1: Change all elements in group i
                ndp[xorVal] = minPrev + size[i];
                
                // Case 2: Keep some elements in group i
                for (int num = 0; num < MAX_XOR; num++) {
                    if (count[i][num] > 0) {
                        int changes = size[i] - count[i][num];
                        ndp[xorVal] = min(ndp[xorVal], dp[xorVal ^ num] + changes);
                    }
                }
            }
            dp = ndp;
        }
        
        return dp[0];           
    }
};
