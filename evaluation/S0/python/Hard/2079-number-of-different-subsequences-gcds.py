# Source: https://leetcode.com/problems/number-of-different-subsequences-gcds/   |   Difficulty: Hard
#
# Problem Description:
# You are given an array nums that consists of positive integers.
#
# The GCD of a sequence of numbers is defined as the greatest integer that divides all the numbers in the sequence evenly.
#
#
# 	For example, the GCD of the sequence [4,6,16] is 2.
#
#
# A subsequence of an array is a sequence that can be formed by removing some elements (possibly none) of the array.
#
#
# 	For example, [2,5,10] is a subsequence of [1,2,1,2,4,1,5,10].
#
#
# Return the number of different GCDs among all non-empty subsequences of nums.
#
# Example:
# Input: nums = [6,10,3]
# Output: 5
# Explanation: The figure shows all the non-empty subsequences and their GCDs.
# The different GCDs are 6, 10, 3, 2, and 1.
#
# Constraints:
# 1 <= nums.length <= 105
# 	1 <= nums[i] <= 2 * 105
#

class Solution(object):
    def countDifferentSubsequenceGCDs(self, nums):
        """
        :type nums: List[int]
        :rtype: int
        """
        max_num = max(nums)
        num_set = set(nums)
        result = 0

        for gcd_candidate in range(1, max_num + 1):
            current_gcd = 0
            for multiple in range(gcd_candidate, max_num + 1, gcd_candidate):
                if multiple in num_set:
                    current_gcd = self.compute_gcd(current_gcd, multiple)
                if current_gcd == gcd_candidate:
                    break
            if current_gcd == gcd_candidate:
                result += 1

        return result