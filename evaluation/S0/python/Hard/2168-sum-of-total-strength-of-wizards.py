# Source: https://leetcode.com/problems/sum-of-total-strength-of-wizards/   |   Difficulty: Hard
#
# Problem Description:
# As the ruler of a kingdom, you have an army of wizards at your command.
#
# You are given a 0-indexed integer array strength, where strength[i] denotes the strength of the ith wizard. For a contiguous group of wizards (i.e. the wizards' strengths form a subarray of strength), the total strength is defined as the product of the following two values:
#
#
# 	The strength of the weakest wizard in the group.
# 	The total of all the individual strengths of the wizards in the group.
#
#
# Return the sum of the total strengths of all contiguous groups of wizards. Since the answer may be very large, return it modulo 109 + 7.
#
# A subarray is a contiguous non-empty sequence of elements within an array.
#
# Example:
# Input: strength = [1,3,1,2]
# Output: 44
# Explanation: The following are all the contiguous groups of wizards:
# - [1] from [1,3,1,2] has a total strength of min([1]) * sum([1]) = 1 * 1 = 1
# - [3] from [1,3,1,2] has a total strength of min([3]) * sum([3]) = 3 * 3 = 9
# - [1] from [1,3,1,2] has a total strength of min([1]) * sum([1]) = 1 * 1 = 1
# - [2] from [1,3,1,2] has a total strength of min([2]) * sum([2]) = 2 * 2 = 4
# - [1,3] from [1,3,1,2] has a total strength of min([1,3]) * sum([1,3]) = 1 * 4 = 4
# - [3,1] from [1,3,1,2] has a total strength of min([3,1]) * sum([3,1]) = 1 * 4 = 4
# - [1,2] from [1,3,1,2] has a total strength of min([1,2]) * sum([1,2]) = 1 * 3 = 3
# - [1,3,1] from [1,3,1,2] has a total strength of min([1,3,1]) * sum([1,3,1]) = 1 * 5 = 5
# - [3,1,2] from [1,3,1,2] has a total strength of min([3,1,2]) * sum([3,1,2]) = 1 * 6 = 6
# - [1,3,1,2] from [1,3,1,2] has a total strength of min([1,3,1,2]) * sum([1,3,1,2]) = 1 * 7 = 7
# The sum of all the total strengths is 1 + 9 + 1 + 4 + 4 + 4 + 3 + 5 + 6 + 7 = 44.
#
# Constraints:
# 1 <= strength.length <= 105
# 	1 <= strength[i] <= 109
#

class Solution(object):
    def totalStrength(self, strength):
        """
        :type strength: List[int]
        :rtype: int
        """
        MOD = 10**9 + 7
        n = len(strength)
        
        # 前缀和
        prefix_sum = [0] * (n + 1)
        for i in range(n):
            prefix_sum[i + 1] = (prefix_sum[i] + strength[i]) % MOD
        
        # 前缀和的前缀和
        prefix_prefix_sum = [0] * (n + 2)
        for i in range(n + 1):
            prefix_prefix_sum[i + 1] = (prefix_prefix_sum[i] + prefix_sum[i]) % MOD
        
        # 单调栈找到每个元素的左边界和右边界
        left = [-1] * n
        right = [n] * n
        stack = []
        
        for i in range(n):
            while stack and strength[stack[-1]] > strength[i]:
                idx = stack.pop()
                right[idx] = i
            if stack:
                left[i] = stack[-1]
            stack.append(i)
        
        result = 0
        
        for i in range(n):
            l, r = left[i], right[i]
            total_left = (prefix_prefix_sum[i + 1] - prefix_prefix_sum[l + 1]) % MOD
            total_right = (prefix_prefix_sum[r + 1] - prefix_prefix_sum[i + 1]) % MOD
            
            count_left = i - l
            count_right = r - i
            
            total_strength = (total_right * count_left - total_left * count_right) % MOD
            result = (result + strength[i] * total_strength) % MOD
        
        return result