# Source: https://leetcode.com/problems/find-unique-binary-string/   |   Difficulty: Medium
#
# Problem Description:
# Given an array of strings nums containing n unique binary strings each of length n, return a binary string of length n that does not appear in nums. If there are multiple answers, you may return any of them.
#
# Example:
# Input: nums = ["01","10"]
# Output: "11"
# Explanation: "11" does not appear in nums. "00" would also be correct.
#
# Constraints:
# n == nums.length
# 	1 <= n <= 16
# 	nums[i].length == n
# 	nums[i] is either '0' or '1'.
# 	All the strings of nums are unique.
#

class Solution(object):
    def findDifferentBinaryString(self, nums):
        """
        :type nums: List[str]
        :rtype: str
        """
        n = len(nums)
        result = []
        
        for i in range(n):
            # Flip the i-th bit of the i-th string
            if nums[i][i] == '0':
                result.append('1')
            else:
                result.append('0')
        
        return ''.join(result)