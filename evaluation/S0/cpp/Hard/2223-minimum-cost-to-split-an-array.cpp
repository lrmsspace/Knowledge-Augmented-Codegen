// Source: https://leetcode.com/problems/minimum-cost-to-split-an-array/   |   Difficulty: Hard
//
// Problem Description:
// You are given an integer array nums and an integer k.
//
// Split the array into some number of non-empty subarrays. The cost of a split is the sum of the importance value of each subarray in the split.
//
// Let trimmed(subarray) be the version of the subarray where all numbers which appear only once are removed.
//
//
// 	For example, trimmed([3,1,2,4,3,4]) = [3,4,3,4].
//
//
// The importance value of a subarray is k + trimmed(subarray).length.
//
//
// 	For example, if a subarray is [1,2,3,3,3,4,4], then trimmed([1,2,3,3,3,4,4]) = [3,3,3,4,4].The importance value of this subarray will be k + 5.
//
//
// Return the minimum possible cost of a split of nums.
//
// A subarray is a contiguous non-empty sequence of elements within an array.
//
// Example:
// Input: nums = [1,2,1,2,1,3,3], k = 2
// Output: 8
// Explanation: We split nums to have two subarrays: [1,2], [1,2,1,3,3].
// The importance value of [1,2] is 2 + (0) = 2.
// The importance value of [1,2,1,3,3] is 2 + (2 + 2) = 6.
// The cost of the split is 2 + 6 = 8. It can be shown that this is the minimum possible cost among all the possible splits.
//
// Constraints:
// 1 <= nums.length <= 1000
// 	0 <= nums[i] < nums.length
// 	1 <= k <= 109
//
//
//  
// .spoilerbutton {display:block; border:dashed; padding: 0px 0px; margin:10px 0px; font-size:150%; font-weight: bold; color:#000000; background-color:cyan; outline:0; 
// }
// .spoiler {overflow:hidden;}
// .spoiler > div {-webkit-transition: all 0s ease;-moz-transition: margin 0s ease;-o-transition: all 0s ease;transition: margin 0s ease;}
// .spoilerbutton[value="Show Message"] + .spoiler > div {margin-top:-500%;}
// .spoilerbutton[value="Hide Message"] + .spoiler {padding:5px;}
//

class Solution {
public:
    int minCost(vector<int>& nums, int k) {
        int n = nums.size();
        vector<int> dp(n + 1, INT_MAX);
        dp[0] = 0;
        
        for (int i = 1; i <= n; i++) {
            unordered_map<int, int> freq;
            int trimLen = 0;
            
            for (int j = i; j >= 1; j--) {
                freq[nums[j - 1]]++;
                
                if (freq[nums[j - 1]] == 2) {
                    trimLen += 2;
                } else if (freq[nums[j - 1]] > 2) {
                    trimLen += 1;
                }
                
                dp[i] = min(dp[i], dp[j - 1] + k + trimLen);
            }
        }
        
        return dp[n];           
    }
};
