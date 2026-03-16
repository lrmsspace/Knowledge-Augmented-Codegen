# Source: https://leetcode.com/problems/special-array-ii/   |   Difficulty: Medium
#
# Problem Description:
# An array is considered special if every pair of its adjacent elements contains two numbers with different parity.
#
# You are given an array of integer nums and a 2D integer matrix queries, where for queries[i] = [fromi, toi] your task is to check that subarray nums[fromi..toi] is special or not.
#
# Return an array of booleans answer such that answer[i] is true if nums[fromi..toi] is special.
#
# Example:
# Input: nums = [3,4,1,2,6], queries = [[0,4]]
#
# Output: [false]
#
# Explanation:
#
# The subarray is [3,4,1,2,6]. 2 and 6 are both even.
#
# Constraints:
# 1 <= nums.length <= 105
# 	1 <= nums[i] <= 105
# 	1 <= queries.length <= 105
# 	queries[i].length == 2
# 	0 <= queries[i][0] <= queries[i][1] <= nums.length - 1
#

class Solution(object):
    def isArraySpecial(self, nums, queries):
        """
        :type nums: List[int]
        :type queries: List[List[int]]
        :rtype: List[bool]
        """
        n = len(nums)
        prefix = [0] * n
        
        for i in range(1, n):
            if (nums[i] % 2) != (nums[i - 1] % 2):
                prefix[i] = prefix[i - 1]
            else:
                prefix[i] = prefix[i - 1] + 1
        
        result = []
        for fromi, toi in queries:
            if prefix[toi] - prefix[fromi] == 0:
                result.append(True)
            else:
                result.append(False)
        
        return result