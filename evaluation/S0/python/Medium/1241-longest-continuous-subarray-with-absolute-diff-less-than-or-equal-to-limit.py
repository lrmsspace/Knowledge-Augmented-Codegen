# Source: https://leetcode.com/problems/longest-continuous-subarray-with-absolute-diff-less-than-or-equal-to-limit/   |   Difficulty: Medium
#
# Problem Description:
# Given an array of integers nums and an integer limit, return the size of the longest non-empty subarray such that the absolute difference between any two elements of this subarray is less than or equal to limit.
#
# Example:
# Input: nums = [8,2,4,7], limit = 4
# Output: 2 
# Explanation: All subarrays are: 
# [8] with maximum absolute diff |8-8| = 0 <= 4.
# [8,2] with maximum absolute diff |8-2| = 6 > 4. 
# [8,2,4] with maximum absolute diff |8-2| = 6 > 4.
# [8,2,4,7] with maximum absolute diff |8-2| = 6 > 4.
# [2] with maximum absolute diff |2-2| = 0 <= 4.
# [2,4] with maximum absolute diff |2-4| = 2 <= 4.
# [2,4,7] with maximum absolute diff |2-7| = 5 > 4.
# [4] with maximum absolute diff |4-4| = 0 <= 4.
# [4,7] with maximum absolute diff |4-7| = 3 <= 4.
# [7] with maximum absolute diff |7-7| = 0 <= 4. 
# Therefore, the size of the longest subarray is 2.
#
# Constraints:
# 1 <= nums.length <= 105
# 	1 <= nums[i] <= 109
# 	0 <= limit <= 109
#

class Solution(object):
    def longestSubarray(self, nums, limit):
        """
        :type nums: List[int]
        :type limit: int
        :rtype: int
        """
        from collections import deque

        max_dq = deque()  # Deque to keep track of max elements
        min_dq = deque()  # Deque to keep track of min elements
        left = 0
        result = 0

        for right in range(len(nums)):
            # Maintain the max deque
            while max_dq and nums[right] > max_dq[-1]:
                max_dq.pop()
            max_dq.append(nums[right])

            # Maintain the min deque
            while min_dq and nums[right] < min_dq[-1]:
                min_dq.pop()
            min_dq.append(nums[right])

            # Shrink the window from the left if the condition is violated
            while max_dq[0] - min_dq[0] > limit:
                if nums[left] == max_dq[0]:
                    max_dq.popleft()
                if nums[left] == min_dq[0]:
                    min_dq.popleft()
                left += 1

            # Update the result with the size of the current valid window
            result = max(result, right - left + 1)

        return result