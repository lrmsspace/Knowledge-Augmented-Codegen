# Source: https://leetcode.com/problems/split-array-into-consecutive-subsequences/   |   Difficulty: Medium
#
# Problem Description:
# You are given an integer array nums that is sorted in non-decreasing order.
#
# Determine if it is possible to split nums into one or more subsequences such that both of the following conditions are true:
#
#
# 	Each subsequence is a consecutive increasing sequence (i.e. each integer is exactly one more than the previous integer).
# 	All subsequences have a length of 3 or more.
#
#
# Return true if you can split nums according to the above conditions, or false otherwise.
#
# A subsequence of an array is a new array that is formed from the original array by deleting some (can be none) of the elements without disturbing the relative positions of the remaining elements. (i.e., [1,3,5] is a subsequence of [1,2,3,4,5] while [1,3,2] is not).
#
# Example:
# Input: nums = [1,2,3,3,4,5]
# Output: true
# Explanation: nums can be split into the following subsequences:
# [1,2,3,3,4,5] --> 1, 2, 3
# [1,2,3,3,4,5] --> 3, 4, 5
#
# Constraints:
# 1 <= nums.length <= 104
# 	-1000 <= nums[i] <= 1000
# 	nums is sorted in non-decreasing order.
#

class Solution(object):
    def isPossible(self, nums):
        """
        :type nums: List[int]
        :rtype: bool
        """
        from collections import Counter, defaultdict

        freq = Counter(nums)
        need = defaultdict(int)

        for num in nums:
            if freq[num] == 0:
                continue
            elif need[num] > 0:
                need[num] -= 1
                need[num + 1] += 1
            elif freq[num + 1] > 0 and freq[num + 2] > 0:
                freq[num + 1] -= 1
                freq[num + 2] -= 1
                need[num + 3] += 1
            else:
                return False
            freq[num] -= 1

        return True