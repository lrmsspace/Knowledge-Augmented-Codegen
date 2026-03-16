# Source: https://leetcode.com/problems/largest-combination-with-bitwise-and-greater-than-zero/   |   Difficulty: Medium
#
# Problem Description:
# The bitwise AND of an array nums is the bitwise AND of all integers in nums.
#
#
# 	For example, for nums = [1, 5, 3], the bitwise AND is equal to 1 & 5 & 3 = 1.
# 	Also, for nums = [7], the bitwise AND is 7.
#
#
# You are given an array of positive integers candidates. Compute the bitwise AND for all possible combinations of elements in the candidates array.
#
# Return the size of the largest combination of candidates with a bitwise AND greater than 0.
#
# Example:
# Input: candidates = [16,17,71,62,12,24,14]
# Output: 4
# Explanation: The combination [16,17,62,24] has a bitwise AND of 16 & 17 & 62 & 24 = 16 > 0.
# The size of the combination is 4.
# It can be shown that no combination with a size greater than 4 has a bitwise AND greater than 0.
# Note that more than one combination may have the largest size.
# For example, the combination [62,12,24,14] has a bitwise AND of 62 & 12 & 24 & 14 = 8 > 0.
#
# Constraints:
# 1 <= candidates.length <= 105
# 	1 <= candidates[i] <= 107
#

class Solution(object):
    def largestCombination(self, candidates):
        """
        :type candidates: List[int]
        :rtype: int
        """
        max_count = 0
        for i in range(32):  # 遍历每一位
            count = 0
            for num in candidates:
                if num & (1 << i):  # 检查第 i 位是否为 1
                    count += 1
            max_count = max(max_count, count)
        return max_count