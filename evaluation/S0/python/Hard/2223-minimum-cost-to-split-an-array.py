# Source: https://leetcode.com/problems/minimum-cost-to-split-an-array/   |   Difficulty: Hard
#
# Problem Description:
# You are given an integer array nums and an integer k.
#
# Split the array into some number of non-empty subarrays. The cost of a split is the sum of the importance value of each subarray in the split.
#
# Let trimmed(subarray) be the version of the subarray where all numbers which appear only once are removed.
#
#
# 	For example, trimmed([3,1,2,4,3,4]) = [3,4,3,4].
#
#
# The importance value of a subarray is k + trimmed(subarray).length.
#
#
# 	For example, if a subarray is [1,2,3,3,3,4,4], then trimmed([1,2,3,3,3,4,4]) = [3,3,3,4,4].The importance value of this subarray will be k + 5.
#
#
# Return the minimum possible cost of a split of nums.
#
# A subarray is a contiguous non-empty sequence of elements within an array.
#
# Example:
# Input: nums = [1,2,1,2,1,3,3], k = 2
# Output: 8
# Explanation: We split nums to have two subarrays: [1,2], [1,2,1,3,3].
# The importance value of [1,2] is 2 + (0) = 2.
# The importance value of [1,2,1,3,3] is 2 + (2 + 2) = 6.
# The cost of the split is 2 + 6 = 8. It can be shown that this is the minimum possible cost among all the possible splits.
#
# Constraints:
# 1 <= nums.length <= 1000
# 	0 <= nums[i] < nums.length
# 	1 <= k <= 109
#
#
#  
# .spoilerbutton {display:block; border:dashed; padding: 0px 0px; margin:10px 0px; font-size:150%; font-weight: bold; color:#000000; background-color:cyan; outline:0; 
# }
# .spoiler {overflow:hidden;}
# .spoiler > div {-webkit-transition: all 0s ease;-moz-transition: margin 0s ease;-o-transition: all 0s ease;transition: margin 0s ease;}
# .spoilerbutton[value="Show Message"] + .spoiler > div {margin-top:-500%;}
# .spoilerbutton[value="Hide Message"] + .spoiler {padding:5px;}
#

class Solution(object):
    def minCost(self, nums, k):
        """
        :type nums: List[int]
        :type k: int
        :rtype: int
        """
        n = len(nums)
        dp = [0] * (n + 1)
        
        for i in range(1, n + 1):
            freq = {}
            trimmed_length = 0
            dp[i] = dp[i - 1] + k  # Start with the cost of a new subarray
            
            for j in range(i, 0, -1):
                freq[nums[j - 1]] = freq.get(nums[j - 1], 0) + 1
                
                if freq[nums[j - 1]] == 2:
                    trimmed_length += 2
                elif freq[nums[j - 1]] > 2:
                    trimmed_length += 1
                
                current_cost = dp[j - 1] + k + trimmed_length
                dp[i] = min(dp[i], current_cost)
        
        return dp[n]